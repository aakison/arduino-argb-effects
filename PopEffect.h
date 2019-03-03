#ifndef POPEFFECT_H
#define POPEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Trapezoid.h"

class PopEffect {
public:
  PopEffect(CRGB* leds, int innerCount, int outerCount) :
    inner(0, 2500, 2600, 2800, 3500),
    outer(2500, 2700, 2750, 3500, 3500) {
      innerLeds = leds;
      this->innerCount = innerCount;
      outerLeds = &leds[innerCount];
      this->outerCount = outerCount;
  }
  void Loop(long ticks) {
    int innerBrightness = inner.Evaluate(ticks);
    int outerBrightness = outer.Evaluate(ticks);
    for(int i = 0; i < innerCount; ++i) {
      innerLeds[i].r = innerBrightness;
      innerLeds[i].g = innerBrightness;
      innerLeds[i].b = innerBrightness;
    }
    for(int i = 0; i < outerCount; ++i) {
      outerLeds[i].r = outerBrightness;
      outerLeds[i].g = outerBrightness;
      outerLeds[i].b = outerBrightness;
    }
    FastLED.show();
  }
private:
  Trapezoid inner;
  Trapezoid outer;
  CRGB* innerLeds;
  int innerCount;
  CRGB* outerLeds;
  int outerCount;
};

#endif
