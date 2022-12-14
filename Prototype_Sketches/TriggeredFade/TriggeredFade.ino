/*
  Triggered Fade

  This code lights up an led that will fade in and out while audio is played from an
  Adafruit Soundboard.
*/

uint8_t led[] = {
    0, 1, 2, 3, 4, 5, 6
  };         // the PWM pin the LED is attached to
int brightness[] = {
    0, -122, 0, 255, 122, 122, 0
  };  // how bright the LED is
bool isIncreasing[] = {
    false, true, true, false, false, true, false
  };
uint8_t ledCount = 7;
uint8_t soundActive = 22;
int fadeAmount = 5;  // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  for (int i = 0; i < ledCount; i++) {
    pinMode(led[i], OUTPUT);
  }
  pinMode(soundActive, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < ledCount; i++) {
    // Adafruit Soundboard active pin outputs low when audio is playing
    if (digitalRead(soundActive)){
      // set the brightness of pin 9:
      analogWrite(led[i], 0);
    }
    else {
      analogWrite(led[i], brightness[i]);
    }

    // change the brightness for next time through the loop:
    if (isIncreasing[i]) {
      brightness[i] += fadeAmount;
    }
    else {
      brightness[i] -= fadeAmount;
    }

    // reverse the direction of the fading at the ends of the fade:
    if (brightness[i] <= -122 || brightness[i] >= 377) {
      isIncreasing[i] = !isIncreasing[i];
    }
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(50);
}
