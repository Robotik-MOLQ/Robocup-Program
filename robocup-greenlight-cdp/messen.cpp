#include <Arduino.h>
#include "meinePins.h"
#include "messen.h"
#include "fahren.h"
#include <SPI.h>
#include <EEPROM.h>

#define MAX_ADC 1023

long TimeV = 0;
long TimeW = 0;
int Richtung = RECHTS;
byte LEDs[ANZ_LEDs] = {LED_W, LED_G, LED_R, LED_A};
byte LS[ANZ_LS] = {SE_LI, SE_RE, SE_MI};
int WerteW[ANZ_LS];
int WerteG[ANZ_LS];
int WerteR[ANZ_LS];
int WerteA[ANZ_LS];
int MinW[ANZ_LS];
int MinG[ANZ_LS];
int MinR[ANZ_LS];
int MinA[ANZ_LS];
int MaxW[ANZ_LS];
int MaxG[ANZ_LS];
int MaxR[ANZ_LS];
int MaxA[ANZ_LS];

void LEDTest() {
  Serial.println("LED Test");
  setLED(LED_W);
  delay(4000);
  setLED(LED_A);
  Serial.println("Weiß");
  delay(4000);
  setLED(LED_G);
  Serial.println("Grün");
  delay(4000);
  setLED(LED_R);
  Serial.println("Rot");
  delay(4000);
  setLED(0);
  Serial.println("100% Completed");
}

void messeRawLicht() {
  byte pause = 2;
  setLED (LED_W);
  delay(pause);
  for (int i = 0; i < ANZ_LS; i++) {
    WerteW[i] = analogRead(LS[i]);
  }
  setLED (LED_G);
  delay(pause);
  for (int i = 0; i < ANZ_LS; i++) {
    WerteG[i] = analogRead(LS[i]);
  }
  setLED (LED_R);
  delay(pause);
  for (int i = 0; i < ANZ_LS; i++) {
    WerteR[i] = analogRead(LS[i]);
  }
  setLED (LED_A);
  delay(pause);
  for (int i = 0; i < ANZ_LS; i++) {
    WerteA[i] = analogRead(LS[i]);
  }
  setLED(0);
}

void zeigeLichtSeriell() {
  Serial.print ("W_li: ");
  Serial.print(WerteW[0]);
  Serial.print ("A_li: ");
  Serial.print(WerteA[0]);
  /* Serial.print(" ");
    Serial.print(WerteG[0]);
    Serial.print(" ");
    Serial.print(WerteR[0]);*/
  Serial.print(" \t W_re: ");
  Serial.print(WerteW[1]);
  Serial.print(" \t A_re: ");
  Serial.print(WerteA[1]);
  /*Serial.print(" ");
    Serial.print(WerteG[1]);
    Serial.print(" ");
    Serial.print(WerteR[1]);*/
  Serial.println();

}


void kalibrieren() {
  for (int j = 0; j < ANZ_LS; j++) {
    MinW[j] = MAX_ADC;
    MinG[j] = MAX_ADC;
    MinR[j] = MAX_ADC;
    MinA[j] = MAX_ADC;
    MaxW[j] = 0;
    MaxG[j] = 0;
    MaxR[j] = 0;
    MaxA[j] = 0;
  }
  for (int i = 0; i < 500; i++) {
    messeRawLicht();
    delay(10);
    for (int j = 0; j < ANZ_LS; j++) {


      if (WerteW[j] > MaxW[j])
        MaxW[j] = WerteW[j];
      if (WerteW[j] < MinW[j])
        MinW[j] = WerteW[j];

      if (WerteG[j] > MaxG[j])
        MaxG[j] = WerteG[j];
      if (WerteG[j] < MinG[j])
        MinG[j] = WerteG[j];

      if (WerteR[j] > MaxR[j])
        MaxR[j] = WerteR[j];
      if (WerteR[j] < MinR[j])
        MinR[j] = WerteR[j];

      if (WerteA[j] > MaxA[j])
        MaxA[j] = WerteA[j];
      if (WerteA[j] < MinA[j])
        MinA[j] = WerteA[j];

    }
  }
}
void messeLicht() {
  messeRawLicht();
  LichtUmrechnen();
#ifdef DEBUG
  zeigeLichtSeriell();
#endif
}
void zeigeMinMax () {
  Serial.print ("Min_li: ");
  Serial.print(MinW[0]);
  Serial.print(" ");
  Serial.print(MinG[0]);
  Serial.print(" ");
  Serial.print(MinR[0]);
  Serial.print(" \t Min_re: ");
  Serial.print(MinW[1]);
  Serial.print(" ");
  Serial.print(MinG[1]);
  Serial.print(" ");
  Serial.print(MinR[1]);
  Serial.println();

  Serial.print ("Max_li: ");
  Serial.print(MaxW[0]);
  Serial.print(" ");
  Serial.print(MaxG[0]);
  Serial.print(" ");
  Serial.print(MaxR[0]);
  Serial.print(" \t Max_re: ");
  Serial.print(MaxW[1]);
  Serial.print(" ");
  Serial.print(MaxG[1]);
  Serial.print(" ");
  Serial.print(MaxR[1]);
  Serial.println();
}
void LichtUmrechnen () {
  for (int j = 0; j < ANZ_LS; j++) {
    WerteW[j] =   map (WerteW[j], MinW[j], MaxW[j], 0, 100);
    WerteG[j] =   map (WerteG[j], MinG[j], MaxG[j], 0, 100);
    WerteR[j] =   map (WerteR[j], MinR[j], MaxR[j], 0, 100);
    WerteA[j] =   map (WerteA[j], MinA[j], MaxA[j], 0, 100);
  }

}

void SpeichereMinMax() {
  EEPROM.put( 0, MinW[0]);
  EEPROM.put( 2, MinG[0]);
  EEPROM.put( 4, MinR[0]);
  EEPROM.put( 6, MaxW[0]);
  EEPROM.put( 8, MaxG[0]);
  EEPROM.put(10, MaxR[0]);
  EEPROM.put(12, MinW[1]);
  EEPROM.put(14, MinG[1]);
  EEPROM.put(16, MinR[1]);
  EEPROM.put(18, MaxW[1]);
  EEPROM.put(20, MaxG[1]);
  EEPROM.put(22, MaxR[1]);
  EEPROM.put(24, MinA[0]);
  EEPROM.put(26, MaxA[0]);
  EEPROM.put(28, MinA[1]);
  EEPROM.put(30, MaxA[1]);
}


void LeseMinMax() {
  Serial.println("leseMinMax");
  EEPROM.get( 0, MinW[0]);
  Serial.print("/");
  EEPROM.get( 2, MinG[0]);
  Serial.print("/");
  EEPROM.get( 4, MinR[0]);
  Serial.print("/");
  EEPROM.get( 6, MaxW[0]);
  Serial.print("/");
  EEPROM.get( 8, MaxG[0]);
  Serial.print("/");
  EEPROM.get(10, MaxR[0]);
  Serial.print("/");
  EEPROM.get(12, MinW[1]);
  Serial.print("/");
  EEPROM.get(14, MinG[1]);
  Serial.print("/");
  EEPROM.get(16, MinR[1]);
  Serial.print("/");
  EEPROM.get(18, MaxW[1]);
  Serial.print("/");
  EEPROM.get(20, MaxG[1]);
  Serial.print("/");
  EEPROM.get(22, MaxR[1]);
  Serial.print("/");
  EEPROM.get(24, MinA[0]);
  Serial.print("/");
  EEPROM.get(26, MaxA[0]);
  Serial.print("/");
  EEPROM.get(28, MinA[1]);
  Serial.print("/");
  EEPROM.get(30, MaxA[1]);
  Serial.print("/");
  Serial.println("----------------");
}


void hardwareInit () {
  pinMode(LICHT_CS, OUTPUT);
  digitalWrite(LICHT_CS, HIGH);
  SPI.begin();
  Serial.begin(115200);
  Serial.println("Hallo MOLQ");
  Serial.println(" Hardware Init");
}

void kalibrierenJaNein(){
  Serial.println("Kal? => T");
  TimeV = millis() + 3000;
  while(TimeV > millis()){
    if (leseTaster() > 0){
      Serial.println("Gedrueckt...");
      kalibrieren();
      SpeichereMinMax();
      break;
    }
  }
  LeseMinMax();
}
