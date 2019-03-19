#ifndef HUEEFFECT_H
#define HUEEFFECT_H

#include <pixeltypes.h>
#include <FastLED.h>

#include "Effect.h"

// A simple effect that updates the hue of all leds in a sequence in sync.
class HueEffect : public Effect {
  public:
    HueEffect(const Sequence &leds, int duration, int offset = 0)
        : leds(leds),
        duration(duration),
        offset(offset)
    {
    }

    void Update(long ticks)
    {
        int hue = InverseLerpLerp(0, duration, 0, 255, (ticks + offset) % duration);
        CRGB color = CHSV(hue, 255, 255);
        for (int i = 0; i < leds.GetCount(); ++i)
        {
            leds[i] = color;
        }
    }

  private:
    const Sequence &leds;
    int duration;
    int offset;
};

#endif
