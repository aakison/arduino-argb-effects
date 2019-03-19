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

int led = 5;

const int LED_DT = 7;
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 87

#define Fixed int

int maxBright = 140;

struct CRGB leds[Chassis::LedCount];

Chassis c(leds);

#define HUB 4
#define RIM 12
int hub[HUB];
int rim[RIM];

Trapezoid *trapezoid = new Trapezoid(0, 65, 70, 100, 200);

PopEffect pop = PopEffect(leds, 4, 12);

int clock = LOW;

Sequence allLeds(leds, NUM_LEDS, NUM_LEDS);
Sequence topOuter(leds + 4, 12, 12);
Sequence topInner(leds, 4, 4);
Sequence lowerOuter(leds, 32, 12);
Sequence lowerInner(leds + 16, 4, 4);
Sequence figureEight(leds, NUM_LEDS, 24);

Sequence caseLeds(leds + 32, 55, 55);

HueEffect hue(topOuter, 7000);
HueEffect hue2(topInner, 5000);
HueEffect hue4(lowerOuter, 3000);
HueEffect hue3(lowerInner, 2000);

HueEffect caseHue(caseLeds, 10000);

ChaseEffect chase(figureEight, 2500);

SolidEffect allOn(allLeds, CRGB::White);

ChaseEffect countLeds = ChaseEffect(allLeds, 30000);

RotatingHueCaseEffect effect1(c, 5000);
HueEffect effect2(c.AllLeds(), 15000);

// the setup routine runs once when you press reset:
void setup()
{
    // initialize the digital pin as an output.
    pinMode(led, OUTPUT);
    pinMode(3, INPUT);
    LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(maxBright);

    for (int i = 0; i < HUB; ++i)
    {
        hub[i] = HUB - 1 - i;
    }
    for (int i = 0; i < RIM; ++i)
    {
        rim[i] = HUB + i;
    }

    figureEight.Set(15, 7, -1);
    figureEight.Set(30, 2, +1);
    figureEight.Set(20, 10, +1);
    figureEight.Set(8, 5, -1);

}

int effect = 0;
int pressed = 0;

void loop()
{
    long ticks = millis();

    //hue.Update(ticks);
    //pop.Update(ticks);
    //hue2.Update(ticks);
    //hue3.Update(ticks);
    //hue4.Update(ticks);
    //shower.Update(ticks);
    //caseHue.Update(ticks);

    //chase.Update(ticks);

    //countLeds.Update(ticks);

    // allOn.Update(ticks);

    if(effect % 2 == 0) {
        effect1.Update(ticks);
    }
    else {
        effect2.Update(ticks);
    }

    // Alternate high/low in dev to trigger oscilloscope
    clock = (clock == LOW) ? HIGH : LOW;
    //digitalWrite(led, clock);

    int lastPressed = pressed;
    int s = digitalRead(3);
    pressed = s > 0 ? 1 : 0;
    digitalWrite(led, pressed);
    if(pressed == 1 && lastPressed == 0) {
        ++effect;
    }

    // Show the cumulative effect of all the led changes
    FastLED.show();
    //delay(1000);
    delay(4); // No more than 16 to hit 60fps
}
