#include <Arduino.h>
#include <SPI.h>
#include "meinePins.h"
#include "messen.h"
#include "fahren.h"
#include <EEPROM.h>

int crossingU = 0;
int crossingK = 0;
int crossingO = 0;
int GruenerPunkt = 0;
//------------------------------------------------------------------CDP 8.14
int crossingReact(int crossing1, int crossing2, int crossing3) {
  Off(OUT_AB);
  #ifdef DEBUG
  if (crossing1 == 0) {
    Serial.println(" | ");
  }
  else if (crossing1 == 1) {
    Serial.println("x| ");
  }
  else if (crossing1 == 2) {
    Serial.println(" |x");
  }
  else {
    Serial.println("x|x");
  }
  if (crossing2 == 1) {
    Serial.println("-+ ");
  }
  else if (crossing2 == 2) {
    Serial.println(" +-");
  }
  else {
    Serial.println("-+-");
  }
  if (crossing3 == 0) {
    Serial.println(" | ");
  }
  else if (crossing3 == 1) {
    Serial.println("x| ");
  }
  else if (crossing3 == 2) {
    Serial.println(" |x");
  }
  else {
    Serial.println("x|x");
  }
  if (crossing3 == 0) {
    Serial.println("Vorwaerts");
    return 0;
  }
  else if (crossing3 == 1) {
    Serial.println("Links");
    return 1;
  }
  else if (crossing3 == 2) {
    Serial.println("Rechts");
    return 2;
  }
  else if (crossing3 == 3) {
    Serial.println("180 Grad");
    return 3;
  }
  #endif
}
void crossingDetect() {
  int Punkt1 = 0;
  int Punkt2 = 0;
  if(GruenerPunkt > 0){
    Off(OUT_AB);
    Serial.println("Crossing Detected: ");
    Serial.print(GruenerPunkt);
    crossingU = GruenerPunkt;
    OnFwd(OUT_AB,70);
    delay(1000);
    Off(OUT_AB);
    if(WerteA[RECHTS] >= SCHWARZ){
      Punkt1 = 2;
    }
    else{Punkt1 = 0;}
    if(WerteA[LINKS] >= SCHWARZ){
      Punkt2 = 1;
    }
    else{Punkt2 = 0;}
    crossingK = Punkt1 + Punkt2;
    if(crossingK == 0){
      return;
      }
    OnFwd(OUT_AB,70);
    delay(1000);
    Off(OUT_AB);
    if ((WerteG[RECHTS] - WerteR[RECHTS] >= GRUENSCHWELLE )&&( WerteG[RECHTS] < 50)) {
      Punkt1 = 2; 
    }
    else{Punkt1 = 0;}
    if ((WerteG[RECHTS] - WerteR[RECHTS] >= GRUENSCHWELLE )&&( WerteG[RECHTS] < 50)) {
      Punkt2 = 1;
    }
    else{Punkt2 = 0;}
    crossingO = Punkt1 + Punkt2;
    crossingReact(crossingU,crossingK,crossingO);
  }
}
