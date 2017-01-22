#include <Adafruit_NeoPixel.h>
#include <SparkFunDS1307RTC.h>
#include <stdlib.h>

#define PIN      6
#define N_LEDS 89 // will be 86
#define LEN(x) sizeof(x) / sizeof(x[0])
#define COLOR Wheel(COUNTER)

// Mapping of words to which pixels in the strip they are
int IT[] = {0};
int IS[] = {1};
int TEN[] = {2, 3};
int HALF[] = {4, 5, 6};
int TWENTY[] = {7, 8, 9, 10, 11}; 
int QUARTER[] = {12, 13, 14, 15, 16, 17}; 
int FIVE[] = {18, 19, 20}; 
int MINUTES[] = {21, 22, 23, 24, 25, 26}; 
int TO[] = {27}; 
int SHIFT[] = {28, 29, 30, 31};
int PAST[] = {32, 33, 34}; 
int NUM1[] = {35, 36}; 
int NUM2[] = {37, 38}; 
int NUM11[] = {39, 40, 41, 42, 43}; 
int NUM5[] = {44, 45, 46}; 
int NUM4[] = {47, 48, 49}; 
int NUM3[] = {50, 51, 52, 53}; 
int NUM6[] = {54, 55}; 
int NUM7[] = {56, 57, 58, 59}; 
int NUM8[] = {60, 61, 62, 63}; 
int NUM12[] = {64, 65, 66, 67}; 
int NUM10[] = {68, 69}; 
int NUM9[] = {70, 71}; 
int OUT[] = {72, 73}; 
int LOVE[] = {74, 75, 76}; 
int OCLOCK[] = {77, 78, 79, 80}; 
int HARAMBE[] = {81, 82, 83, 84, 85, 86};
int FOR[] = {87, 88};

bool LEDS_ON[N_LEDS];
byte COUNTER = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void turnOn(int section[], int len) {
  for (int i=0; i < len; i++) {
    LEDS_ON[section[i]] = true;
  }
}

void turnOff(int section[], int len) {
  for (int i=0; i < len; i++) {
    LEDS_ON[section[i]] = false;
  }
}

void turnOffAll() {
  for (int i=0; i < N_LEDS; i++) {
    LEDS_ON[i] = false;
  } 
}

void turnOnAll() {
  for (int i=0; i < N_LEDS; i++) {
    LEDS_ON[i] = true;
  } 
}

void updateLEDS() {
  byte offset = 0;
  for (int i = 0; i < N_LEDS; i++) {
    if (LEDS_ON[i]) {
      strip.setPixelColor(i, Wheel((COUNTER + 5*offset) % 256));
      //strip.setPixelColor(i, strip.Color(255,255,255));
      offset ++;
    }
    else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();
}

void setup() {
  turnOffAll();

  Serial.begin(9600);
  rtc.begin();
  strip.begin();
  turnOffAll();
  updateLEDS();
  //delay(5000);
}

void loop() {
  //test();
  //return;
  // Initialize everything
  Serial.println("Updating rtc...");
  rtc.update();
  Serial.print("Updated! Time is "); Serial.print(rtc.hour()); Serial.print(":"); Serial.print(rtc.minute()); Serial.print(":"); Serial.println(rtc.second());
  int mts = rtc.minute() + (rtc.second() / 60.0);

  //COUNTER = (COUNTER + 1)%256;
  uint32_t c = Wheel(COUNTER);

  // Reset all LEDs
  turnOffAll();

  // IT IS
  turnOn(IT, LEN(IT));
  turnOn(IS, LEN(IS));

  // OCLOCK
  if (mts >= 57.5 || mts < 2.5) {
    turnOn(OCLOCK, LEN(OCLOCK));
  }

  // FIVE
  if ((2.5 <= mts && mts < 7.5) 
  || (22.5 <= mts && mts < 27.5) 
  || (32.5 <= mts && mts < 37.5) 
  || (52.5 <= mts && mts < 57.5)) {
    turnOn(FIVE, LEN(FIVE));
    turnOn(MINUTES, LEN(MINUTES)); 
  }

  // TEN
  if ((7.5 <= mts && mts < 12.5) 
  || (47.5 <= mts && mts < 52.5)) {
    turnOn(TEN, LEN(TEN));
    turnOn(MINUTES, LEN(MINUTES));
  }

  // QUARTER
  if ((12.5 <= mts && mts < 17.5)
  || (42.5 <= mts && mts < 47.5)) {
    turnOn(QUARTER, LEN(QUARTER)); 
  }

  // TWENTY
  if ((17.5 <= mts && mts < 27.5) 
  || (32.5 <= mts && mts < 42.5)) {
    turnOn(TWENTY, LEN(TWENTY));
    turnOn(MINUTES, LEN(MINUTES));
  }

  // HALF
  if (27.5 <= mts && mts < 32.5) {
    turnOn(HALF, LEN(HALF));
  }

  // PAST
  if (2.5 <= mts && mts < 32.5) {
    turnOn(PAST, LEN(PAST));
  }

  // TO
  if (32.5 <= mts && mts < 57.5) {
    turnOn(TO, LEN(TO));
  }

  int hr = rtc.hour();
  if (hr < 5) {hr += 24;}
  int number = (hr - 5) % 12;
  if (32.5 <= mts) {
    number += 1; 
  }

  Serial.print(number); Serial.print(":"); Serial.println(mts);

  switch(number) {
    case 1:
      turnOn(NUM1, LEN(NUM1));
      break;
    case 2: 
      turnOn(NUM2, LEN(NUM2));
      break;
    case 3: 
      turnOn(NUM3, LEN(NUM3));
      break;
    case 4: 
      turnOn(NUM4, LEN(NUM4));
      break;
    case 5: 
      turnOn(NUM5, LEN(NUM5));
      break;
    case 6: 
      turnOn(NUM6, LEN(NUM6));
      break;
    case 7: 
      turnOn(NUM7, LEN(NUM7));
      break;
    case 8: 
      turnOn(NUM8, LEN(NUM8));
      break;
    case 9: 
      turnOn(NUM9, LEN(NUM9));
      break;
    case 10: 
      turnOn(NUM10, LEN(NUM10));
      break;
    case 11: 
      turnOn(NUM11, LEN(NUM11));
      break;
    default:
      turnOn(NUM12, LEN(NUM12));
      break;
  }
  
  turnOn(HARAMBE, LEN(HARAMBE));
  updateLEDS();
  COUNTER = (COUNTER + 2) % 256;
  delay(50);
}

void test() {
  turnOffAll();
  turnOn(IT, LEN(IT));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(IS, LEN(IS));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(TEN, LEN(TEN));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(HALF, LEN(HALF));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(TWENTY, LEN(TWENTY));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(QUARTER, LEN(QUARTER));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(FIVE, LEN(FIVE));
  updateLEDS();
  delay(500);
  turnOffAll();


  turnOn(MINUTES, LEN(MINUTES));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(TO, LEN(TO));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(SHIFT, LEN(SHIFT));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(PAST, LEN(PAST));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM1, LEN(NUM1));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM2, LEN(NUM2));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM11, LEN(NUM11));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM5, LEN(NUM5));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM4, LEN(NUM4));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM3, LEN(NUM3));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM6, LEN(NUM6));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM7, LEN(NUM7));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM8, LEN(NUM8));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM12, LEN(NUM12));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM10, LEN(NUM10));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(NUM9, LEN(NUM9));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(OUT, LEN(OUT));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(LOVE, LEN(LOVE));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(OCLOCK, LEN(OCLOCK));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(HARAMBE, LEN(HARAMBE));
  updateLEDS();
  delay(500);
  turnOffAll();

  turnOn(FOR, LEN(FOR));
  updateLEDS();
  delay(500);
  turnOffAll();
}
