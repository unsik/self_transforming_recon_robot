#include <Wire.h>
#include <Kalman.h> 

#include <SoftwareSerial.h>

SoftwareSerial serial1(11,12);


#define RESTRICT_PITCH 



Kalman kalmanX; 
Kalman kalmanY;

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
int16_t tempRaw;

double gyroXangle, gyroYangle; 
double compAngleX, compAngleY; 
double kalAngleX, kalAngleY;

uint32_t timer;
uint8_t i2cData[14]; 

int ch1 =150;
int ch2 =150;
int ch3 =150;
int ch4 =150;
int ch5 =150;
int ch6 =150;
int ch7 =150;
int ch8 =150;
int acc_x=0;
int acc_y=0;


void setup() {
  Serial.begin(9600);
  serial1.begin(9600);
  Wire.begin();
#if ARDUINO >= 157
  Wire.setClock(400000UL); 
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; 
#endif

  i2cData[0] = 7; 
  i2cData[1] = 0x00; 
  i2cData[2] = 0x00; 
  i2cData[3] = 0x00; 
  while (i2cWrite(0x19, i2cData, 4, false)); 
  while (i2cWrite(0x6B, 0x01, true)); 

  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { 
    Serial.print(F("Error reading sensor"));
    while (1);
  }

  delay(100); 

 
  while (i2cRead(0x3B, i2cData, 6));
  accX = (i2cData[0] << 8) | i2cData[1];
  accY = (i2cData[2] << 8) | i2cData[3];
  accZ = (i2cData[4] << 8) | i2cData[5];

  
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = roll;
  compAngleY = pitch;

  timer = micros();
  
  
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
}

void loop() {

ch1 = ((pulseIn(2, HIGH))/10);
ch2 = ((pulseIn(3, HIGH))/10);
ch3 = ((pulseIn(4, HIGH))/10);
ch4 = ((pulseIn(5, HIGH))/10);
ch5 = ((pulseIn(6, HIGH))/10);
ch6 = ((pulseIn(7, HIGH))/10);
ch7 = ((pulseIn(8, HIGH))/10);
ch8 = ((pulseIn(9, HIGH))/10);


  
///////////////////////////////////////////////////////////////////////////////////////////////////
/*                                 MPU6050 ROOP START                                            */
//////////////////////////////////////////////////////////////////////////////////////////////////  

  while (i2cRead(0x3B, i2cData, 14));
  accX = ((i2cData[0] << 8) | i2cData[1]);
  accY = ((i2cData[2] << 8) | i2cData[3]);
  accZ = ((i2cData[4] << 8) | i2cData[5]);
  tempRaw = (i2cData[6] << 8) | i2cData[7];
  gyroX = (i2cData[8] << 8) | i2cData[9];
  gyroY = (i2cData[10] << 8) | i2cData[11];
  gyroZ = (i2cData[12] << 8) | i2cData[13];

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  double gyroXrate = gyroX / 131.0; // Convert to deg/s
  double gyroYrate = gyroY / 131.0; // Convert to deg/s

#ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    compAngleX = roll;
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleX) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    compAngleY = pitch;
    kalAngleY = pitch;
    gyroYangle = pitch;
  } else
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleY) > 90)
    gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif

  gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  gyroYangle += gyroYrate * dt;
  //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate() * dt;

  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

  // Reset the gyro angle when it has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;

  acc_x = kalAngleX;
  acc_y = kalAngleY;
  
  if(acc_x<(-90))
  {
    acc_x=-90;
  }
  else if(acc_x>90)
  {
    acc_x=90;
  }
  
  if(acc_y<(-80))
  {
    acc_y=-80;
  }
  else if(acc_y>80)
  {
    acc_y=80;
  }
  
  Serial.print(acc_x); Serial.print("\t");

  Serial.print(acc_y); Serial.print("\t");
 
 
  acc_x = (acc_x+90);
  acc_y = (acc_y+80);


  delay(2);
  

  
///////////////////////////////////////////////////////////////////////////////////////////////////
/*                                 MPU6050 ROOP END                                              */
//////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.print("||ch1 - ");
  Serial.print(ch1);
   Serial.print("||ch2 - ");
  Serial.print(ch2);
   Serial.print("||ch3 - ");
  Serial.print(ch3);
   Serial.print("||ch4 - ");
  Serial.print(ch4);
   Serial.print("||ch5 - ");
  Serial.print(ch5);
   Serial.print("||ch6 - ");
  Serial.print(ch6);
   Serial.print("||ch7 - ");
  Serial.print(ch7);
   Serial.print("||ch8 - ");
  Serial.println(ch8);
  
serial1.write(253);   
serial1.write(acc_x);
serial1.write(acc_y);  
serial1.write(ch1);
serial1.write(ch2);
serial1.write(ch3);
serial1.write(ch4);
serial1.write(ch5);
serial1.write(ch6);
serial1.write(ch7);
serial1.write(ch8);

}
