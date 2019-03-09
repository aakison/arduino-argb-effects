#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <pixeltypes.h>

class Sequence {
public:
    Sequence(CRGB* leds, int count, int sequenceCount) {
        allLeds = leds;
        this->count = count;
        for(int i = 0; i < sequenceCount; ++i) {
            int ledOffset = i % count;
            sequence[i] = leds + ledOffset;
        }
    }
    CRGB* operator[](int index) {
        return sequence[index];
    } 
    int GetCount() {
        return sequenceCount;
    }
private:
    CRGB* allLeds;
    int count;
    CRGB** sequence;
    int sequenceCount;
};

#endif