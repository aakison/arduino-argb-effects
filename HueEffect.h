#ifndef HUEEFFECT_H
#define HUEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"

class HueEffect {
public:

  HueEffect(Sequence& leds, int duration, int offset = 0) : leds(leds)
  {
    this->duration = duration;
    this->offset = offset;
  }

  void Update(long ticks) 
  {
    int hue = InverseLerpLerp(0, duration, 0, 255, (ticks + offset) % duration);
    CRGB color = CHSV(hue, 255, 255);
    for(int i = 0; i < leds.GetCount(); ++i) {
      leds[i] = color;
    }
  }

private:
  Sequence& leds;
  int duration;
  int offset;
};

#endif
