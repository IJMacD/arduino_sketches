const int PIN_COUNT = 5;
const int LED_COUNT = PIN_COUNT * (PIN_COUNT - 1);

const int DISPLAY_WIDTH = 4;
const int DISPLAY_HEIGHT = 4;

void setup() {
  // put your setup code here, to run once:
}

void loop() {

  static unsigned long compensate = -16;

  unsigned long time = millis() / 1000;

  time = time  + compensate;

  for(int i = 0; i < DISPLAY_WIDTH; i++){
    for(int j = 0; j < DISPLAY_HEIGHT; j++){
      setPixel(i, j, time & 0x1);
      time = time >> 1;
      delay(1);
    }
  }
}

// light a pixel at the given coordinates
void setPixel(byte x, byte y, boolean ledStatus) {
  if (x >= 0 && x < DISPLAY_WIDTH) {
    if (y <= x) {
      x++;
    }
    setLed(x, y, ledStatus);
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

