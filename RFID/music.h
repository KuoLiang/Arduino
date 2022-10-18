#include "pitches.h"

void music() {
  // 建立要發音的音色陣列
  int Notes[25] = {
    NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, 
    NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
    NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, 
    NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5
  };
  
    for(int i=0; i<3; i++){
      tone(12, Notes[i], 100); // 從第12Pin發聲,發出100ms的聲音
      //delay(100);
    }
}
