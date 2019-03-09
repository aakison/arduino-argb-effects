#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <pixeltypes.h>

// Represents a sequence of LEDs in order.
class Sequence {
public:
    // Create an initial sequence with the set of LEDs coming in, the count of LEDs, and the length of the sequence.
    Sequence(CRGB* leds, int ledCount, int sequenceCount) {
        allLeds = leds;
        this->ledCount = ledCount;

        sequence = new int[sequenceCount];
        this->sequenceCount = sequenceCount;

        for(int i = 0; i < sequenceCount; ++i) {
            int ledOffset = i % ledCount;
            sequence[i] = ledOffset;
        }

        sequenceIndex = 0;
    }

    // Sets a specifc sequence from within the list of known LEDs.
    // Call this multiple times to string together LEDs in a sequence that aren't contiguous on the strip.
    void Set(int index, int run, int step = 1) {
        int ledIndex = index;
        for(int i = 0; i < run; ++i) {
            sequence[sequenceIndex] = ledIndex;
            sequenceIndex = (sequenceIndex + 1) % sequenceCount;
            ledIndex = (ledIndex + step) % ledCount;
        }
    }

    // Access the color information for the LED at the given position in this sequence.
    CRGB& operator[](int index) {
        int indirect = sequence[index];
        return allLeds[indirect];
    } 

    // Returns the count of elements in this sequence
    int GetCount() {
        return sequenceCount;
    }

private:
    CRGB* allLeds;
    int ledCount;
    int* sequence;
    int sequenceCount;
    int sequenceIndex;
};

#endif
