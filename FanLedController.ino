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

#include "Trapezoid.h"
#include "PopEffect.h"
#include "HueEffect.h"

int led = 11;

const int LED_DT = 7;
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 32

#define Fixed int

int maxBright = 140;

struct CRGB leds[NUM_LEDS];

#define HUB 4
#define RIM 12
int hub[HUB];
int rim[RIM];

Trapezoid* trapezoid = new Trapezoid(0, 65, 70, 100, 200);

PopEffect pop = PopEffect(leds, 4, 12);
HueEffect hue = HueEffect(leds, 4, 7000);
HueEffect hue2 = HueEffect(leds + 4, 12, 5000);
HueEffect hue4 = HueEffect(leds + 16, 4, 3000);
HueEffect hue3 = HueEffect(leds + 20, 12, 2000);

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(maxBright);

  for(int i = 0; i < HUB; ++i) {
    hub[i] = HUB - 1 - i;
  }
  for(int i = 0; i < RIM; ++i) {
    rim[i] = HUB + i;
  }
}

int clock = LOW; 

void loop() {
  long ticks = millis();

  hue.Loop(ticks);
  //pop.Loop(ticks);
  hue2.Loop(ticks);
  hue3.Loop(ticks);
  hue4.Loop(ticks);
  //chaseLoop(ticks);
  clock = (clock == LOW) ? HIGH : LOW;

  digitalWrite(led, clock);
  FastLED.show();

  delay(4); // No more than 16 to hit 60fps
}


void popLoop(long ticks) {
  
}

void chaseLoop(long ticks) {
  leds[0].r = trapezoid->Evaluate(ticks + 00);
  leds[1].r = trapezoid->Evaluate(ticks + 50);
  leds[2].r = trapezoid->Evaluate(ticks + 100);
  leds[3].r = trapezoid->Evaluate(ticks + 150);

  for(int i = 4; i < 16; ++i) {
    leds[i].g = trapezoid->Evaluate(ticks + -12 * i);
  }
  FastLED.show();
}
