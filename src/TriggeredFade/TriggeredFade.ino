/*
  Triggered Fade

  This code lights up an led that will fade in and out while audio is played from an
  Adafruit Soundboard.
*/

// Pins for the attached LEDs
uint8_t led[] = {
    0, 1, 2, 3, 4, 5, 6, 7
  };
// Initial brightness values for each LED
int16_t brightness[] = {
    -122, -60, 3, 66, 128, 191, 253, 316
  };
// Whether the brightness value is increasing or decreasing
bool isIncreasing[] = {
    true, false, true, false, true, false, true, false
  };
// Amount of attached LEDs, must be changed when LEDs are added or removed
uint8_t ledCount = 8;
uint8_t soundActive = 22;     // Pin that reads whether sound is playing or not
uint8_t fadeAmount = 5;       // How many points to fade the LEDs by
int16_t maxBrightVal = 377;
int16_t minBrightVal = -122;

void setup() {
  // Setup each LED pin to be an output pin
  for (int i = 0; i < ledCount; i++) {
    pinMode(led[i], OUTPUT);
  }
  pinMode(soundActive, INPUT);
}

void loop() {
  for (int i = 0; i < ledCount; i++) {
    // Adafruit Soundboard active pin outputs low when audio is playing
    if (digitalRead(soundActive)){
      // Turn off all LEDs if no audio is playing
      analogWrite(led[i], 0);
    }
    else {
      analogWrite(led[i], brightness[i]);
    }

    // change the brightness for next time
    if (isIncreasing[i]) {
      brightness[i] += fadeAmount;
    }
    else {
      brightness[i] -= fadeAmount;
    }

    // reverse the direction of the fading at the ends of the fade:
    if (brightness[i] <= minBrightVal || brightness[i] >= maxBrightVal) {
      isIncreasing[i] = !isIncreasing[i];
    }
  }

  // wait for 50 milliseconds to set the dimming effect speed
  delay(50);
}
