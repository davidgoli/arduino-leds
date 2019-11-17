#include "FastLED.h"
#define NUM_LEDS 75
#define NUM_STRIPS 5
CRGB leds[NUM_STRIPS][NUM_LEDS];

struct Point {
  int val = 0;
  int direction = 1;
  int life = 0;
  int lifespan = 150;
  Point *next;
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

void loop()
{
  updatePoints();

  for (int s = 0; s < NUM_STRIPS; s++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      Point *ptr = pointHead;
      bool set = false;
      do {
        if (i == ptr->val) {
          set = true;
        }
        ptr = ptr->next;
      } while (ptr);

      if (set) {
                double b = 127 * (1 + sin((i * 0.2) + (millis() * 0.00042 * (s + 1))));
        double g = 127 * (1 + sin((i * 0.2) + (millis() * 0.00036 * (s + 1))));
        leds[s][i] = CRGB(
            0,
            g,
            b);
      } else {
        leds[s][i] = CRGB(0, 0, 0);
      }
    }
  }

  FastLED.show();
  delay(60);
}

void updatePoints()
{
  Point *ptr = pointHead;
  Point *prev = 0;

  if ((random() % 10) == 0) {
    Point *newPt = new Point();
    newPt->lifespan = 20 + random() % 10;
    newPt->val = random() % NUM_LEDS;
    newPt->direction = 1;
    append(pointHead, newPt);
  }

  do
  {
    ptr->val += ptr->direction;

    if (ptr->val >= NUM_LEDS) {
      ptr->direction = -1;
    } else if (ptr->val <= 0) {
      ptr->direction = 1;
    }

    if (ptr->life++ >= ptr->lifespan) {
      if (prev == 0) { // this is the head
        if (ptr == pointHead) {
          Point *newHead = pointHead->next;
          if (newHead) {
            delete pointHead;
            pointHead = newHead;
            ptr = pointHead;
          }
        }
      } else {
        prev->next = ptr->next;
        delete ptr;
        ptr = prev->next;
      }
    }

    if (!ptr) {
      break;
    }

    prev = ptr;
    ptr = ptr->next;
  } while (ptr);
}

void append(Point *head, Point *item) {
  while (head->next) {
    head = head->next;
  }

  head->next = item;
}
