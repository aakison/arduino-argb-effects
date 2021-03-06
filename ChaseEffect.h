#ifndef CHASEEFFECT_H
#define CHASEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Effect.h"
#include "Trapezoid.h"
#include "Sequence.h"

class ChaseEffect : public Effect {
public:
  ChaseEffect(const Sequence& leds, int cycleTime) 
    : inner(0, 100, 200, 500, cycleTime), leds(leds)
  {
      this->cycleTime = cycleTime;
      offset = cycleTime / leds.GetCount();
  }
  void Update(long ticks) {
    for(int i = 0; i < leds.GetCount(); ++i) {
      int brightness = inner.Evaluate(ticks - offset * i);
      CRGB& led = leds[i];
      led.r = brightness;
      led.g = brightness;
      led.b = brightness;
    }
  }
private:
  const Sequence& leds;
  Trapezoid inner;
  int cycleTime;
  int offset;
};

#endif
