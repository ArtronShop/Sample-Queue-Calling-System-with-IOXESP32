#include <Arduino.h>
#include <IOXESP32Audio.h>

#define NEXT_SW_PIN (0)

unsigned int count = 0;

void setup() {
  Audio.begin(); // Init IOXESP32 Audio shield V2
}

void loop() {
  if (digitalRead(NEXT_SW_PIN) == LOW) {
    while(digitalRead(NEXT_SW_PIN) == LOW) delay(10);
    
    count++; // count up

    Serial.print("call queue ");
    Serial.print(count);
    
    // Gen play list
    String list[10];
    list[0] = "pre-number.mp3";
    if (count < 10) { // 0 - 9
      list[1] = String(count) + ".mp3";
    } else if (count < 99) { // 10 - 99
      if ((count >= 10) && (count <= 19)) { // 1_
        list[1] = "10.mp3";
      } else if ((count >= 20) && (count <= 29)) { // 2_
        list[1] = "20.mp3";
      } else {
        list[1] = String((count / 10) % 10) + ".mp3"; // [3-9]_
        list[2] = "10.mp3";
      }

      if ((count % 10) > 0) { // only do it when last number is 1 - 9
        if ((count % 10) == 1) { // _x1
          list[3] = "x1.mp3";
        } else {
          list[3] = String(count % 10) + ".mp3";
        }
      }
    } else if (count < 999) {
      list[1] = String((count / 100) % 10) + ".mp3"; // x__
      list[2] = "100.mp3";

      if (((count % 100) >= 10) && ((count % 100) <= 19)) { // 1_
        list[3] = "10.mp3";
      } else if (((count % 100) >= 20) && ((count % 100) <= 29)) { // 2_
        list[3] = "20.mp3";
      } else {
        list[3] = String((count / 10) % 10) + ".mp3"; // [3-9]_
        list[4] = "10.mp3";
      }

      if ((count % 10) > 0) { // only do it when last number is 1 - 9
        if ((count % 10) == 1) { // _x1
          list[5] = "x1.mp3";
        } else {
          list[5] = String(count % 10) + ".mp3";
        }
      }
    }
    list[9] = "post-number.mp3";
    
    // Play list
    Serial.print(" (   ");
    for (int i=0;i<10;i++) {
      if (list[i] != "") { // do it if not empty
        Audio.play("SD:/" + list[i]); // start play file in MicroSD Card
        Serial.print(list[i]);
        Serial.print("   ");
        while (Audio.isPlaying()) delay(10); // wait play done
      }
    }

    Serial.println(")");
  }

  delay(10); // make sure other task work
}
