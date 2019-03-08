#ifndef HUEEFFECT_H
#define HUEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"

class HueEffect {
public:

  HueEffect(CRGB* leds, int count, int duration, int offset = 0) 
  {
    cycle = new Trapezoid(0, duration / 3, duration / 3, 2 * duration / 3, duration);
    this->leds = leds;
    this->count = count;
    this->duration = duration;
    this->offset = offset;
  }

  void Loop(long ticks) 
  {
    CRGB color;
    color.r = cycle->Evaluate(ticks + offset);
    color.g = cycle->Evaluate(ticks + offset + duration / 3);
    color.b = cycle->Evaluate(ticks + offset + 2 * duration / 3);
    for(int i = 0; i < count; ++i) {
      leds[i] = color;
    }
    
  }

private:
  Trapezoid* cycle;
  CRGB* leds;
  int count;
  int duration;
  int offset;
};

#endif
