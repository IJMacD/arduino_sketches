
#include <TinySSD1306.h>
#include <Wire.h>

uint8_t const PROGMEM eisenbahn_bmp[] = 
{ 0x08,0xFC,0x0C,0x0C,0x0C,0xFE,0x0F,0x0F,0x0F,0xFE,
  0x0C,0x0C,0x0C,0xFE,0x0F,0x0F,0x0F,0xFE,0x0C,0x0C,
  0x0C,0xFC,0x08,0x00,0x08,0xFC,0x0C,0x0C,0x0C,0xFE,
  0x0F,0x0F,0x0F,0xFE,0x0C,0x0C,0x0C,0xFE,0x0F,0x0F,
  0x0F,0xFE,0x0C,0x0C,0x0C,0xFC,0x08,0x00,0x08,0xFC,
  0x86,0x86,0x86,0xFE,0x86,0x86,0xFE,0x84,0x80,0xF0,
  0xF8,0xF0,0x80,0x80,0x83,0xFF,0xFF,0x83,0x00,0x00,
  0x38,0x2F,0x76,0xFA,0xDA,0xFB,0x76,0x2E,0x3E,0x3F,
  0x36,0x36,0x36,0x3F,0x3E,0x2E,0x76,0xFB,0xDA,0xFA,
  0x76,0x2F,0x38,0x0C,0x38,0x2F,0x76,0xFA,0xDA,0xFB,
  0x76,0x2E,0x3E,0x3F,0x36,0x36,0x36,0x3F,0x3E,0x2E,
  0x76,0xFB,0xDA,0xFA,0x76,0x2F,0x38,0x0C,0x08,0x3F,
  0x77,0xFB,0xDB,0xFB,0x77,0x2F,0x3D,0x3D,0x35,0x35,
  0x3F,0x3D,0x3D,0x2F,0x77,0xFB,0xDB,0xFB,0x77,0x3C
};

uint8_t const PROGMEM rauch_bmp[] =
{ 0x1D,0x3B,0x7B,0x7F,0x67,0x6E,0xFC,0xF0
};

uint8_t const PROGMEM tanne_bmp[] =
{ 0x00,0x00,0x00,0x80,0xC0,0xE8,0xFC,0xFE,
  0xFF,0xFE,0xFC,0xE8,0xC0,0x80,0x00,0x00,
  0x00,0x10,0x19,0x1D,0x1F,0x1F,0x1F,0x7F,
  0x7F,0x7F,0x1F,0x1F,0x1F,0x1D,0x19,0x10
};

uint8_t const PROGMEM star_bmp[] =
{ 0x40,0xC0,0xC0,0xE0,0xE0,0xF0,0xFC,0xFF,
  0xFC,0xF0,0xE0,0xE0,0xC0,0xC0,0x40,0x00,
  0x00,0x00,0x01,0x71,0x3F,0x1F,0x0F,0x07,
  0x0F,0x1F,0x3F,0x71,0x01,0x00,0x00,0x00
};
uint8_t const PROGMEM square_lo_bmp[] =
{ 0x00,0x00,0xFC,0xFC,0xFC,0xFC,0x3C,0x3C
};

uint8_t const PROGMEM square_ro_bmp[] =
{ 0x3C,0x3C,0xFC,0xFC,0xFC,0xFC,0x00,0x00
};

uint8_t const PROGMEM square_lu_bmp[] =
{ 0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3C,0x3C
};

uint8_t const PROGMEM square_ru_bmp[] =
{ 0x3C,0x3C,0x3F,0x3F,0x3F,0x3F,0x00,0x00
};

uint8_t const PROGMEM square_lo_r_bmp[] =
{ 0x00,0x00,0xC0,0xF0,0xF8,0xF8,0x7C,0x3C
};

uint8_t const PROGMEM square_ro_r_bmp[] =
{ 0x3C,0x7C,0xF8,0xF8,0xF0,0xC0,0x00,0x00
};

uint8_t const PROGMEM square_lu_r_bmp[] =
{ 0x00,0x00,0x03,0x0F,0x1F,0x1F,0x3E,0x3C
};

uint8_t const PROGMEM square_ru_r_bmp[] =
{ 0x3C,0x3E,0x1F,0x1F,0x0F,0x03,0x00,0x00
};

uint8_t const PROGMEM square_v_bmp[] =
{ 0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00
};

uint8_t const PROGMEM square_h_bmp[] =
{ 0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C
};


void setup()   {                
  display.ssd1306_begin();  // initialize with the I2C addr 0x3C (for the 128x64)
  randomSeed(analogRead(0));
}

void loop() {
  textoutput();
  blinking_stars();
  draw_rectangles();
  xmas_greetings();
}

void blinking_stars() {
  unsigned long startTime = millis(); 
  uint8_t x,y,z;
  
  display.ssd1306_fill_area();
  while ((unsigned long)(millis() - startTime) <= 25000) {
    x = random(8);
    y = random(4);
    z = random(2);
    if (z) 
      display.ssd1306_draw_bmp(x*16,y*2,16,2,star_bmp);
    else
      display.ssd1306_fill_area(0,x*16,y*2,16,2);
    delay(100);
  }
  display.ssd1306_inverted(true);
  display.ssd1306_startscroll(LEFT_UP);
  delay(5000);
  display.ssd1306_stopscroll();
  display.ssd1306_inverted(false);
}  
  
void xmas_greetings() {
  display.ssd1306_fill_area();

  display.ssd1306_draw_bmp(4,0,16,2,tanne_bmp);
  display.ssd1306_draw_bmp(27,0,16,2,tanne_bmp);
  display.ssd1306_draw_bmp(85,0,16,2,tanne_bmp);
  display.ssd1306_draw_bmp(108,0,16,2,tanne_bmp);

  display.ssd1306_str_small(48,0,"Merry");
  display.ssd1306_str_small(52,1,"XMAS");

  display.ssd1306_draw_bmp(2,2,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(10,3,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(42,3,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(50,4,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(66,2,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(74,3,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(114,4,8,1,rauch_bmp);
  display.ssd1306_draw_bmp(122,5,8,1,rauch_bmp);

  display.ssd1306_draw_bmp(0,6,70,2,eisenbahn_bmp);

  display.ssd1306_startscroll(RIGHT_UP,6,7,4,2,4,1);
  delay(23100);
  display.ssd1306_startscroll(RIGHT_UP,6,1,4,2,4,1);
  delay(15000);
  display.ssd1306_stopscroll();
}

void rectangle(uint8_t x, uint8_t y, uint8_t dx, uint8_t dy, boolean roundc = false, boolean invers = false) {
  uint8_t ix,iy;
  if (roundc) {
    display.ssd1306_draw_bmp(x*8,y,8,1,square_lo_r_bmp, invers);    
    display.ssd1306_draw_bmp(x*8,y+dy-1,8,1,square_lu_r_bmp, invers);    
    display.ssd1306_draw_bmp((x+dx-1)*8,y,8,1,square_ro_r_bmp, invers);    
    display.ssd1306_draw_bmp((x+dx-1)*8,y+dy-1,8,1,square_ru_r_bmp, invers);
  } else {
    display.ssd1306_draw_bmp(x*8,y,8,1,square_lo_bmp, invers);    
    display.ssd1306_draw_bmp(x*8,y+dy-1,8,1,square_lu_bmp, invers);    
    display.ssd1306_draw_bmp((x+dx-1)*8,y,8,1,square_ro_bmp, invers);    
    display.ssd1306_draw_bmp((x+dx-1)*8,y+dy-1,8,1,square_ru_bmp, invers);
  }
  for (ix=x+1; ix<x+dx-1; ix++) {
    display.ssd1306_draw_bmp(ix*8,y,8,1,square_h_bmp, invers);    
    display.ssd1306_draw_bmp(ix*8,y+dy-1,8,1,square_h_bmp, invers);    
  }
  for (iy=y+1; iy<y+dy-1; iy++) {
    display.ssd1306_draw_bmp(x*8,iy,8,1,square_v_bmp, invers);    
    display.ssd1306_draw_bmp((x+dx-1)*8,iy,8,1,square_v_bmp, invers);    
  }
}

void textoutput() {
  display.ssd1306_fill_area();
  rectangle(0,0,16,8,true);
  display.ssd1306_str_big(42, 1, "DEMO");
  display.ssd1306_prop_str_small(11,2,"OLED",true);
  display.ssd1306_prop_str_small(94,2,"0.96",true);
  display.ssd1306_prop_str_small(13,3,"SSD1306");
  display.ssd1306_str_small(62,3,"Digistump");
  display.ssd1306_prop_str_small(10,5,"proportional ein");
  display.ssd1306_str_small(10,6,"proportional aus");  
  delay(20000);
}

void draw_rectangles() {
  unsigned long startTime; 
  uint8_t x,y,dx,dy,z;
  
  for (x=0; x<20; x++) {
    rectangle(0,0,16,8,false, false);
    rectangle(1,1,14,6,false, true);
    rectangle(2,2,12,4,false, false);
    rectangle(3,3,10,2,false, true);
    rectangle(0,0,16,8,true, true);
    rectangle(1,1,14,6,true, false);
    rectangle(2,2,12,4,true, true);
    rectangle(3,3,10,2,true, false);
  }
  
  display.ssd1306_fill_area();
  startTime = millis();  
  while ((unsigned long)(millis() - startTime) <= 20000) {
    x = random(15);
    dx = random(17-x); 
    dx = max(2,dx);
    y = random(7);
    dy = random(9-y);
    dy = max(2,dy);
    z = random(2);
    rectangle(x,y,dx,dy,(z==1));
    delay(50);
  }
}
    

