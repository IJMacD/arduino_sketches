void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

int seconds = 0;

void loop() {

  seconds++;
  
  setPins(seconds % 60);
  
  delay(1000);
  
}

void setPins(int num){
  digitalWrite(0, num & 0x20 ? HIGH : LOW);
  digitalWrite(1, num & 0x10 ? HIGH : LOW);
  digitalWrite(2, num & 0x08 ? HIGH : LOW);
  digitalWrite(3, num & 0x04 ? HIGH : LOW);
  digitalWrite(4, num & 0x02 ? HIGH : LOW);
  digitalWrite(5, num & 0x01 ? HIGH : LOW);
}

