#ifndef CHASEEFFECT_H
#define CHASEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"

class ChaseEffect {
public:
  ChaseEffect(CRGB* leds, int count, int cycleTime) 
    : inner(0, 100, 200, 500, cycleTime)
  {
      this->leds  = leds;
      this->count = count;
      this->cycleTime = cycleTime;
      offset = cycleTime / count;
  }
  void Update(long ticks) {
    for(int i = 0; i < count; ++i) {
      int brightness = inner.Evaluate(ticks + offset * i);
      leds[i].r = brightness;
      leds[i].g = brightness;
      leds[i].b = brightness;
    }
  }
private:
  Trapezoid inner;
  CRGB* leds;
  int count;
  int cycleTime;
  int offset;
};

#endif
