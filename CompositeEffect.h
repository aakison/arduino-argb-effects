#ifndef COMPOSITEEFFECT_H
#define COMPOSITEEFFECT_H

#include "Effect.h"

class CompositeEffect : public Effect {
public:
    CompositeEffect(int count) : 
        effectCount(count),
        effects(new Effect*[count]),
        current(0)
    {
        for(int i = 0; i < count; ++i) {
            effects[i] = 0;
        }
    }

    void Add(Effect& effect) {
        effects[current] = &effect;
        current = (current + 1) % effectCount;
    }

    void Update(long ticks) {
        for(int i = 0; i < effectCount; ++i) {
            Effect* effect = effects[i];
            if(effect != 0) {
                effect->Update(ticks);
            }
        }
    }

private:
    Effect** effects;
    int effectCount;
    int current;
};

#endif
