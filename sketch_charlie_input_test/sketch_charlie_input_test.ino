const int PIN_COUNT = 5;
const int LED_COUNT = PIN_COUNT * (PIN_COUNT - 1);

const int DISPLAY_WIDTH = 4;
const int DISPLAY_HEIGHT = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT);
}

void loop() {

  static unsigned long compensate = -16;
  
  unsigned int val = analogRead(1);
  
  for(int i = 0; i < DISPLAY_WIDTH; i++){
    for(int j = 0; j < DISPLAY_HEIGHT; j++){
      setPixel(i, j, val & 0x1);
      val = val >> 1;
      delay(1);
    }
  }
  
//  if(analogRead(5) > 128){
//    compensate = compensate + 60;
//  }
//
//  unsigned long time = millis() / 1000;
//
//  time = time  + compensate;
//
//  for(int i = 0; i < DISPLAY_WIDTH; i++){
//    for(int j = 0; j < DISPLAY_HEIGHT; j++){
//      setPixel(i, j, time & 0x1);
//      time = time >> 1;
//      delay(1);
//    }
//  }
}

// light a pixel at the given coordinates
void setPixel(byte x, byte y, boolean ledStatus) {
  if (x >= 0 && x < DISPLAY_WIDTH) {
    if (y <= x) {
      x++;
    }
    setLed(y, x, ledStatus);
  }
}

void setLed(int vin, int gnd, boolean ledStatus)
{
  pinMode(1, INPUT); 
  pinMode(2, INPUT); 
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 
  pinMode(5, INPUT); 

  if(!ledStatus) return;
  
  pinMode(vin + 1, OUTPUT);
  pinMode(gnd + 1, OUTPUT);
  
  digitalWrite(vin + 1, HIGH);
  digitalWrite(gnd + 1, LOW);
}

