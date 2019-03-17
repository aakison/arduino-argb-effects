#ifndef COLORCIRCLEEFFECT_H
#define COLORCIRCLEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"
#include "Effect.h"
#include "Math.h"

// Given a sequence of LEDs, arranged in a circle, will light them up with all the hues in a rotating color wheel.
class ColorCircleEffect : public Effect {
public:

  // Create a new color wheel, rotating every `duration`ms.  
  // The color red is set to the first LED, unless `offset` by indicated ms.
  ColorCircleEffect(const Sequence& leds, int duration, int offset = 0) 
    : leds(leds)
  {
      this->duration = duration;
      this->offset = offset;
      ledDelta = 255 / leds.GetCount(); // might see a cumulative rounding error for large number of leds.  Adjust if seen.
  }

  // Override of the effect update.
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
