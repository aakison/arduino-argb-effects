#ifndef CHASSIS_H
#define CHASSIS_H

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

class Chassis {
public:

    static const int LedCount = 87;

    Chassis(CRGB* leds) :
        leds(leds),
        allLeds(leds, 87, 87),
        topFanInnerLeds(leds, 87, 4),
        topFanOuterLeds(leds, 87, 12),
        bottomFanInnerLeds(leds, LedCount, 4),
        bottomFanOuterLeds(leds, 87, 12),
        bodyLeds(leds, 87, 55),
        figureEight(leds, 87, 24)
    {
        topFanInnerLeds.Set(0, 1);
        topFanInnerLeds.Set(3, 3, -1);

        topFanOuterLeds.Set(14, 11, -1);
        topFanOuterLeds.Set(15, 1);

        bottomFanInnerLeds.Set(16, 1);
        bottomFanInnerLeds.Set(19, 3, -1);

        bottomFanOuterLeds.Set(30, 11, -1);
        bottomFanOuterLeds.Set(31, 1);

        bodyLeds.Set(86, 55, -1);

        figureEight.Set(15, 7, -1);
        figureEight.Set(30, 2, +1);
        figureEight.Set(20, 10, +1);
        figureEight.Set(8, 5, -1);

    }

    // All the leds in the entire case.
    const Sequence& AllLeds() const {
        return allLeds;
    }

    // The leds on the inside hub of the top fan, clockwise from top.
    const Sequence& TopFanInnerLeds() const {
        return topFanInnerLeds;
    }

    // The leds on the outside rim of the top fan, clockwise from top.
    const Sequence& TopFanOuterLeds() const {
        return topFanOuterLeds;
    }

    // The leds on the inside hub of the bottom fan, clockwise from top.
    const Sequence& BottomFanInnerLeds() const {
        return bottomFanInnerLeds;
    }

    // The leds on the outside rim of the bottom fan, clockwise from top.
    const Sequence& BottomFanOuterLeds() const {
        return bottomFanOuterLeds;
    }

    // The leds inside the chassis, clockwise from top-left corner.
    const Sequence& BodyLeds() const {
        return bodyLeds;
    }

    const Sequence& FigureEight() const {
        return figureEight;
    }

private:

    CRGB* leds;
    Sequence allLeds;
    Sequence topFanOuterLeds;
    Sequence topFanInnerLeds;
    Sequence bottomFanOuterLeds;
    Sequence bottomFanInnerLeds;
    Sequence bodyLeds;
    Sequence figureEight;
};

#endif
