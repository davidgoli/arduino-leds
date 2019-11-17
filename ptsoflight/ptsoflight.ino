#include "FastLED.h"
#define NUM_LEDS 75
#define NUM_STRIPS 5
CRGB leds[NUM_STRIPS][NUM_LEDS];

struct Point {
  int val = 0;
  int direction = 1;
};

struct Point *pointHead = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, 0>(leds[0], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 1>(leds[1], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 2>(leds[2], NUM_LEDS);
//  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS); // not working
//  FastLED.addLeds<NEOPIXEL, 4>(leds, NUM_LEDS); // not working
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 6>(leds[4], NUM_LEDS);
//  Serial.begin(9600);
  pointHead = new Point();
}

void loop() {
  if (pointHead->val >= NUM_LEDS) {
    pointHead->direction = -1;
  } else if (pointHead->val <= 0) {
    pointHead->direction = 1;
  }

  pointHead->val += pointHead->direction;

  for (int s=0; s<NUM_STRIPS; s++) {
    for (int i=0; i<NUM_LEDS; i++) {
      if (i == pointHead->val) {
        double b = 127 * (1 + sin((i * 0.2) + (millis() * 0.00042 * (s+1))));
        double g = 127 * (1 + sin((i * 0.2) + (millis() * 0.00036 * (s+1))));
  //      Serial.println(g);
        leds[s][i] = CRGB(
          0,
          g,
          b
        );
      } else {
        leds[s][i] = CRGB(0, 0, 0);
      }
    }
  }

  FastLED.show();
//  delay(10);
}
