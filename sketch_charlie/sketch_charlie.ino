#include <EEPROM.h>

const int PIN_COUNT = 5;
const int LED_COUNT = PIN_COUNT * (PIN_COUNT - 1);

const int DISPLAY_WIDTH = 4;
const int DISPLAY_HEIGHT = 4;

// Convert from seconds to binary fractions of a day
const double TIME_RATIO = 65536.0d / 86400.0d;

const unsigned int TIME_ADDRESS = 0;

unsigned long compensate;

void setup() {
  // put your setup code here, to run once:

  EEPROM.get(TIME_ADDRESS, compensate);

  compensate = compensate - 16;
}

void loop() {

  unsigned long time = (millis() * TIME_RATIO / 1000) + compensate;

  displayValue(time);

  // EEPROM only has 100,000 writes so minute resolution
  // will make it last months rather than days :(
  if(time % 60 == 0){
    EEPROM.put(TIME_ADDRESS, time);
  }
}

void displayValue(unsigned long val){
  for(int j = 0; j < DISPLAY_HEIGHT; j++){
    for(int i = 0; i < DISPLAY_WIDTH; i++){
      setPixel(i, j, val & 0x1);
      val = val >> 1;
      delay(1);
    }
  }
}

// light a pixel at the given coordinates
void setPixel(byte x, byte y, boolean ledStatus) {
  if (x >= 0 && x < DISPLAY_WIDTH) {
    if (x <= y) {
      y++;
    }
    setLed(y, x, ledStatus);
  }
}

void setLed(int vin, int gnd, boolean ledStatus)
{
  pinMode(0, INPUT); 
  pinMode(1, INPUT); 
  pinMode(2, INPUT); 
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 

  if(!ledStatus) return;
  
  pinMode(vin, OUTPUT);
  pinMode(gnd, OUTPUT);
  
  digitalWrite(vin, HIGH);
  digitalWrite(gnd, LOW);
}

