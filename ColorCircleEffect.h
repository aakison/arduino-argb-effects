#ifndef COLORCIRCLEEFFECT_H
#define COLORCIRCLEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"

class ColorCircleEffect {
public:
  ColorCircleEffect(const Sequence& leds, int duration, int offset = 0) 
    : leds(leds)
  {
      this->duration = duration;
      this->offset = offset;
      ledDelta = 255 / leds.GetCount(); // might see a cumulative rounding error for large number of leds.  Adjust if seen.
  }
  void Update(long ticks) {
    int hue = InverseLerpLerp(0, duration, 255, 0, (ticks + offset) % duration);
    for(int i = 0; i < leds.GetCount(); ++i) {
      CRGB color = CHSV(hue, 255, 255);
      leds[i] = color;
      hue = (hue + ledDelta) % 255;
    }
  }
private:
  const Sequence& leds;
  int duration;
  int offset;
  int ledDelta;
};

#endif
