
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4); 

// This example shows a scrolling text.
// If U8G2_16BIT is not set (default), then the pixel width of the text must be lesser than 128
// If U8G2_16BIT is set, then the pixel width an be up to 32000

u8g2_uint_t offset;      // current offset for the scrolling text
u8g2_uint_t width;      // pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
const char *text = "         HELLO FROM JOHN K1WIZ     TG 31688     HAMSHACKHOTLINE.COM ";  // scroll this text from right to left


void setup(void) {

  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);   

  /* U8g2 Project: T6963 Test Board */
  //pinMode(18, OUTPUT);
  //digitalWrite(18, 1);  

  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0);  

  u8g2.begin();  
  
  u8g2.setFont(u8g2_font_inb30_mr); // set the target font to calculate the pixel width
  width = u8g2.getUTF8Width(text);    // calculate the pixel width of the text
  
  u8g2.setFontMode(0);    // enable transparent mode, which is faster
}


void loop(void) {
  u8g2_uint_t x;
  
  u8g2.firstPage();
  do {
  
    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_inb30_mr);   // set the target font
    do {                // repeated drawing of the scrolling text...
      u8g2.drawUTF8(x, 30, text);     // draw the scolling text
      x += width;           // add the pixel width of the scrolling text
    } while( x < u8g2.getDisplayWidth() );    // draw again until the complete display is filled
    
    u8g2.setFont(u8g2_font_inb16_mr);   // draw the current pixel width
    u8g2.setCursor(0, 58);
    u8g2.print(width);          // this value must be lesser than 128 unless U8G2_16BIT is set
    
  } while ( u8g2.nextPage() );
  
  offset-=3;              // scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t)-width )  
    offset = 0;             // start over again
    
  delay(1);             // do some small delay
}
