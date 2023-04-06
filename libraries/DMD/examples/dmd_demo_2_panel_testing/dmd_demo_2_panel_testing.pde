/*--------------------------------------------------------------------------------------

 dmd_demo.cpp 
   Demo and example project for the Freetronics DMD, a 512 LED matrix display
   panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 See http://www.freetronics.com/dmd for resources and a getting started guide.

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.

 USAGE NOTES
 -----------

 - Place the DMD library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Get the TimerOne library from here: http://code.google.com/p/arduino-timerone/downloads/list
   or download the local copy from the DMD library page (which may be older but was used for this creation)
   and place the TimerOne library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Restart the IDE.
 - In the Arduino IDE, you can open File > Examples > DMD > dmd_demo, or dmd_clock_readout, and get it
   running straight away!

 * The DMD comes with a pre-made data cable and DMDCON connector board so you can plug-and-play straight
   into any regular size Arduino Board (Uno, Freetronics Eleven, EtherTen, USBDroid, etc)
  
 * Please note that the Mega boards have SPI on different pins, so this library does not currently support
   the DMDCON connector board for direct connection to Mega's, please jumper the DMDCON pins to the
   matching SPI pins on the other header on the Mega boards.

 This example code is in the public domain.
 The DMD library is open source (GPL), for more see DMD.cpp and DMD.h

--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

//Fire up the DMD library as dmd
DMD dmd(2,1);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   byte b;
   
   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
   dmd.drawChar(  0,  2, '2', GRAPHICS_NORMAL );
   dmd.drawChar(  7,  2, '3', GRAPHICS_NORMAL );
   dmd.drawChar( 16,  2, '4', GRAPHICS_NORMAL );
   dmd.drawChar( 24,  2, '5', GRAPHICS_NORMAL );
   dmd.drawChar( 15,  3, '.', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );
   dmd.drawChar( 15,  3, '.', GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawChar( 15,  3, '.', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );
   dmd.drawChar( 15,  3, '.', GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawChar( 15,  3, '.', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );

   // draw an X right across 2 panels
   //dmd.drawLine(  0,  0, 63, 15, GRAPHICS_NORMAL );
   //dmd.drawLine(  0, 15, 63,  0, GRAPHICS_NORMAL );
   //delay( 1000 );

   dmd.drawMarquee("Scrolling Text",14,1);
   //dmd.drawMarquee("Sarah Sarah ",14,1);   //testing with my daughter, remove
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(1);
       timer=millis();
     }
   }
   // half the pixels on
   dmd.drawTestPattern( PATTERN_ALT_0 );
   delay( 1000 );

   // the other half on
   dmd.drawTestPattern( PATTERN_ALT_1 );
   delay( 1000 );
   
   // display some text
   dmd.clearScreen( true );
   dmd.selectFont(System5x7);
   dmd.drawString(  2,  1, "freet", 5, GRAPHICS_NORMAL );
   dmd.drawString(  2,  9, "ronic", 5, GRAPHICS_NORMAL );
   delay( 2000 );
   
   // draw a border rectangle around the outside of the display
   dmd.clearScreen( true );
   dmd.drawBox(  0,  0, 31, 15, GRAPHICS_NORMAL );
   delay( 1000 );
   
   // draw an X
   dmd.drawLine(  0,  0, 11, 15, GRAPHICS_NORMAL );
   dmd.drawLine(  0, 15, 11,  0, GRAPHICS_NORMAL );
   delay( 1000 );
   
   // draw a circle
   dmd.drawCircle( 16,  8,  5, GRAPHICS_NORMAL );
   delay( 1000 );
   
   // draw a filled box
   dmd.drawFilledBox( 24, 3, 29, 13, GRAPHICS_NORMAL );
   delay( 1000 );

   // stripe chaser
   for( b = 0 ; b < 20 ; b++ )
   {
      dmd.drawTestPattern( (b&1)+PATTERN_STRIPE_0 );
      delay( 200 );      
   }
   delay( 200 );      
   
}

