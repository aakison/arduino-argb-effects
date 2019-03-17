#ifndef SOLIDEFFECT_H
#define SOLIDEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

class SolidEffect {
public:
  SolidEffect(Sequence& leds, CRGB color) 
    : leds(leds)
  {
      this->color = color;
  }
  void Update(long ticks) {
    for(int i = 0; i < leds.GetCount(); ++i) {
      CRGB& led = leds[i];
      led.r = color.r;
      led.g = color.g;
      led.b = color.b;
    }
  }
private:
  Sequence& leds;
  CRGB color;
};

#endif
