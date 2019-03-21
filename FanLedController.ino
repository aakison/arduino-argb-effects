#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#include "Sequence.h"
#include "Trapezoid.h"
#include "PopEffect.h"
#include "HueEffect.h"
#include "ChaseEffect.h"
#include "SolidEffect.h"
#include "ColorCircleEffect.h"
#include "Chassis.h"
#include "CompositeEffect.h"
#include "RotatingHueCaseEffect.h"
#include "ContrastingHueCaseEffect.h"

const int switchPin = 3;
const int onboardLedPin = 5;
const int argbSignalPin = 7;
const int maxBright = 255;

CRGB leds[Chassis::LedCount];

Chassis c(leds);

PopEffect pop = PopEffect(leds, 4, 12);

int clock = LOW;

RotatingHueCaseEffect effect1(c, 5000);
HueEffect effect2(c.AllLeds(), 15000);
ContrastingHueCaseEffect effect3(c, 7000);
ChaseEffect effect4(c.AllLeds(), 3000);
ChaseEffect effect5(c.FigureEight(), 2000);

int effect = 0;

void setup()
{
    // initialize the digital pin as an output.
    pinMode(onboardLedPin, OUTPUT);
    pinMode(switchPin, INPUT);
    LEDS.addLeds<WS2812B, argbSignalPin>(leds, Chassis::LedCount);
    FastLED.setBrightness(maxBright);

    // Read a floating analog pin to get a random start value
    effect = analogRead(A3);
}

int pressed = 0;

Effect effects[] = { effect1, effect2, effect3, effect4 };

void loop()
{
    long ticks = millis();

    if(effect % 5 == 0) {
        effect1.Update(ticks);
    }
    else if(effect % 5 == 1) {
        effect2.Update(ticks);
    }
    else if(effect %5 == 2 ) {
        effect3.Update(ticks);
    }
    else if(effect % 5 == 3) {
        effect4.Update(ticks);
    }
    else {
        effect5.Update(ticks);
    }

    // Alternate high/low in dev to trigger oscilloscope
    clock = (clock == LOW) ? HIGH : LOW;
    digitalWrite(onboardLedPin, clock);

    // Check switch to move to next effect.
    int lastPressed = pressed;
    int s = digitalRead(switchPin);
    pressed = s > 0 ? 1 : 0;
    if(pressed == 1 && lastPressed == 0) {
        ++effect;
    }

    // Show the cumulative effect of all the led changes
    FastLED.show();
    delay(4); // No more than 16 to hit 60fps, at least 2-4 to debounce switch logic above.
}
