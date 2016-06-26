/*
 * OLED 128x64 monochrome library for Digistump (ATTiny85)
 *
 *
 * taken useful parts from 
 * 1.
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 * @file: ssd1306xled.c
 * @created: 2014-08-12
 * @author: Neven Boyanov
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 * 2.
 * This is a library for our Monochrome OLEDs based on SSD1306 drivers
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/category/63_98
 * I2C is used to communicate, 4 (without reset) or 5 pins are required to  
 * interface
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * Written by Limor Fried/Ladyada  for Adafruit Industries.
 *
 *
 * for ATTiny85 reduced Flash- & SRAM-usage 
 * - smaller font array (double used also for big letters - sorry for the blocks)
 * - no display buffer (bmp graphic position x=0..127, y = 0..7, only 8 pixel high lines - no "Flying Toasters")
 * 
 * S. Goetze, 14.12.2014 
 *      rework 18.10.2015 -> inspired by DigisparkOLED
 *      ssd1306_begin() and constructor OLED() changed to no parameters - hardware variants eliminated
 *      element "display" now created in library
 */

 
 /**********************************************************************
  *              * * * * * * N O T E * * * * * *
  *
  * You have to use x,y-positions different:
  *
  * x is horizontal position 0..127 or horizontal size 1..128
  *
  * y is vertical position in 8 lines of each 8 pixel (byte) height
  * i.e. position 0..7 or size 1..8
  * MSB of databyte is written to lowermost position in line
  *
  ***********************************************************************/

  
#include <avr/pgmspace.h> 
#include "TinySSD1306.h"
#include "font_5x8p.h"

const uint8_t ssd1306_init_sequence [] PROGMEM = {	// Initialization Sequence
	0xAE,			// Display OFF (sleep mode)
	0x20, 0b00,		// Set Memory Addressing Mode
					// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
					// 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,			// Set COM Output Scan Direction
	0x00,			// ---set low column address
	0x10,			// ---set high column address
	0x40,			// --set start line address
	0x81, 0x3F,		// Set contrast control register
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x3F,		// Set multiplex ratio(1 to 64)
	0xA4,			// Output RAM to Display
					// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xD5,			// --set display clock divide ratio/oscillator frequency
	0xF0,			// --set divide ratio
	0xD9, 0x22,		// Set pre-charge period
	0xDA, 0x12,		// Set com pins hardware configuration		
	0xDB,			// --set vcomh
	0x20,			// 0x20,0.77xVcc
	0x8D, 0x14,		// Set DC-DC enable
	0xAF			// Display ON in normal mode
	
};

OLED::OLED(void) {}

void OLED::ssd1306_begin(void) {

  Wire.begin();  // I2C Init

  for (uint8_t i = 0; i < sizeof (ssd1306_init_sequence); i++) {
	ssd1306_command(pgm_read_byte(&ssd1306_init_sequence[i]));
  }
  ssd1306_fill_area();
}

void OLED::ssd1306_command(uint8_t command)
{
	Wire.beginTransmission(SSD1306_SA);  //SSD1306_SA
    Wire.write(0);	// write command
	Wire.write(command);
	Wire.endTransmission();
}

void OLED::ssd1306_data_start(void)
{
    Wire.beginTransmission(SSD1306_SA);
	Wire.write(0x40);
}	

void OLED::ssd1306_data(uint8_t data)
{
	if(Wire.writeAvailable()) {
		Wire.endTransmission();
    	ssd1306_data_start();
	}
    Wire.write(data);
}
	
void OLED::ssd1306_setpos(uint8_t x, uint8_t y)
{
	Wire.beginTransmission(SSD1306_SA);
    Wire.write(0);
	Wire.write(0xb0 + y);
	Wire.write(((x & 0xf0) >> 4) | 0x10); // | 0x10
	Wire.write((x & 0x0f) | 0x01); // | 0x01
	Wire.endTransmission();
}

void OLED::ssd1306_fill_area(uint8_t fill_Data,uint8_t x, uint8_t y, uint8_t dx, uint8_t dy)
{
	uint8_t m,n;
	if ((dx += x) > SSD1306_LCDWIDTH) return;
	if ((dy += y) > SSD1306_LCDHEIGHT) return;
	for(m=y;m<dy;m++)
	{
		ssd1306_setpos(x,m);
		ssd1306_data_start();
		for(n=x;n<dx;n++)
		{
			ssd1306_data(fill_Data);
		}
		Wire.endTransmission();
	}
}

void OLED::ssd1306_prop_str_small(uint8_t x, uint8_t y, const char ch[], boolean invert)
{
	uint8_t c,i,j=0,pa;
	while(ch[j] != '\0')
	{
		c = ch[j] - 32;
		if(x>123)		//poor but fast test, possibly there is enough space for a small char
		{
			x=0;
			y++;
		}
		ssd1306_setpos(x,y);
		ssd1306_data_start();
	    for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]);
			if(pa < 0x80) 
			{
			  ssd1306_data(invert?(pa^0xff):pa);
			  x++;
			}
		}
        ssd1306_data(invert?0xff:0);		//space column to next char
		Wire.endTransmission();
		x++;
		j++;
	}
}

void OLED::ssd1306_str_small(uint8_t x, uint8_t y, const char ch[], boolean invert)
{
	uint8_t c,i,j=0,pa;
	while(ch[j] != '\0')
	{
		c = ch[j] - 32;
		if(x>123)
		{
			x=0;
			y++;
		}
		ssd1306_setpos(x,y);
		ssd1306_data_start();
	    for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]) & 0x7f;
			ssd1306_data(invert?(pa^0xff):pa);
		}
		ssd1306_data(invert?0xff:0);		//6th column
		Wire.endTransmission();
		x += 6;
		j++;
	}
}

void OLED::ssd1306_prop_str_big(uint8_t x, uint8_t y,const char ch[], boolean invert)
{
	uint8_t c,i,j=0,pa,spa;
	while (ch[j]!='\0') 
	{
		c = ch[j] - 32;
		if (x>118)
		{
			x=0;
			y++;
		}
		ssd1306_setpos(x,y+1);
		ssd1306_data_start();
		for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]);
			if (pa < 0x80) 
			{
				spa = ((pa & 0x40)?0x30:0) | ((pa & 0x20)?0x0c:0) | ((pa & 0x10)?0x03:0);  
				ssd1306_data(invert?(spa^0xff):spa);
				ssd1306_data(invert?(spa^0xff):spa);
			}
		}
		ssd1306_data(invert?0xff:0);
		ssd1306_data(invert?0xff:0);
		Wire.endTransmission();

		ssd1306_setpos(x,y);
		ssd1306_data_start();
		for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]);
			if (pa < 0x80) {
				spa = ((pa & 0x08)?0xc0:0) | ((pa & 0x04)?0x30:0) | ((pa & 0x02)?0x0c:0) | ((pa & 0x01)?0x03:0);  
				ssd1306_data(invert?(spa^0xff):spa);
				ssd1306_data(invert?(spa^0xff):spa);
				x += 2;
			}
		}
		ssd1306_data(invert?0xff:0);
		ssd1306_data(invert?0xff:0);
		Wire.endTransmission();
		x += 2;
		j++;
	}
}

void OLED::ssd1306_str_big(uint8_t x, uint8_t y,const char ch[], boolean invert)
{
	uint8_t c,i,j=0,pa,spa;
	while (ch[j]!='\0') 
	{
		c = ch[j] - 32;
		if (x>118)
		{
			x=0;
			y++;
		}
		ssd1306_setpos(x,y+1);
		ssd1306_data_start();

		for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]);
			spa = ((pa & 0x40)?0x30:0) | ((pa & 0x20)?0x0c:0) | ((pa & 0x10)?0x03:0);  
			ssd1306_data(invert?(spa^0xff):spa);
			ssd1306_data(invert?(spa^0xff):spa);
		}
		ssd1306_data(invert?0xff:0);
		ssd1306_data(invert?0xff:0);
		Wire.endTransmission();
		
		ssd1306_setpos(x,y);
		ssd1306_data_start();
		for(i=0;i<5;i++)
		{
			pa = pgm_read_byte(&font5_8[c][i]);
			spa = ((pa & 0x08)?0xc0:0) | ((pa & 0x04)?0x30:0) | ((pa & 0x02)?0x0c:0) | ((pa & 0x01)?0x03:0);  
			ssd1306_data(invert?(spa^0xff):spa);
			ssd1306_data(invert?(spa^0xff):spa);
			
		}
		ssd1306_data(invert?0xff:0);
		ssd1306_data(invert?0xff:0);
		Wire.endTransmission();
		x += 12;
		j++;
	}
}

void OLED::ssd1306_draw_bmp(uint8_t x, uint8_t y, uint8_t dx, uint8_t dy, uint8_t const bitmap[], boolean invert)
{
	unsigned int j = 0;
	uint8_t ix,iy,pa;

	if ((dx += x) > SSD1306_LCDWIDTH) return;
	if ((dy += y) > SSD1306_LCDHEIGHT) return;

	for(iy=y;iy<dy;iy++)
	{
		ssd1306_setpos(x,iy);
		ssd1306_data_start();
		for(ix=x;ix<dx;ix++)
		{
			pa = pgm_read_byte(&bitmap[j++]);
			ssd1306_data(invert?(pa^0xff):pa);
		}
		Wire.endTransmission();
	}
}


void OLED::ssd1306_inverted(boolean invert) {
  if (invert) {
    ssd1306_command(SSD1306_INVERTDISPLAY);
  } else {
    ssd1306_command(SSD1306_NORMALDISPLAY);
  }
}

// startscroll
// Activate a scrolling
// no chance to select borders left and right, always whole lines (pages) are part of scrolling
// Parameters (all optional)
// mode: scrolling direction - RIGHT (0, default), LEFT (1), RIGHT_UP (2), LEFT_UP (3)
// htp: horizontal top page - first line that is scrolled in "mode" direction - 0(default)..7
// hpb: horizontal botton page - last line that is scrolled - 0..7(default)
// hspeed: scrolling speed of this area - 0(fastest)..7(slowest), default 3
// the next 3 parameters are used only if also vertical scrolling is selected
// vtp: vertical top pages - count of pages (lines) from top that are not scrolled vertically - 0(default)..8
// vbp: vertical botton pages - count of pages (lines) under top area  that is scrolled vertically - 0..8(default)
// vmult: multiplicator to hspeed for vertical scrolling (stepwidth for each scrollstep) - 0..7 - default 1

void OLED::ssd1306_startscroll(uint8_t mode, uint8_t htp, uint8_t hbp, uint8_t hspeed, uint8_t vtp, uint8_t vbp, uint8_t vmult) {
  static uint8_t timeCode[8] = {7,4,5,0,6,1,2,3};
  static uint8_t modeCode[4] = {SSD1306_RIGHT_HORIZONTAL_SCROLL, SSD1306_LEFT_HORIZONTAL_SCROLL,
                                SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL, SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL};
  uint8_t mCode = modeCode[mode & 3];
  if (mode > 1) {
    ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);  
    ssd1306_command((vtp % 9) * 8);
    ssd1306_command((vbp % 9) * 8);
  }
  ssd1306_command(mCode);
  ssd1306_command(0);
  ssd1306_command(htp & 7);
  ssd1306_command(timeCode[hspeed & 7]);
  ssd1306_command(hbp & 7);  
  if ((mode & 3) < 2) {
    ssd1306_command(0);
    ssd1306_command(0xff);
  } else {
    ssd1306_command(vmult & 7);
  }
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}
  
void OLED::ssd1306_stopscroll(void){
  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

// Dim the display
// dim = true: display is dimmed
// dim = false: display is normal
void OLED::ssd1306_dim(boolean dim) {
  ssd1306_command(SSD1306_SETCONTRAST);
  ssd1306_command(dim ? 0 : 0x3f);
}

OLED display;