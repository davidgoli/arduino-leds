#include "FastLED.h"
#define NUM_LEDS 75
#define NUM_STRIPS 5
CRGB leds[NUM_STRIPS][NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, 0>(leds[0], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 1>(leds[1], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 2>(leds[2], NUM_LEDS);
//  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS); // not working
//  FastLED.addLeds<NEOPIXEL, 4>(leds, NUM_LEDS); // not working
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 6>(leds[4], NUM_LEDS);
//  Serial.begin(9600);
}

void loop() {
  for (int s=0; s<NUM_STRIPS; s++) {
    for (int i=0; i<NUM_LEDS; i++) {
      double b = 127 * (1 + sin((i * 0.2) + (millis() * 0.0042 * (s+1))));
      double g = 127 * (1 + sin((i * 0.2) + (millis() * 0.0036 * (s+1))));
//      Serial.println(g);
      leds[s][i] = CRGB(
        0,
        g,
        b
      );
    }
  }

  FastLED.show();
//  delay(10);
}
