#include <TinyWireM.h>

// ============================================================================

#include "SI7021.h"
#include "DigisparkOLED.h"

// ============================================================================

//#include "img0_128x64c1.h"
//#include "digistump_128x64c1.h"
//#include "faihai.h"
//#include "dick.h"
//#include "fai.h"
//#include "hai.h"

SI7021 sensor;
//int x = 40;
//int y = 3;
char temp[5];
char humid[5];
char msg[3] = {129,130};

void setup() {
  // put your setup code here, to run once:

temp[0] = '0';
temp[1] = '0';
temp[2] = '.';
temp[3] = '0';
temp[4] = '0';

humid[0] = '0';
humid[1] = '0';
humid[2] = '0';
humid[3] = '%';
humid[4] = 0;


  oled.begin();
  sensor.begin();

}

void loop() {
  
  // put your main code here, to run repeatedly:
//  oled.fill(0xFF); //fill screen with color
//  delay(1000);
//  oled.clear(); //all black
//    si7021_env data = sensor.getHumidityAndTemperature();
//    temp = String(data.celsiusHundredths);

//  convertInt(temp, 1234);
  convertHumid(humid, sensor.getHumidityPercent());
  convertTemp(temp, sensor._getCelsiusPostHumidity());
//    humid = String(data.humidityBasisPoints);
  //usage: oled.setCursor(X IN PIXELS, Y IN ROWS OF 8 PIXELS STARTING WITH 0);
  oled.setCursor(0, 0); //top left
  oled.setFont(FONT8X16);
  oled.print(F("Temp: "));
  oled.println(temp);
  oled.print(F("Humidity: "));
  oled.println(humid);
  oled.print(F("Forecast: "));
  oled.setFont(FONT16X16);
  oled.println(msg);
    delay(1000);
////  
//  if((x += 8) >= 128){
//    x = 0;
//  }
//  if(++y >= 7){
//    y = 0;
//  }
//  oled.setFont(FONT6X8);
//  oled.print(F(" OLED!"));
//  oled.setCursor(0, 2); //two rows down because the 8x16 font takes two rows of 8
//  oled.println(F("test")); //println will move the cursor 8 or 16 pixels down (based on the front) and back to X=0
//  oled.print(F("test test test test test")); //lines auto wrap
  
//  delay(1000);
  //usage oled.bitmap(START X IN PIXELS, START Y IN ROWS OF 8 PIXELS, END X IN PIXELS, END Y IN ROWS OF 8 PIXELS, IMAGE ARRAY);
//  oled.bitmap(0, 0, 128, 8, img0_128x64c1);
//  delay(3000);
//  oled.bitmap(0, 0, 128, 8, dick);
//  delay(3000);
//  oled.bitmap(0, 0, 128, 8, faihai);
//  delay(3000);
//  oled.bitmap(x, 0, 53+x, 8, fai);
//  delay(100);
//  oled.bitmap(x, 0, 55+x, 8, hai);
//  delay(100);
}
void convertTemp(char *out, int t){
  for(int i = 4; i >= 0; i--){
    if(i == 2) { continue; }
    out[i] = (t % 10) + '0';
    t = t / 10;
  }
}
void convertHumid(char *out, int t){
  for(int i = 2; i >= 0; i--){
    out[i] = (t % 10) + '0';
    t = t / 10;
  }
}

