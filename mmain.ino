

int command_array2[3]={125,125,1};
int command_cnt2;

int command_array1[10]={90,80,150,150,150,150,150,150,150,150};
int command_cnt1;

int ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8;
int acc_x,acc_y;
int c_mag, c_acc;
int switch1;
int sn=0;


int Position101, Position102, Position103, Position104, Position105, Position106, Position107, Position108, Position10, Position11, Position14;

int Load101, Load102, Load103, Load104, Load105, Load106, Load107, Load108;

int mode = 0;

int spd1=0;
int spd2=0;

Dynamixel Dxl(3);

void setup() {
  // put your setup code here, to run once:
Serial2.begin(9600);
Serial1.begin(9600);
SerialUSB.begin();
Dxl.begin(3);

Dxl.jointMode(101);
Dxl.jointMode(102);
Dxl.jointMode(103);
Dxl.jointMode(104);
Dxl.jointMode(105);
Dxl.jointMode(106);
Dxl.jointMode(107);
Dxl.jointMode(108);
Dxl.jointMode(10);
Dxl.jointMode(11);
Dxl.jointMode(14);

Dxl.writeWord(1, 8, 0); 
Dxl.writeWord(2, 8, 0); 
Dxl.writeWord(3, 8, 0); 
Dxl.writeWord(4, 8, 0); 
Dxl.writeWord(5, 8, 0); 
Dxl.writeWord(6, 8, 0); 
Dxl.writeWord(7, 8, 0); 
Dxl.writeWord(9, 8, 0); 



}

/*
Dxl.writeWord(ID_NUM, 32, 1023);   //wheel  <-
Dxl.writeWord(ID_NUM, 32, 1023 | 0x400);  ->

Dxl.setPosition(ID_NUM,0,100); jointmode id_num, position, velocity 


*/
void loop() {
readrx();  
Position();
Load();
rx_monitor();
//motor_monitor();

if(mode>=1);
{
Serial2.write(mode);
}

if(switch1==0)
{
  sn++;
}



if(ch5<130)
{
    
    if(ch6>170)
    {
      //mode select
      mode_select();
      sn=0;
    }
    
    else if(ch6<130)
    {
      move_cam();
      //moving 
      if(mode==1)
      {
        move1();
      }
      
      else if(mode==2)
      {
        move1();
      }
      
     else if(mode==3)
      {
        move1();
      }
      
      else if(mode==4)
      {
        move1();
      }
      
      else if(mode==5)
      {
        move1();
      }
      
      else if(mode==6)
      {
        move1();
      }
      
      else if(mode==7)
      {
        move2();
      }
      
      else if(mode==8)
      {
        move1();
      }
      
      else if(mode==9)
      {
        move2();
      }
      
      
      
      
    }
}


else if (ch5>170)
{
  Dxl.writeWord(101, 24, 0);
  Dxl.writeWord(102, 24, 0);
  Dxl.writeWord(103, 24, 0);
  Dxl.writeWord(104, 24, 0);
  Dxl.writeWord(105, 24, 0);
  Dxl.writeWord(106, 24, 0);
}




}




//////////////////////////////////////////////////////////////////////////////////////////////////

//                   R O O P       E N D

///////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//M O V E     C A M

void move_cam()
{
  
  if(sn>0)
  {
                if(mode == 1)
                {
                 
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                
                  
                  
                }
                
                else if(mode==2)
                {
                  
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                  
                }
                
                else if(mode==3)
                {
                 
                 Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100); 
                }
                
                else if(mode==4)
                {
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                }
                
                else if(mode==5)
                {
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                }
                
                else if(mode==6)
                {
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                }
                
                else if(mode==7)
                {
                  Dxl.setPosition(10,512,100);
                  Dxl.setPosition(11,((c_acc*4)),100);
                  Dxl.setPosition(14,(c_mag*4),100);
                }
                
                else if(mode==8)
                {
                  Dxl.setPosition(10,((c_mag*4)-307),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                }
                
                else if(mode==9)
                {
                  Dxl.setPosition(10,(c_mag*4),100);
                  Dxl.setPosition(11,((c_acc*4)-350),100);
                  Dxl.setPosition(14,512,100);
                }
  
  
  }
  
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void Position()
{
  int PositionL101 = Dxl.readByte(101, 36);
  int PositionH101 = Dxl.readByte(101, 37);
   
   Position101 = ((PositionH101*256)+PositionL101);
   
   int PositionL102 = Dxl.readByte(102, 36);
  int PositionH102 = Dxl.readByte(102, 37);
   
   Position102 = ((PositionH102*256)+PositionL102);
   
   int PositionL103 = Dxl.readByte(103, 36);
  int PositionH103 = Dxl.readByte(103, 37);
   
   Position103 = ((PositionH103*256)+PositionL103);
   
   int PositionL104 = Dxl.readByte(104, 36);
  int PositionH104 = Dxl.readByte(104, 37);
   
   Position104 = ((PositionH104*256)+PositionL104);
   
   int PositionL105 = Dxl.readByte(105, 36);
  int PositionH105 = Dxl.readByte(105, 37);
   
   Position105 = ((PositionH105*256)+PositionL105);
   
   int PositionL106 = Dxl.readByte(106, 36);
  int PositionH106 = Dxl.readByte(106, 37);
   
   Position106 = ((PositionH106*256)+PositionL106);
   
   int PositionL107 = Dxl.readByte(107, 36);
  int PositionH107 = Dxl.readByte(107, 37);
   
   Position107 = ((PositionH107*256)+PositionL107);
   
   int PositionL108 = Dxl.readByte(108, 36);
  int PositionH108 = Dxl.readByte(108, 37);
   
   Position108 = ((PositionH108*256)+PositionL108);
   
   int PositionL10 = Dxl.readByte(10, 36);
  int PositionH10 = Dxl.readByte(10, 37);
   
   Position10 = ((PositionH10*256)+PositionL10);
   
   int PositionL11 = Dxl.readByte(11, 36);
  int PositionH11 = Dxl.readByte(11, 37);
   
   Position11 = ((PositionH11*256)+PositionL11);
   
   int PositionL14 = Dxl.readByte(14, 36);
  int PositionH14 = Dxl.readByte(14, 37);
   
   Position14 = ((PositionH14*256)+PositionL14);
   
   

}

void Load()
{
  int LoadL101 = Dxl.readByte(101, 40);
  int LoadH101 = Dxl.readByte(101, 41);
   
   Load101 = ((LoadH101*256)+LoadL101);
   
   int LoadL102 = Dxl.readByte(102, 40);
  int LoadH102 = Dxl.readByte(102, 41);
   
   Load102 = ((LoadH102*256)+LoadL102);
   
   int LoadL103 = Dxl.readByte(103, 40);
  int LoadH103 = Dxl.readByte(103, 41);
   
   Load103 = ((LoadH103*256)+LoadL103);
   
   int LoadL104 = Dxl.readByte(104, 40);
  int LoadH104 = Dxl.readByte(104, 41);
   
   Load104 = ((LoadH104*256)+LoadL104);
   
   int LoadL105 = Dxl.readByte(105, 40);
  int LoadH105 = Dxl.readByte(105, 41);
   
   Load105 = ((LoadH105*256)+LoadL105);
   
   int LoadL106 = Dxl.readByte(106, 40);
  int LoadH106 = Dxl.readByte(106, 41);
   
   Load106 = ((LoadH106*256)+LoadL106);
   
   int LoadL107 = Dxl.readByte(107, 40);
  int LoadH107 = Dxl.readByte(107, 41);
   
   Load107 = ((LoadH107*256)+LoadL107);
   
   int LoadL108 = Dxl.readByte(108, 40);
  int LoadH108 = Dxl.readByte(108, 41);
   
   Load108 = ((LoadH108*256)+LoadL108);
   
   

}

void motor_monitor()
{
  SerialUSB.print(" -1- ");
SerialUSB.print(Position101);  
SerialUSB.print(" -2- ");
SerialUSB.print(Position102);  
SerialUSB.print(" -3- ");
SerialUSB.print(Position103);  
SerialUSB.print(" -4- ");
SerialUSB.print(Position104);  
SerialUSB.print(" -5- ");
SerialUSB.print(Position105);  
SerialUSB.print(" -6- ");
SerialUSB.print(Position106);  
SerialUSB.print(" -7- ");
SerialUSB.print(Position107);  
SerialUSB.print(" -8- ");
SerialUSB.print(Position108);  
SerialUSB.print(" -10- ");
SerialUSB.print(Position10); 
SerialUSB.print(" -1- ");
SerialUSB.print(Load101);  
SerialUSB.print(" -2- ");
SerialUSB.print(Load102);  
SerialUSB.print(" -3- ");
SerialUSB.print(Load103);  
SerialUSB.print(" -4- ");
SerialUSB.print(Load104);  
SerialUSB.print(" -5- ");
SerialUSB.print(Load105);  
SerialUSB.print(" -6- ");
SerialUSB.print(Load106);  
SerialUSB.print(" -7- ");
SerialUSB.print(Load107);  
SerialUSB.print(" -8- ");
SerialUSB.println(Load108);  


}

void rx_monitor()
{
  SerialUSB.print(acc_x);
SerialUSB.print(" - ");
SerialUSB.print(acc_y);
SerialUSB.print(" - ");
SerialUSB.print(ch1);
SerialUSB.print(" - ");
SerialUSB.print(ch2);
SerialUSB.print(" - ");
SerialUSB.print(ch3);
SerialUSB.print(" - ");
SerialUSB.print(ch4);
SerialUSB.print(" - ");
SerialUSB.print(ch5);
SerialUSB.print(" - ");
SerialUSB.print(ch6);
SerialUSB.print(" - ");
SerialUSB.print(ch7);
SerialUSB.print(" - ");
SerialUSB.print(ch8);
SerialUSB.print(" - ");
SerialUSB.print(c_mag);
SerialUSB.print(" - ");
SerialUSB.print(c_acc);
SerialUSB.print(" - ");
SerialUSB.print(switch1);
SerialUSB.print(" - ");
SerialUSB.println(mode);
}

void readrx()
{
  while (Serial2.available()) {
    // get the new byte:
    int inChar2 = (unsigned char)Serial2.read();
    // add it to the inputString:
    if(inChar2== 253)
    {
     
       command_cnt2 = 0;
    }
    else
    {
      command_array2[command_cnt2] =inChar2;
     

       command_cnt2++;
    }
  }
  
  
  

  
while (Serial1.available()) {
    // get the new byte:
    int inChar1 = (unsigned char)Serial1.read();
    // add it to the inputString:
    if(inChar1== 253)
    {
     
       command_cnt1 = 0;
    }
    else
    {
      command_array1[command_cnt1] =inChar1;
     

       command_cnt1++;
    }
  }  

c_mag=command_array2[0];  
c_acc=command_array2[1];  
switch1=command_array2[2];

acc_x=command_array1[0];
acc_y=command_array1[1];
ch1=command_array1[2];
ch2=command_array1[3];
ch3=command_array1[4];
ch4=command_array1[5];
ch5=command_array1[6];
ch6=command_array1[7];
ch7=command_array1[8];
ch8=command_array1[9];
}
///////////////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////////////////////////

void mode_select()
{
  if( (ch3>170)&&(ch1<120) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode1_t();
       mode=1;
     }
  }
  
  else if( (ch3>170)&&((ch1>140)&&(ch1<160)) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode2_t();
       mode=2;
     }
  }
  
  else if( (ch3>170)&&(ch1>170) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode3_t();
       mode=3;
     }
  }
  
  else if( ((ch3>140)&&(ch3<150))&&(ch1<120) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode4_t();
       mode=4;
     }
  }
  
  else if( ((ch3>140)&&(ch3<150))&&((ch1>140)&&(ch1<160)) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode5_t();
       mode=5;
     }
  }
  
  else if( ((ch3>140)&&(ch3<150))&&(ch1>170) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode6_t();
       mode=6;
     }
  }
  
  else if( (ch3<120)&&(ch1<120) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode7_t();
       mode=7;
     }
  }
  
  else if( (ch3<120)&&((ch1>140)&&(ch1<160)) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       
       mode8_t();
       mode=8;
     }
  }
  
  else if( (ch3<120)&&(ch1>170) )
  {
     if( (ch2>170)&&(ch4<120) )
     {
       mode9_t();
       mode=9;
     }
  }
  
}


void mode1_t()
{
  int n=1;
 
 
    
      while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
    
  
  
  if (mode==8)
  {   
      Dxl.setPosition(101,3405,100);
      Dxl.setPosition(102,3414,100); 
      Dxl.setPosition(104,3413,100);
      Dxl.setPosition(105,3409,100);
      
      
      Dxl.writeWord(1, 32, 300 | 0x400); 
       Dxl.writeWord(2, 32, 300); 
       Dxl.writeWord(3, 32, 300 | 0x400); 
       Dxl.writeWord(4, 32, 300); 
       Dxl.writeWord(5, 32, 300 | 0x400); 
       Dxl.writeWord(6, 32, 300); 
       Dxl.writeWord(7, 32, 300 | 0x400); 
       Dxl.writeWord(9, 32, 300); 
       
       
       delay(2000);
       
      Dxl.setPosition(103,2048,50);
      Dxl.setPosition(106,2048,50);
       
     delay(2000);
     
       Dxl.writeWord(1, 32, 0); 
       Dxl.writeWord(2, 32, 0); 
       Dxl.writeWord(3, 32, 0); 
       Dxl.writeWord(4, 32, 0); 
       Dxl.writeWord(5, 32, 0); 
       Dxl.writeWord(6, 32, 0); 
       Dxl.writeWord(7, 32, 0); 
       Dxl.writeWord(9, 32, 0);
       
       
  }
  else if(mode==9)
  {
      Dxl.setPosition(101,3071,50);
      Dxl.setPosition(102,1024,50); 
      Dxl.setPosition(103,2048,50);
      Dxl.setPosition(104,3071,50);
      Dxl.setPosition(105,1024,50);
      Dxl.setPosition(106,2048,50);
    
    
  }
  
  else if(mode==6)
  {
    
    
  }
  else if(mode==7)
  {
     Dxl.setPosition(103,2048,100);
     Dxl.setPosition(106,2048,100);
     delay(1000);
      Dxl.setPosition(101,3072,100);
      Dxl.setPosition(102,1024,100);
      Dxl.setPosition(103,1024,100);
      Dxl.setPosition(104,3072,100);
      Dxl.setPosition(105,1024,100);
      Dxl.setPosition(106,1024,100);
    int n=1;
    int m=1;  
      while(n+m)
    {
      int PositionL102 = Dxl.readByte(102, 36);
      int PositionH102 = Dxl.readByte(102, 37);
      int PositionL105 = Dxl.readByte(105, 36);
      int PositionH105 = Dxl.readByte(105, 37);
   
       Position102 = ((PositionH102*256)+PositionL102);
       Position105 = ((PositionH105*256)+PositionL105);
       
       
    if(Position102>1030)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position105>1030)
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
    
      Dxl.setPosition(107,2048,100);
      Dxl.setPosition(108,2048,100);
    n=1;
    m=1;
    
      while(n+m)
    {
      int PositionL107 = Dxl.readByte(107, 36);
      int PositionH107 = Dxl.readByte(107, 37);
      int PositionL108 = Dxl.readByte(108, 36);
      int PositionH108 = Dxl.readByte(108, 37);
   
       Position107 = ((PositionH107*256)+PositionL107);
       Position108 = ((PositionH108*256)+PositionL108);
       
       
    if(Position108<2040)
    {
     Dxl.writeWord(1, 32, 1023 | 0x400); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 | 0x400); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position107>2060)
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 ); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 ); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
      
     
  }
  
  
if(mode<8)
{ 
 Dxl.setPosition(101,2048,100);
 Dxl.setPosition(102,2048,100);
 Dxl.setPosition(103,2048,100);
 Dxl.setPosition(104,2048,100);
 Dxl.setPosition(105,2048,100);
 Dxl.setPosition(106,2048,100);
 Dxl.setPosition(107,2048,100);
 Dxl.setPosition(108,2048,100);
 
 Dxl.writeWord(1, 32, 1023 | 0x400); 
 Dxl.writeWord(2, 32, 1023); 
 Dxl.writeWord(3, 32, 1023 | 0x400); 
 Dxl.writeWord(4, 32, 1023); 
 Dxl.writeWord(5, 32, 1023 | 0x400); 
 Dxl.writeWord(6, 32, 1023); 
 Dxl.writeWord(7, 32, 1023 | 0x400); 
 Dxl.writeWord(9, 32, 1023); 
 delay(1000);
 Dxl.writeWord(1, 32, 0); 
 Dxl.writeWord(2, 32, 0); 
 Dxl.writeWord(3, 32, 0); 
 Dxl.writeWord(4, 32, 0); 
 Dxl.writeWord(5, 32, 0); 
 Dxl.writeWord(6, 32, 0); 
 Dxl.writeWord(7, 32, 0); 
 Dxl.writeWord(9, 32, 0); 
}



else if(mode==8)
{
  Dxl.setPosition(101,2048,100);
 Dxl.setPosition(102,2048,100);
 Dxl.setPosition(103,2048,100);
 Dxl.setPosition(104,2048,100);
 Dxl.setPosition(105,2048,100);
 Dxl.setPosition(106,2048,100);
 Dxl.setPosition(107,2048,100);
 Dxl.setPosition(108,2048,100);

}

      Dxl.setPosition(10,205,100);
      Dxl.setPosition(11,205,100);
      Dxl.setPosition(14,512,100);
   
}

void mode2_t()
{
  int n=1;
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
          Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
      
  if(mode==4)
  {
    int n=1;
    int m=1;
    
     Dxl.setPosition(101,1024,100);
     Dxl.setPosition(102,2048,100);
     Dxl.setPosition(103,3072,100);
     Dxl.setPosition(104,1024,100);
     Dxl.setPosition(105,2048,100);
     Dxl.setPosition(106,3072,100);
     
     while(n+m)
    {
      int PositionL102 = Dxl.readByte(102, 36);
      int PositionH102 = Dxl.readByte(102, 37);
      int PositionL105 = Dxl.readByte(105, 36);
      int PositionH105 = Dxl.readByte(105, 37);
   
       Position102 = ((PositionH102*256)+PositionL102);
       Position105 = ((PositionH105*256)+PositionL105);
       
       
    if(Position102>2055)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position105>2055)
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
     
   Dxl.setPosition(101,2048,100);
   Dxl.setPosition(104,2048,100);  
   n=1;
   m=1;
 
   while(n+m)
    {
      int PositionL101 = Dxl.readByte(101, 36);
      int PositionH101 = Dxl.readByte(101, 37);
      int PositionL104 = Dxl.readByte(104, 36);
      int PositionH104 = Dxl.readByte(104, 37);
   
       Position101 = ((PositionH101*256)+PositionL101);
       Position104 = ((PositionH104*256)+PositionL104);
       
       
    if(Position101<2040)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position104<2040)
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }  
     
  }
  
  else
  {
     Dxl.setPosition(101,1024,100);
     Dxl.setPosition(102,3072,100);
     Dxl.setPosition(103,2048,100);
     Dxl.setPosition(104,1024,100);
     Dxl.setPosition(105,3072,100);
     Dxl.setPosition(106,2048,100);
     Dxl.setPosition(107,2048,100);
     Dxl.setPosition(108,2048,100);
  }
   
}

void mode3_t()
{
  int n=1;
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
      
 if(mode==1)
 {
   
    int n=1;
    
    mode2_t();
    Dxl.setPosition(10,819,100);
    
    delay(2000);
    
    Dxl.setPosition(103,3072,100);
    Dxl.setPosition(106,3072,100);
    
    while(n)
    {
      int PositionL103 = Dxl.readByte(103, 36);
      int PositionH103 = Dxl.readByte(103, 37);
   
       Position103 = ((PositionH103*256)+PositionL103);
    if(Position103<3072)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     n=0; 
    }
    }
    
 }
 
 else if(mode==2)
 {
   
   int n=1;
    Dxl.setPosition(103,3072,100);
    Dxl.setPosition(106,3072,100);
    
    while(n)
    {
      int PositionL103 = Dxl.readByte(103, 36);
      int PositionH103 = Dxl.readByte(103, 37);
   
       Position103 = ((PositionH103*256)+PositionL103);
    if(Position103<3072)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     n=0; 
    }
    }
   
 }
 Dxl.setPosition(10,205,100);
    Dxl.setPosition(11,205,100);
    Dxl.setPosition(14,512,100);
}

void mode4_t()
{
  int n=1;
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
      
  if(mode==3)
  {
        Dxl.setPosition(101,2048,100);
        Dxl.setPosition(104,2048,100);
  }
  
  else
  {
      mode3_t();
      Dxl.setPosition(10,819,100);
      
      Dxl.setPosition(101,2048,100);
      Dxl.setPosition(104,2048,100);
  }

 Dxl.setPosition(10,205,100);
    Dxl.setPosition(11,205,100);
    Dxl.setPosition(14,512,100);
  
  
  delay(2000);
  Dxl.writeWord(104, 24, 0);
  Dxl.writeWord(101, 24, 0);
}

void mode5_t()
{
  int n=1;
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
      
   n=1;
   mode4_t();
   Dxl.setPosition(10,819,100);
   
   
   
   Dxl.setPosition(101,1545,100);
   Dxl.setPosition(102,3400,100);
   Dxl.setPosition(103,3400,100);
   Dxl.setPosition(104,2060,100);
   Dxl.setPosition(105,2560,100);
   Dxl.setPosition(106,2560,100);
   
   while(n)
    {
      int PositionL102 = Dxl.readByte(102, 36);
      int PositionH102 = Dxl.readByte(102, 37);
 
   
       Position102 = ((PositionH102*256)+PositionL102);
       
       
    if(Position102<3390)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     n=0; 
    }
    }
    delay(1000);
    Dxl.writeWord(104, 24, 0);
  
    Dxl.setPosition(10,205,100);
    Dxl.setPosition(11,205,100);
    Dxl.setPosition(14,512,100);
  
}

void mode6_t()
{
  int n=1;
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
   n =1;
   int m =1;
   
  if(mode=!1)
  {
    mode1_t();
  }
  
  Dxl.setPosition(101,3072,100);
  Dxl.setPosition(102,1024,100);
  Dxl.setPosition(103,1024,100);
  Dxl.setPosition(104,3072,100);
  Dxl.setPosition(105,1024,100);
  Dxl.setPosition(106,1024,100);
  
  while(n+m)
    {
      int PositionL102 = Dxl.readByte(102, 36);
      int PositionH102 = Dxl.readByte(102, 37);
      int PositionL105 = Dxl.readByte(105, 36);
      int PositionH105 = Dxl.readByte(105, 37);
   
       Position102 = ((PositionH102*256)+PositionL102);
       Position105 = ((PositionH105*256)+PositionL105);
       
       
    if(Position102>1030)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position105>1030)
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);

    Dxl.setPosition(10,205,100);
    Dxl.setPosition(11,205,100);
    Dxl.setPosition(14,512,100);  
  
}

void mode7_t()
{
   int n=1;
   
    while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
    n=1;
    int m=1;
      mode6_t();
      Dxl.setPosition(10,819,100);
      
      Dxl.setPosition(108,1024,100);
      Dxl.setPosition(107,3072,100);
  
     while(n+m)
    {
      int PositionL107 = Dxl.readByte(107, 36);
      int PositionH107 = Dxl.readByte(107, 37);
      int PositionL108 = Dxl.readByte(108, 36);
      int PositionH108 = Dxl.readByte(108, 37);
   
       Position107 = ((PositionH107*256)+PositionL107);
       Position108 = ((PositionH108*256)+PositionL108);
       
       
    if(Position108>1024)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 ); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 ); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position107<3072)
    {
     Dxl.writeWord(5, 32, 1023 | 0x400); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 | 0x400); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
    
   Dxl.setPosition(101,2048,100);
   Dxl.setPosition(102,2048,100);
   Dxl.setPosition(103,2048,100);
   Dxl.setPosition(104,2048,100);
   Dxl.setPosition(105,2048,100);
   Dxl.setPosition(106,2048,100);
   
   Dxl.writeWord(1, 32, 400 | 0x400); 
   Dxl.writeWord(2, 32, 400);    
   Dxl.writeWord(3, 32, 400 | 0x400); 
   Dxl.writeWord(4, 32, 400); 
   Dxl.writeWord(5, 32, 400 | 0x400); 
   Dxl.writeWord(6, 32, 400); 
   Dxl.writeWord(7, 32, 400 | 0x400); 
   Dxl.writeWord(9, 32, 400); 
   delay(1500);
   Dxl.writeWord(1, 32, 0); 
   Dxl.writeWord(2, 32, 0); 
   Dxl.writeWord(3, 32, 0); 
   Dxl.writeWord(4, 32, 0); 
   Dxl.writeWord(5, 32, 0); 
   Dxl.writeWord(6, 32, 0); 
   Dxl.writeWord(7, 32, 0); 
   Dxl.writeWord(9, 32, 0); 
   
   Dxl.setPosition(103,1200,50);
   Dxl.setPosition(106,1200,50);
   
   delay(1000);
    
   Dxl.setPosition(101,2400,100);
   Dxl.setPosition(102,1800,100);
   Dxl.setPosition(104,2400,100);
   Dxl.setPosition(105,1800,100);
 
  Dxl.setPosition(10,512,100);
  Dxl.setPosition(11,512,100);
  Dxl.setPosition(14,512,100);
  
  
}

void mode8_t()
{
  int n=1;
  
  
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
  
      
   Dxl.setPosition(101,3405,100);
   Dxl.setPosition(102,3414,100);
   Dxl.setPosition(103,2048,100);
   Dxl.setPosition(104,3413,100);
   Dxl.setPosition(105,3409,100);
   Dxl.setPosition(106,2048,100);
   Dxl.setPosition(107,2048,100);
   Dxl.setPosition(108,2048,100);
   
   delay(2000);
   
   Dxl.setPosition(103,3000,100);
    Dxl.setPosition(106,2900,100);
    n=1;
    int m=1;
    
    while(n)
    {
      int PositionL103 = Dxl.readByte(103, 36);
      int PositionH103 = Dxl.readByte(103, 37);
      int PositionL105 = Dxl.readByte(105, 36);
      int PositionH105 = Dxl.readByte(105, 37);
   
       Position103 = ((PositionH103*256)+PositionL103);
       Position105 = ((PositionH105*256)+PositionL105);
    if(Position103<3000)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    else if(Position105<3072)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     n=0; 
    }
    }
    
    Dxl.setPosition(101,2048,100);
   Dxl.setPosition(102,2048,100);
   Dxl.setPosition(104,2048,100);
   Dxl.setPosition(105,2048,100);
   
   
   delay(2000);
   
   n=1;
   m=1;
  /*
    while(n+m)
    {
      int PositionL102 = Dxl.readByte(102, 36);
      int PositionH102 = Dxl.readByte(102, 37);
      int PositionL105 = Dxl.readByte(105, 36);
      int PositionH105 = Dxl.readByte(105, 37);
   
       Position102 = ((PositionH102*256)+PositionL102);
       Position105 = ((PositionH105*256)+PositionL105);
       
       
    if((Position102>2065)&&n==1)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023  | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023  | 0x400); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0 ); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if((Position105<2065)&&(m==1))
    {
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    }
 */  

     Dxl.writeWord(1, 32, 400 ); 
     Dxl.writeWord(2, 32, 400 | 0x400); 
     Dxl.writeWord(3, 32, 400 ); 
     Dxl.writeWord(4, 32, 400 | 0x400); 
     Dxl.writeWord(5, 32, 300 ); 
     Dxl.writeWord(6, 32, 300 | 0x400); 
     Dxl.writeWord(7, 32, 400 ); 
     Dxl.writeWord(9, 32, 400 | 0x400); 

    delay(1500);
  
    Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
   
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);

    delay(500);
     
    
   Dxl.setPosition(10,205,100);
    Dxl.setPosition(11,205,100);
    Dxl.setPosition(14,512,100);
  
}

void mode9_t()
{
  
  int n=1;
   while(n)
      {
         int PositionL10 = Dxl.readByte(10, 36);
         int PositionH10 = Dxl.readByte(10, 37);
       
         Position10 = ((PositionH10*256)+PositionL10);
         
         Dxl.setPosition(10,819,100);
          Dxl.setPosition(11,205,100);
          Dxl.setPosition(14,512,100);
          
          if(Position10>800)
          {
            n=0;
          }
      }
      
  
    n=1;
   int m=1;
   
   Dxl.setPosition(101,2815,100);
   Dxl.setPosition(102,900,100);
   
   Dxl.setPosition(104,2815,100);
   Dxl.setPosition(105,900,100);
   
   delay(1000);
   
   Dxl.setPosition(103,2048,100);
   Dxl.setPosition(106,2048,100);
  
   
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 | 0x400); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 | 0x400); 
     Dxl.writeWord(5, 32, 1023 ); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 ); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 

    delay(2000);
  
    Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
   
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     
     Dxl.setPosition(108,1024,100);
      Dxl.setPosition(107,3072,100);
  
     while(n+m)
    {
      int PositionL107 = Dxl.readByte(107, 36);
      int PositionH107 = Dxl.readByte(107, 37);
      int PositionL108 = Dxl.readByte(108, 36);
      int PositionH108 = Dxl.readByte(108, 37);
   
       Position107 = ((PositionH107*256)+PositionL107);
       Position108 = ((PositionH108*256)+PositionL108);
       
       
    if(Position108>1024)
    {
     Dxl.writeWord(1, 32, 1023 ); 
     Dxl.writeWord(2, 32, 1023 ); 
     Dxl.writeWord(3, 32, 1023 ); 
     Dxl.writeWord(4, 32, 1023 ); 
     
    }
    else
    {
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     n=0; 
    }
    
    
    if(Position107<3072)
    {
     Dxl.writeWord(5, 32, 1023 | 0x400); 
     Dxl.writeWord(6, 32, 1023 | 0x400); 
     Dxl.writeWord(7, 32, 1023 | 0x400); 
     Dxl.writeWord(9, 32, 1023 | 0x400); 
    }
    
    else
    {
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
     m=0;
    }
    } 
    
    
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
    
    Dxl.setPosition(103,1100,100);
    Dxl.setPosition(106,1100,100); 

   
 
  
}


void move1()
{
  
  if(((ch1<=150)&&(ch1>=140))&&((ch3<=150)&&(ch3>=140)))
  {
    
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     
  }
  
  else if((ch1<=150)&&(ch1>=140))
  {
           if(ch3>150)
           {   
               spd1=((ch3-150)*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               Dxl.writeWord(1, 32, spd1 | 0x400); 
               Dxl.writeWord(2, 32, spd1); 
               Dxl.writeWord(3, 32, spd1 | 0x400); 
               Dxl.writeWord(4, 32, spd1); 
               Dxl.writeWord(5, 32, spd1); 
               Dxl.writeWord(6, 32, spd1 | 0x400); 
               Dxl.writeWord(7, 32, spd1); 
               Dxl.writeWord(9, 32, spd1 | 0x400);
               
               
           }
           
           else if(ch3<140)
           {
               spd1=(((ch3-140)*(-1))*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               
               Dxl.writeWord(1, 32, spd1); 
               Dxl.writeWord(2, 32, spd1 | 0x400); 
               Dxl.writeWord(3, 32, spd1); 
               Dxl.writeWord(4, 32, spd1 | 0x400); 
               Dxl.writeWord(5, 32, spd1 | 0x400); 
               Dxl.writeWord(6, 32, spd1); 
               Dxl.writeWord(7, 32, spd1 | 0x400); 
               Dxl.writeWord(9, 32, spd1);
             
           }
     
  }
  
  else if((ch3<=150)&&(ch3>=140))
  {
           if(ch1>150)
           {   
               spd2=((ch1-150)*35);
               if(spd2>1023)
               {
                 spd2=1023;
               }
               Dxl.writeWord(1, 32, (spd2*95)/100 | 0x400); 
               Dxl.writeWord(2, 32, spd2 | 0x400); 
               Dxl.writeWord(3, 32, (spd2*95)/100 | 0x400); 
               Dxl.writeWord(4, 32, spd2 | 0x400); 
               Dxl.writeWord(5, 32, spd2 | 0x400); 
               Dxl.writeWord(6, 32, (spd2*95)/100 | 0x400); 
               Dxl.writeWord(7, 32, spd2 | 0x400); 
               Dxl.writeWord(9, 32, (spd2*95)/100 | 0x400);
           }
           
           else if(ch1<140)
           {
               spd1=(((ch1-140)*(-1))*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               Dxl.writeWord(1, 32, (spd2*95)/100 ); 
               Dxl.writeWord(2, 32, spd2 ); 
               Dxl.writeWord(3, 32, (spd2*95)/100 ); 
               Dxl.writeWord(4, 32, spd2 ); 
               Dxl.writeWord(5, 32, spd2 ); 
               Dxl.writeWord(6, 32, (spd2*95)/100 ); 
               Dxl.writeWord(7, 32, spd2 ); 
               Dxl.writeWord(9, 32, (spd2*95)/100 );
             
           }
     
  }
  
  
}

void move2()
{
  if(((ch1<=150)&&(ch1>=140))&&((ch3<=150)&&(ch3>=140)))
  {
    
     Dxl.writeWord(1, 32, 0); 
     Dxl.writeWord(2, 32, 0); 
     Dxl.writeWord(3, 32, 0); 
     Dxl.writeWord(4, 32, 0); 
     Dxl.writeWord(5, 32, 0); 
     Dxl.writeWord(6, 32, 0); 
     Dxl.writeWord(7, 32, 0); 
     Dxl.writeWord(9, 32, 0);
     
  }
  
  else if((ch1<=150)&&(ch1>=140))
  {
           if(ch3>150)
           {   
               spd1=((ch3-150)*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               
               Dxl.writeWord(1, 32, spd1 | 0x400); 
               Dxl.writeWord(2, 32, spd1 ); 
               Dxl.writeWord(3, 32, spd1 | 0x400); 
               Dxl.writeWord(4, 32, spd1 ); 
               Dxl.writeWord(5, 32, spd1 | 0x400); 
               Dxl.writeWord(6, 32, spd1); 
               Dxl.writeWord(7, 32, spd1 | 0x400); 
               Dxl.writeWord(9, 32, spd1);
           }
           
           else if(ch3<140)
           {
               spd1=(((ch3-140)*(-1))*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               Dxl.writeWord(1, 32, spd1 ); 
               Dxl.writeWord(2, 32, spd1 | 0x400); 
               Dxl.writeWord(3, 32, spd1 ); 
               Dxl.writeWord(4, 32, spd1 | 0x400); 
               Dxl.writeWord(5, 32, spd1); 
               Dxl.writeWord(6, 32, spd1 | 0x400); 
               Dxl.writeWord(7, 32, spd1); 
               Dxl.writeWord(9, 32, spd1 | 0x400);
             
           }
     
  }
  
  else if((ch3<=150)&&(ch3>=140))
  {
           if(ch1>150)
           {   
               spd2=((ch1-150)*35);
               if(spd2>1023)
               {
                 spd2=1023;
               }
               Dxl.writeWord(1, 32, spd2 ); 
               Dxl.writeWord(2, 32, spd2 | 0x400); 
               Dxl.writeWord(3, 32, spd2 ); 
               Dxl.writeWord(4, 32, spd2 | 0x400); 
               Dxl.writeWord(5, 32, spd2 | 0x400); 
               Dxl.writeWord(6, 32, spd2 ); 
               Dxl.writeWord(7, 32, spd2 | 0x400); 
               Dxl.writeWord(9, 32, spd2 );
           }
           
           else if(ch1<140)
           {
               spd1=(((ch1-140)*(-1))*35);
               if(spd1>1023)
               {
                 spd1=1023;
               }
               Dxl.writeWord(1, 32, spd2 | 0x400); 
               Dxl.writeWord(2, 32, spd2 ); 
               Dxl.writeWord(3, 32, spd2 | 0x400); 
               Dxl.writeWord(4, 32, spd2 ); 
               Dxl.writeWord(5, 32, spd2 ); 
               Dxl.writeWord(6, 32, spd2 | 0x400); 
               Dxl.writeWord(7, 32, spd2 ); 
               Dxl.writeWord(9, 32, spd2 | 0x400);
             
           }
     
  }
  
}
