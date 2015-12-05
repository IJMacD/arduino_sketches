const int PIN_COUNT = 5;
const int LED_COUNT = PIN_COUNT * (PIN_COUNT - 1);

const int DISPLAY_WIDTH = 4;
const int DISPLAY_HEIGHT = 4;

void setup() {
  // put your setup code here, to run once:
//  setLed(3, 0, true);
//  displayValue(256);
}

void loop() {
//    for(int i = 0; i < 5000; i++){
//      displayValue(256);
//    }
//    for(int i = 0; i < 5000; i++){
//      displayValue(8192);
//    }
//    for(int i = 0; i < 5000; i++){
//      displayValue(8196);
//    }

  unsigned long acc = 1;
  for(int j = 0; j < 16; j++){
    for(int i = 0; i < 500; i++){
      displayValue(acc);
    }
    acc = acc * 2;
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

//  delay(1);
}

