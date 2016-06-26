/*
 * OLED 128x64 monochrome library for Digistump (ATTiny85)
 *
 *
 * useful parts from 
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
 * - no display buffer (bmp graphic position x=0..127, y = 0..7 only 8 pixel high lines - no "Flying Toasters")
 * 
 * S. Goetze, 14.12.2014
 *      rework 18.10.2015 -> inspired by DigisparkOLED
 *      ssd1306_begin() and constructor OLED() changed to no parameters - hardware variants eliminated
 *      element "display" now created in library
 */
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
 
#ifndef TINYSSD1306_H
#define TINYSSD1306_H

// ----------------------------------------------------------------------------
#ifndef SSD1306_SA
#define SSD1306_SA		0x78 // Slave address
#endif
// ----------------------------------------------------------------------------

#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 8

#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_SETCONTRAST 0x81

#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

//use as mode in scrolling function
#define RIGHT 0
#define LEFT 1
#define RIGHT_UP 2
#define LEFT_UP 3

class OLED {
public:
  OLED(void);
  void ssd1306_begin(void);
  void ssd1306_command(uint8_t command);
  void ssd1306_data_start(void);
  void ssd1306_data(uint8_t data);
  void ssd1306_setpos(uint8_t x, uint8_t y);
  void ssd1306_fill_area(uint8_t fill_Data=0, uint8_t x=0, uint8_t y=0, uint8_t dx=128, uint8_t dy=8);
  void ssd1306_prop_str_small(uint8_t x, uint8_t y, const char ch[], boolean invert=false);
  void ssd1306_str_small(uint8_t x, uint8_t y, const char ch[], boolean invert=false);
  void ssd1306_prop_str_big(uint8_t x, uint8_t y,const char ch[], boolean invert=false);
  void ssd1306_str_big(uint8_t x, uint8_t y,const char ch[], boolean invert=false);
  void ssd1306_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[], boolean invert=false);
  void ssd1306_inverted(boolean invert);
  void ssd1306_startscroll(uint8_t mode = RIGHT, uint8_t htp = 0, uint8_t hbp = 7, uint8_t hspeed = 3,
							uint8_t vtp = 0, uint8_t vbp = 8,uint8_t vmult = 1);
  void ssd1306_stopscroll(void);
  void ssd1306_dim(uint8_t contrast);

};

extern OLED display;

#endif
