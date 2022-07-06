#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

int getSign(int pin);


#define PIN A0
#define NUMPIXELS 540
#define DESCENDING true
#define LENGTH(X) sizeof(X)/sizeof(X[0])

int sign_buttonpin[8] = {7, 6, 5, 4, 3, 2, 1, 0};
int max_led_sign[8] = {72, 72, 71, 72, 69, 72, 72, 72};
boolean party_mode = false;
boolean is_first_cycle = true;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  for(uint16_t i = 0; i < LENGTH(sign_buttonpin); i++){
    pinMode(sign_buttonpin[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  Serial.println("Starting Programm");
  pixels.begin();
}

void loop() {
  if(is_first_cycle){
    is_first_cycle = false;
    if(digitalRead(sign_buttonpin[7]) == LOW) {
      party_mode = true; // if button is high on boot
    }
  }
  if(party_mode){
    for(uint16_t i=0; i < 10; i=i+1){
      pixels.rainbow(random(65534));
      pixels.show();
      delay(500);
      pixels.clear();
      pixels.show();
      delay(200);
    }
  } else {
    int button_pin_state[LENGTH(sign_buttonpin)];
    for(uint16_t i = 0; i < LENGTH(sign_buttonpin); i++){
      button_pin_state[i] = 255 * digitalRead(sign_buttonpin[i]);
    }

    for(uint16_t i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color( button_pin_state[getSign(i)] , (255 - button_pin_state[getSign(i)] ), 0));
    }

    pixels.show();
    delay(10);
  }
}

int getSign(int led){
  int lednummax = 0;
  if(DESCENDING){
    for(uint16_t i=LENGTH(max_led_sign)-1; i >= 0 ; i = i-1){
      lednummax = lednummax + max_led_sign[i];
      if(led < lednummax){
        return i;
      }
    }
  } else{
    for(uint16_t i=0; i < LENGTH(max_led_sign) ; i=i+1){
      lednummax = lednummax + max_led_sign[i];
      if(led < lednummax){
        return i;
      }
    }
  }
  return -1;
}