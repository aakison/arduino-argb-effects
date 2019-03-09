#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <pixeltypes.h>

// Represents a sequence of LEDs in order.
class Sequence {
public:
    // Create an initial sequence with the set of LEDs coming in, the count of LEDs, and the length of the sequence.
    Sequence(CRGB* leds, int count, int sequenceCount) {
        this->sequenceCount = sequenceCount;
        allLeds = leds;
        this->count = count;
        int *a = new int[sequenceCount];
        ledIndex = a;
        for(int i = 0; i < sequenceCount; ++i) {
            int ledOffset = i % count;
            ledIndex[i] = ledOffset;
        }
        setPos = 0;
    }

    // Sets a specifc sequence from within the list of known LEDs.
    // Call this multiple times to string together LEDs in a sequence that aren't contiguous on the strip.
    void Set(int index, int run, int step = 1) {
        for(int i = setPos, remote = index; i < setPos + run; ++i, remote += step) {
            int local = i % sequenceCount;
            remote = remote % count;
            ledIndex[local] = remote;
        }
    }

    // Access the color information for the LED at the given position in this sequence.
    CRGB& operator[](int index) {
        int indirect = ledIndex[index];
        return allLeds[indirect];
    } 

    // Returns the count of elements in this sequence
    int GetCount() {
        return sequenceCount;
    }
private:
    CRGB* allLeds;
    int count;
    int* ledIndex;
    int sequenceCount;
    int setPos;
};

#endif
