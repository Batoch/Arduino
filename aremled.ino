#include <FastLED.h>
#define NUM_LEDS 144
#define Intervalle 1
#define tmax 5000
#define buzzerPin 6
#define j1  2
#define j2  3
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
// Pin 2 pour interruption 0     ou    Pin 21 pour interruption 2     ou      Pin 18 pour interruption 4
// Pin 3 pour interruption 1     ou    Pin 20 pour interruption 3     ou      Pin 19 pour interruption 5
int mode = 0;
int sens = 1;
int led = 0;
int gagnant = 0;
int delai = 0;
int ledp1 = 0;
int ledp2 = 144;
int choixmode = 0;
int appuip1 = 0;
int appuip2 = 0;
#define LED_PIN     5
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define p1 1
#define p2 -1




CRGB leds[NUM_LEDS];



void setup() {
  Serial.begin(115200);                                            // configuration de la vitesse de connexion série : 115200 bauds (ou bits par seconde)
  Serial.println("fghjkl");

  delay(100);
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  pinMode(j1, INPUT);
  pinMode(j2, INPUT);

  attachInterrupt(0, boutonp1, RISING);
  attachInterrupt(1, boutonp2, RISING);





}






void loop() {
  mode = 0;
  choixmode = 0;
  veille();
  Serial.println(choixmode);
  switch (choixmode) {
    case 1:
      black();
      spam();
      Serial.println("fin mode spam");
      delay(3000);
      choixmode = 0;
      break;
    case 2:
      black();
      tapetaupe();
      delay(2000);
      choixmode = 0;
      break;
    case 0:
      break;

  }




}


void spam() {
  mode = 2;
  Serial.println("debut spam");
  ledp1 = 0;
  ledp2 = 143;
  leds[71] = CHSV(100, 255, 255);
  while (ledp1 < 71 && ledp2 > 71)
  {
    alumerled(ledp1);
    alumerled(ledp2);

  }
  black();
  Serial.println("fin spam, annonce");
  if (ledp1 > 70) {
    victoire(p1);
  }
  else if (ledp2 < 72) {
    victoire(p2);
  }
  else {
    victoire(p1);
    victoire(p2);
  }
  Serial.println("fin spam");
  return;

}

void Pong1D() {
  mode = 1;
  sens = 1;
  led = 1;
  delai = 30000;
  gagnant = 0;
  while (gagnant == 0) {
    led = led + sens;
    Serial.println(led);
    alumerlednoir(led);
    delayMicroseconds(delai);
    if (led == 143) {
      victoire(p1);
      gagnant = 1;
    }
    else if (led == 0) {
      victoire(p2);
      gagnant = 1;
    }
  }
  led = 0;


}


void tapetaupe() {
  mode = 3;
  int joueurgagnant = 0;
  int score1 = 0;
  int score2 = 0;
  appuip1 = 0;
  appuip2 = 0;
  for (int nb_jeux = 0; nb_jeux < 5; nb_jeux++) {

    //choix et affichage sur les leds après un tmps aleatoire
    CRGB couleur = CHSV(random8(), 255, 255);
    delay(random(200, 5000));
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = couleur;
    }
    FastLED.show();

    if (appuip1 == 1) {
      score2++;
      annimationgg(2);
      delay(500);
    }
    else if (appuip2 == 1) {
      score1++;
      annimationgg(1);
      delay(500);
    }
    else
    {
      int t0 = millis();
      while (appuip1 == 0 and appuip2 == 0)
      {
        Serial.println(appuip1);
        Serial.println(appuip2);
      }
      int tpsreaction = millis() - t0; // à faire quelque chose avec...
      if (appuip1 == 1) {
        score1++;
        annimationgg(1);
        delay(500);
      }
      else {
        score2++;
        annimationgg(2);
        delay(500);
      }
    }

  appuip1 = 0;
  appuip2 = 0;
  black();
    delay(150);
  }
  black();
  if(score1>score2){
    victoire(p1);
  }
  else{
    victoire(p2);
  }
}




void victoire(int joueurgagnant){
for (int j = 0; j < 15; j++) {
  CRGB couleur = CHSV( random8(), 255, 255);

  if (joueurgagnant == 1) {
    for ( int i = 0; i < NUM_LEDS / 2; i++) leds[i] = couleur;
    for ( int i = NUM_LEDS / 2; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
  }
  else {
    for ( int i = NUM_LEDS / 2; i < NUM_LEDS ; i++) leds[i] = couleur;
    for ( int i = 0; i < NUM_LEDS / 2; i++) leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(150);
}
}



void annimationgg(int joueur) {
  if (joueur == 1) {
    leds[1] = CRGB::Blue;
    leds[2] = CRGB::Blue;
    leds[3] = CRGB::Blue;
    FastLED.show();
  }
  else {
    leds[140] = CRGB::Blue;
    leds[141] = CRGB::Blue;
    leds[142] = CRGB::Blue;
    FastLED.show();
  }

}

void black() {
  for (int i = 0; i < 144; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
void alumerlednoir(int led) {
  leds[led] = CHSV(led, 255, 255);
  FastLED.show();
  leds[led] = CRGB::Black;
}

void alumerled(int led) {
  leds[led] = CHSV(abs(led), 255, 255);
  FastLED.show();
  Serial.println(led);
  return;
}


void veille()
{
  // draw a generic, no-name rainbow
  static uint8_t starthue = 0;
  fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);

  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (40 * 2);
  if ( secs < 40) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
    leds[0] = TEMPERATURE_1; // show indicator pixel
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
    leds[0] = TEMPERATURE_2; // show indicator pixel
  }


  FastLED.show();
  FastLED.delay(8);
}




void boutonp1() {
  switch (mode) {
    case 0:
      choixmode = 1;
    case 1:
      if (led < 10) {
        sens = 1;
        delai -= 100;
      }
      else {
        gagnant = 1;
        victoire(p2);
      }
      break;
    case 2:
      ledp1++;
      break;
    case 3:
      appuip1 = 1;
      break;
  }
}

void boutonp2() {
  switch (mode) {
    case 0:
      choixmode = 2;
      break;
    case 1:
      if (led > 134) {
        sens = -1;
        delai -= 100;
      }
      else {
        gagnant = 1;
        victoire(p1);
      }
      break;
    case 2:
      ledp2--;
      break;
    case 3:
      appuip2 = 1;
      break;
  }
}
