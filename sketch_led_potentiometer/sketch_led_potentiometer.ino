/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

int potPort = 1;    // select the analgog input port for the 
                    // potentiometer. Note: not the same as pin number
int ledPin = 1;     // select the pin for the LED
int val = 0;        // variable to store the value coming from the sensor
int refreshRate = 100;
int timeSinceChange = 0;
int ledState = 1;

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
}

void loop() {
  timeSinceChange += refreshRate;
  val = analogRead(potPort) * 10;    // read the value from the sensor

  if(timeSinceChange > val){
    flipState();
    timeSinceChange = 0; 
    
  }

  delay(refreshRate);
}

void flipState(){
  if(ledState){
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
  else {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  }
}

