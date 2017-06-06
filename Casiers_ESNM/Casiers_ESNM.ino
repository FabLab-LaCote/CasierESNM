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

// Définition du nombre de leds par rapport à la taille du comportiment
#define NUM_LEDS_PER_STRIP_L 55 // Grand
#define NUM_LEDS_PER_STRIP_M 39 // Moyen
#define NUM_LEDS_PER_STRIP_S 28 // Petit

// Définition des pins de sortie pour chaque compartiment
#define LIVRES_PIN 8
#define NOUVEAUTES_PIN 9
#define MULTIMEDIA_PIN 10
#define MODEDECO_PIN 11
#define DIVERS_PIN 12

#define LED_PIN 13 // Pin pour debug

// Définition des pins d'entrée
#define MOTION_PIN 7 //Capteur PIR


// Initialisation des array
CRGB LivresLeds[NUM_LEDS_PER_STRIP_M];      // array 1
CRGB NouveautesLeds[NUM_LEDS_PER_STRIP_S];  // array 2
CRGB MultimediaLeds[NUM_LEDS_PER_STRIP_M];  // array 3
CRGB ModeDecoLeds[NUM_LEDS_PER_STRIP_L];    // array 4
CRGB DiversLeds[NUM_LEDS_PER_STRIP_L];      // array 5

// Initialisation du détecteur
boolean motion = false; //Est-ce que quelqu'un bouge? true si quelqu'un est présent
boolean state = false; //Est-ce allumé? true = it is white

void setup() {

  delay (2000);

  FastLED.setBrightness(100); // limite l'intensité

  pinMode(MOTION_PIN, INPUT_PULLUP);  //Défini la pin comme une entrée avec PullUp
  pinMode(LED_PIN, OUTPUT); // Défini la pin comme sortie

  // Initialisation des leds
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

  // Si mouvement détecté
  if (motion == true)
  {
    digitalWrite(LED_PIN, HIGH);
    if (state == false) { // La lumière est éteinte

      toWhite(); // Jouer l'animation toWhite (Blanche)

      state = true;
      delay(15000); // Jouer l'animation et attendre 15 secondes

    } else {
      delay(5000); // Quelqu'un encore présent, attendre 5 secondes
    }
  }
  
  // Si pas de mouvement détecté
  else
  {
    digitalWrite(LED_PIN, LOW);
    if (state == true) { // Light is on
      
      //set usual colors
      fadeToColor();

      state = false;
      delay (5000); // Bascule sur les couleurs standard - Attendre 5 secondes
    } else {
      delay(300); //Pas de mouvement détecté. Couleurs allumées, continue la détection
    }
  }


}

//==== ANIMATIONS ===== 

// Clignote blanc quelques secondes et reste fixe
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

// Allume les couleurs par dégradé d'intensité puis reste fixe
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






























