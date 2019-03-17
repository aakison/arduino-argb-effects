#ifndef CASE_H
#define CASE_H

#include "Sequence.h"

/*
Wiring of Corsair Fans in front of case and strip lighting on side: 
86
  85
    84
      ..
        ..
          ..
            70
              69
                68  
                  67
                                   14
                  66         15          13
  
                  65    04                    12
                                   00
                  .. 
                      05       01      03       11
                  ..
                                   02
                  ..    06                    10
                    
                  ..         07          09
                                   08
                  ..
                                   30
                  ..         31          29
  
                  ..    20                    28
32                                 16
  33              .. 
    34                21       17      19       27
      ..          ..
        ..                         18
          ..      53    22                    26
            48      
              49  52         23          25
                50                 24
                  51

*/

class Case {
public:
    Case(CRGB* leds) :
        leds(leds),
        allLeds(leds, 87, 87),
        topFanOuterLeds(leds, 87, 12),
        topFanInnerLeds(leds, 87, 4)
    {
        topFanInnerLeds.Set(0, 1);
        topFanInnerLeds.Set(3, 3, -1);

        topFanOuterLeds.Set(14, 11, -1);
        topFanOuterLeds.Set(15, 1);
    }

    static const int LedCount = 87;

    // The leds on the outside rim of the top fan, clockwise from top.
    const Sequence& TopFanOuterLeds() {
        return topFanOuterLeds;
    }

    // The leds on the inside hub of the top fan, clockwise from top.
    const Sequence& TopFanInnerLeds() {
        return topFanInnerLeds;
    }

private:

    CRGB* leds;
    Sequence allLeds;
    Sequence topFanOuterLeds;
    Sequence topFanInnerLeds;
};

#endif