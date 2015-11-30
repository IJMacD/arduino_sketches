//ONG LIT YIT 2013-07-20
//This following code plays happy birthday melody on Arduino
//Put Piezo Buzzer on GDN and 9 (Positive and negative are reversible)
//this project requires a Piezo Buzzer and

// an Arduino board and

//jumper wires to connect Buzzer's (+) to ~9 and (-) to GND (any GND)

//HAVE FUN

//this project requires a Piezo Buzzer and

// an Arduino board and

//jumper wires to connect Buzzer's (+) to ~4 and (-) to GND (any GND)

//HAVE FUN

int speakerPin = 1;

int potPort = 1;    // select the analog input port for the 
                    // potentiometer.
                    // Note: not the same as pin number

int length = 11; // the number of notes

char notes[] = "EEE EEEGEAA";

int beats[] = { 8, 8, 8, 4, 4, 4, 4, 4, 4, 4, 4 };

int tempo = 150;

int val = 0;

void playTone(int tone, int duration) {

for (long i = 0; i < duration * 1000L; i += tone * 2) {

   digitalWrite(speakerPin, HIGH);

   delayMicroseconds(tone);

   digitalWrite(speakerPin, LOW);

   delayMicroseconds(tone);

}

}

void playNote(char note, int duration) {

char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int SPEE = 5;

// play the tone corresponding to the note name

for (int i = 0; i < 17; i++) {

   if (names[i] == note) {
    int newduration = duration/SPEE;
//    float pitchAdjust = 0.5 + (val / 250);
//    float newPitch = tones[i] * pitchAdjust;
     playTone(tones[i], newduration);

   }

}

}

void setup() {

pinMode(speakerPin, OUTPUT);

}

void loop() {

for (int i = 0; i < length; i++) {
  
  val = analogRead(potPort);    // read the value from the sensor

  tempo = 50 + val / 5;

   if (notes[i] == ' ') {

     delay(beats[i] * tempo); // rest

   } else {

     playNote(notes[i], beats[i] * tempo);

   }

   // pause between notes

   delay(tempo);

}

}
