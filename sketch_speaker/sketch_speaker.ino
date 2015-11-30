int speakerPin = 4;
int potPort = 1;    // select the analog input port for the 
                    // potentiometer.
                    // Note: not the same as pin number
int refreshRate = 10;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  val = analogRead(potPort);    // read the value from the sensor

  analogWrite(speakerPin, val / 4);

  delay(refreshRate);
}
