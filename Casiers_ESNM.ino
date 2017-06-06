/*
  _____________________________________
  |   LIVRES    | NOUVEAU | MULTIMEDIA  |
  |             |         |             |
  |     1       |    2    |      3      |
  _____________________________________
  |    MODE DECO    |      DIVERS       |
  |                 |                   |
  |       4         |        5          |
  _____________________________________
  |                                     |
  |                                     |
  |                                     |
  |                                     |
  |                                     |
*/



#include "FastLED.h"

#define NUM_LEDS_PER_STRIP_L 55
#define NUM_LEDS_PER_STRIP_M 39
#define NUM_LEDS_PER_STRIP_S 28

#define LIVRES_PIN 8
#define NOUVEAUTES_PIN 9
#define MULTIMEDIA_PIN 10
#define MODEDECO_PIN 11
#define DIVERS_PIN 12

#define MOTION_PIN 7
#define LED_PIN 13

CRGB LivresLeds[NUM_LEDS_PER_STRIP_M]; // Initialize led array 1
CRGB NouveautesLeds[NUM_LEDS_PER_STRIP_S]; // Initialize led array 2
CRGB MultimediaLeds[NUM_LEDS_PER_STRIP_M]; // Initialize led array 3
CRGB ModeDecoLeds[NUM_LEDS_PER_STRIP_L]; // Initialize led array 4
CRGB DiversLeds[NUM_LEDS_PER_STRIP_L]; // Initialize led array 5

boolean motion = false; //is someone moving ? true if someone is present
boolean state = false; //is it turned on ? true = it is white

void setup() {

  delay (2000);

  FastLED.setBrightness(100); // limit brightness

  pinMode(MOTION_PIN, INPUT_PULLUP);  //set pin to up and enable pull up
  pinMode(LED_PIN, OUTPUT); // set pin to out

  FastLED.addLeds<WS2812B, LIVRES_PIN>(LivresLeds, NUM_LEDS_PER_STRIP_M);
  FastLED.addLeds<WS2812B, NOUVEAUTES_PIN>(NouveautesLeds, NUM_LEDS_PER_STRIP_S);
  FastLED.addLeds<WS2812B, MULTIMEDIA_PIN>(MultimediaLeds, NUM_LEDS_PER_STRIP_M);
  FastLED.addLeds<WS2812B, MODEDECO_PIN>(ModeDecoLeds, NUM_LEDS_PER_STRIP_L);
  FastLED.addLeds<WS2812B, DIVERS_PIN>(DiversLeds, NUM_LEDS_PER_STRIP_L);

  fill_solid(LivresLeds, NUM_LEDS_PER_STRIP_M, CRGB::Green); // Set all to red.
  fill_solid(NouveautesLeds, NUM_LEDS_PER_STRIP_S, CRGB::White); // Set all to white
  fill_solid(MultimediaLeds, NUM_LEDS_PER_STRIP_M, CRGB::Yellow); // Set all to Yellow
  fill_solid(ModeDecoLeds, NUM_LEDS_PER_STRIP_L, CRGB::Blue); // Set all to blue
  fill_solid(DiversLeds, NUM_LEDS_PER_STRIP_L, CRGB::Red); // Set all to green

  FastLED.show();

  delay (1000);
}

void loop() {

  motion = digitalRead(MOTION_PIN);

  if (motion == true) // If the sensor's output goes low, motion is detected
  {
    digitalWrite(LED_PIN, HIGH);
    if (state == false) { // Light is off

      //animate to white
      toWhite();

      state = true;
      delay(15000); // just played animation wait 5 sec

    } else {
      delay(5000); // still someone here wait 2 sec
    }
  }
  else // no motion detected
  {
    digitalWrite(LED_PIN, LOW);
    if (state == true) { // Light is on
      
      //set usual colors
      fadeToColor();

      state = false;
      delay (5000); // just switched to usual colors wait 5 sec
    } else {
      delay(300); //no motion detected and usual colors are on, just continue detecting
    }
  }


}


void toWhite() {

  for (short dot = 0; dot < NUM_LEDS_PER_STRIP_L; dot++) {
    if (dot < NUM_LEDS_PER_STRIP_M) {
      LivresLeds[dot] = CRGB::White;
      MultimediaLeds[dot] = CRGB::White;
    }
    ModeDecoLeds[dot] = CRGB::White;
    DiversLeds[dot] = CRGB::White;

    fill_solid(NouveautesLeds, NUM_LEDS_PER_STRIP_S, CRGB::Black);
    FastLED.show();
    delay(20);
    fill_solid(NouveautesLeds, NUM_LEDS_PER_STRIP_S, CRGB::White);
    FastLED.show();
    delay(10);
  }

    for (short blink = 0; blink <6;blink++){
    fill_solid(LivresLeds, NUM_LEDS_PER_STRIP_M, CRGB::Black);
    fill_solid(NouveautesLeds, NUM_LEDS_PER_STRIP_S, CRGB::Black);
    fill_solid(MultimediaLeds, NUM_LEDS_PER_STRIP_M, CRGB::Black);
    fill_solid(ModeDecoLeds, NUM_LEDS_PER_STRIP_L, CRGB::Black);
    fill_solid(DiversLeds, NUM_LEDS_PER_STRIP_L, CRGB::Black);
    FastLED.show();
    delay(40);
    fill_solid(LivresLeds, NUM_LEDS_PER_STRIP_M, CRGB::White);
    fill_solid(NouveautesLeds, NUM_LEDS_PER_STRIP_S, CRGB::White);
    fill_solid(MultimediaLeds, NUM_LEDS_PER_STRIP_M, CRGB::White);
    fill_solid(ModeDecoLeds, NUM_LEDS_PER_STRIP_L, CRGB::White);
    fill_solid(DiversLeds, NUM_LEDS_PER_STRIP_L, CRGB::White);
    FastLED.show();
    delay(20);
    }
}


void fadeToColor() {
  for (short col = 0; col < 255; col++) {

    for (short dot = 0; dot < NUM_LEDS_PER_STRIP_L; dot++) {
      if (dot < NUM_LEDS_PER_STRIP_M) {
        LivresLeds[dot].red -= 1;
        LivresLeds[dot].blue -= 1;
        MultimediaLeds[dot].blue -= 1;
      }
      ModeDecoLeds[dot].red -= 1;
      ModeDecoLeds[dot].green -= 1;
      DiversLeds[dot].green -= 1;
      DiversLeds[dot].blue -= 1;

    }
    FastLED.show();
    delay(10);
  }
}






























