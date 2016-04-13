//We always have to include the library
#include "LedControlMS.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,6);
  /* and clear the display */
  lc.clearDisplay(0);
}

void ScrollOut(int offset,  byte* letter) 
{  
  for(int i = offset; i <= 7; i++)
  {    
    int col = i;
    lc.setRow(0,col,letter[i-offset]);       
  }
}

void ScrollIn(int offset, byte* letter) 
{
  
  for(int i = 0;i <= offset; i++)
  {    
    int col = offset-i;
    lc.setRow(0,col,letter[7-i]);       
  }
}

void drawLetter(byte* letterOut, byte* letterIn)
{
  for(int offset = 0; offset < 8; offset++)
  {
     ScrollOut(offset, letterOut);
     ScrollIn(offset, letterIn);
     delay(delaytime);     
  }  
}


void loop() { 
  /* here is the data for the characters */
  byte r[8]={B00000000,B00000000,B00110010,B01001100,B01001000,B01111110,B01000000,B00000000};
  byte i[8]={B00000000,B01000010,B01000010,B01111110,B01111110,B01000010,B01000010,B00000000};
  byte s[8]={B00000000,B00000000,B01000100,B01001010,B01001010,B01001010,B00110010,B00000000};
  byte h[8]={B00000000,B00000000,B01111110,B00001000,B00001000,B00001000,B01111110,B00000000};
  byte u[8]={B00000000,B00000000,B01111100,B00000010,B00000010,B00000010,B01111100,B00000000};
  byte space[8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
  drawLetter(r, i);
  drawLetter(i, s);
  drawLetter(s, h);
  drawLetter(h, u);
  drawLetter(u, space);
  drawLetter(space,i);
  drawLetter(i,s);
  drawLetter(s,space);
  drawLetter(space,r);
  //writeRishuOnMatrix();
}
