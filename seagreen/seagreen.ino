#include "FastLED.h"

#define NUM_LEDS 75

// range 0-255
#define BRIGHTNESS 32

CRGB leds[NUM_LEDS];

void setup() {
  // save memory by reusing the same data on all strips
  FastLED.addLeds<NEOPIXEL, 0>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 1>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 4>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 5>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
//  Serial.begin(9600);
}

void loop() {
  for (int i=0; i<NUM_LEDS; i++) {
    double b = BRIGHTNESS * (1 + sin((i * 0.2) + (millis() * 0.00042)));
    double g = BRIGHTNESS * (1 + sin((i * 0.2) + (millis() * 0.00036)));
//      Serial.println(g);
    leds[i] = CRGB(
      g,
      0,
      b
    );
  }

  FastLED.show();
//  delay(10);
}
