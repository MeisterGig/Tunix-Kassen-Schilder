#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN        6
#define NUMPIXELS 16
#define PIXELS_PER_SIGN 71

int sign_buttonpin[8] = {9, 3, 2, 4, 3, 2, 7, 8};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  for(int i = 0; i < sizeof(sign_buttonpin); i++){
    pinMode(sign_buttonpin[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  Serial.println("Starting Programm");
  pixels.begin();
}

void loop() {
  int button_pin_state[sizeof(sign_buttonpin)];
  for(int i = 0; i < sizeof(sign_buttonpin); i++){
    button_pin_state[i] = 255 * digitalRead(sign_buttonpin[i]);
  }

  for(int i=0; i<NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color( button_pin_state[i/PIXELS_PER_SIGN] , (255 - button_pin_state[i/PIXELS_PER_SIGN] ), 0));
    pixels.show();
  }
  delay(10);
}  // put your setup code here, to run once: