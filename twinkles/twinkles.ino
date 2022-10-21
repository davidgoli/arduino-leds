#include "FastLED.h"

#define NUM_LEDS 75

// range 0-255
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

struct Twinkle {
  long duration;
  float intensity;
  long darkInterval;
  long startTime;
  int ledNum;
};

#define NUM_TWINKLES 10

struct Twinkle twinkles[NUM_TWINKLES];

void setup() {
  // save memory by reusing the same data on all strips
  FastLED.addLeds<NEOPIXEL, 0>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 1>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 4>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 5>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  Serial.begin(9600);

  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = 0;
  }

  for (int i=0; i<NUM_TWINKLES; i++) {
    initializeTwinkle(twinkles, i);
  }
}

void loop() {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  twinkly(1);
  bisexual(sin(10000 + (millis() / 60000))+1);

  FastLED.show();
//  delay(10);
}

bool ledOccupied(Twinkle twinkles[], int ledNum) {
  for (int i=0; i<NUM_TWINKLES; i++) {
    if (twinkles[i].ledNum == ledNum) {
      return true;
    }
  }

  return false;
}

void initializeTwinkle(Twinkle twinkles[], int i) {
  twinkles[i].duration = random(2000, 10000);
  int ledNum = random(0, NUM_LEDS);
  do {
    ledNum += 1;
  } while (ledOccupied(twinkles, ledNum));
  twinkles[i].ledNum = ledNum;

  twinkles[i].intensity = random(BRIGHTNESS / 2, BRIGHTNESS);
  twinkles[i].startTime = millis();
  twinkles[i].darkInterval = random(0, 1000);
}

void twinkly(float factor) {
  for (int i=0; i<NUM_TWINKLES; i++) {
    Twinkle twinkle = twinkles[i];
    float age = millis() - twinkle.startTime;
    float maxAge = twinkle.duration + twinkle.darkInterval;
    if (age > maxAge+10) {
      initializeTwinkle(twinkles, i);
      continue;
    }

    float maxPt = twinkle.duration * 0.5;
    float b = max(0, (1.0 - (abs(age - maxPt) / maxPt)) * (float)twinkle.intensity);

    leds[twinkle.ledNum] += CHSV(0, 0, b * factor);
    if (i == 10) {
      Serial.println(b);
    }
  }
}

void bisexual(float factor) {
  for (int i=0; i<NUM_LEDS; i++) {
    double b = 32 * max(0, sin((i * 0.2) + (millis() * 0.00042)));
    double r = 32 * max(0, sin((i * 0.2) + (millis() * 0.00036)));
    double g = 32 * max(0, sin((i * 0.2) + (millis() * 0.00031)));

  //      Serial.println(g);
    leds[i] += CRGB(
      r * factor,
      g,
      b * factor
    );
  }
}
