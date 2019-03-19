#ifndef ROTATINGHUECASEEFFECT_H
#define ROTATINGHUECASEEFFECT_H

#include <pixeltypes.h>
#include "CompositeEffect.h"
#include "ColorCircleEffect.h"
#include "Chassis.h"

// A complete case effect that has the front fans rotating in a hue in opposite directions.
// The body lighting rotates as well, but not being round this portion is more subtle.
// WARNING: It is expected that a single global of this object is created, no attempt made to deallocate memory.
class RotatingHueCaseEffect : public CompositeEffect {
public:
    RotatingHueCaseEffect(const Chassis& chassis, int duration) 
      : CompositeEffect(5)
    {
        const int offset = (int)((long)duration * 7 / 16);

        Add(*(new ColorCircleEffect(chassis.TopFanInnerLeds(), duration)));
        Add(*(new ColorCircleEffect(chassis.TopFanOuterLeds(), duration)));

        Sequence* innerCC = new Sequence(chassis.BottomFanInnerLeds());
        Sequence* outerCC = new Sequence(chassis.BottomFanOuterLeds());
        innerCC->Reverse();
        outerCC->Reverse();

        Add(*(new ColorCircleEffect(*innerCC, duration, offset)));
        Add(*(new ColorCircleEffect(*outerCC, duration, offset)));

        Add(*(new ColorCircleEffect(chassis.BodyLeds(), duration)));

    }

};

#endif
