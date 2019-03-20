#ifndef CONTRASTINGHUECASEEFFECT_H
#define CONTRASTINGHUECASEEFFECT_H

#include <pixeltypes.h>
#include "CompositeEffect.h"
#include "HueEffect.h"
#include "Chassis.h"

// A complete case effect that has the front fans rotating in a hue in opposite directions.
// The body lighting rotates as well, but not being round this portion is more subtle.
// WARNING: It is expected that a single global of this object is created, no attempt made to deallocate memory.
class ContrastingHueCaseEffect : public CompositeEffect {
public:
    ContrastingHueCaseEffect(const Chassis& chassis, int duration) 
      : CompositeEffect(5)
    {
        Add(*(new HueEffect(chassis.TopFanInnerLeds(), duration, duration)));
        Add(*(new HueEffect(chassis.TopFanOuterLeds(), duration, duration / 2)));

        Add(*(new HueEffect(chassis.BottomFanInnerLeds(), duration, duration / 4)));
        Add(*(new HueEffect(chassis.BottomFanOuterLeds(), duration, duration / 4 * 3)));

        Add(*(new HueEffect(chassis.BodyLeds(), 2 * duration, duration)));
    }

};

#endif
