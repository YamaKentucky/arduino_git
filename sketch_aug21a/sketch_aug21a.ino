#include "pitches.h"

int melody[] = {
 NOTE_E4, NOTE_E4,0,NOTE_E4,0, 
 NOTE_C4, NOTE_E4,0,NOTE_G4,0,0,0,NOTE_G3,};

int noteDurations[] = {
 8,8,8,8,8,8,8,8,8,8,8,8,8,};

void setup() {
 for (int thisNote = 0; thisNote < 13; thisNote++) {
   int noteDuration = 1000/noteDurations[thisNote];
   tone(8, melody[thisNote],noteDuration);
   int pauseBetweenNotes = noteDuration * 1.30;
   delay(pauseBetweenNotes);
 }
}

void loop() {
}
