#include <SPI.h>
#include "meinePins.h"
#include "messen.h"
#include "fahren.h"
#include <EEPROM.h>
#define V 70
/////////////////////////////////////////////////////////////////////////////
//Variablen
boolean Schwarz = 0;
long Loop = 0;
//-------------------------------------------MOLQ - Linienfolger 2020 Greenlight (8/28/0)--------------------------------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////
//Loop
void setup() {
  hardwareInit();
  //LEDTest();
  Serial.println("Init ok");
  kalibrierenJaNein();
  delay(1000);
  Serial.println("Start?");
  
  
  while (leseTaster() == 0) {
    messeLicht();
    zeigeLichtSeriell();
    delay(100);
  }
  delay(2000);
  Serial.println("Linie");

}

void loop() {
//  fahreZeitBisSchwarz(2000,70);
//  delay(1000);
  messeLicht();
  LinieFolgen();
    if (leseTaster() > 0) {
      DoseUmfahren(V,RECHTS);
    }
  Loop++;
  #ifdef DEBUG
    Serial.println("Loop: ");
    Serial.print(Loop);
  #endif
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dose umfahren unterbefehl

void Drehe(long Zeit, int ges, int Richtung){
  long Start = millis();
  if(Richtung == 0){
    OnFwd(OUT_B,ges);
    OnRev(OUT_A,ges);
  }
  else{
    OnFwd(OUT_A,ges);
    OnRev(OUT_B,ges);
  }
  while(Start + Zeit > millis()){

  }
  Off(OUT_AB);
}
bool DreheZeitBisSchwarz(long Zeit, int ges, int Richtung) {
  long Start = millis();
  boolean SchwarzGesehen = false;
  messeLicht();
  if(Richtung == 0){
    OnFwd(OUT_B,ges);
    OnRev(OUT_A,ges);
  }
  else{
    OnFwd(OUT_A,ges);
    OnRev(OUT_B,ges);
  }
  while ((Start + Zeit > millis()) && ( not SchwarzGesehen)) {
    delayMicroseconds(10);
    messeLicht();
    if((WerteW[0] < SCHWARZ) ||(WerteW[1] < SCHWARZ) ){
      SchwarzGesehen = true;
    }
  }
  Off(OUT_AB);
  return SchwarzGesehen;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lückenerkennung
bool fahreZeitBisSchwarz(long Zeit, int ges) {
  long Start = millis();
  boolean SchwarzGesehen = false;
  messeLicht();
  OnFwd(OUT_AB, ges);
  while ((Start + Zeit > millis()) && ( not SchwarzGesehen)) {
    delayMicroseconds(10);
    messeLicht();
    if((WerteW[0] < SCHWARZ) ||(WerteW[1] < SCHWARZ) ){
      SchwarzGesehen = true;
    }
  }
  Off(OUT_AB);
  return SchwarzGesehen;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dose umfahren
void DoseUmfahren(int ges,int Richtung) {
  Serial.print("Dose");
  OnRev(OUT_AB, ges);
  delay(600);
  Drehe(1900,ges,Richtung);
  #ifdef DEBUG
    delay(2000);
  #endif
  delay(2000);
  boolean schwarzGesehen = false;
  int i = 0;
  while(schwarzGesehen == false){
    if(i%2 == 0){
      schwarzGesehen = fahreZeitBisSchwarz(1900,ges);
    }
    else{
      schwarzGesehen = DreheZeitBisSchwarz(1300,ges,1 - Richtung);
    }
    i++;
  }
  Serial.println("Linie");
}

#define ABBIEGE_DELAY 80

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Linienfolger und Greenlight Verbesserung
void LinieFolgen() {
  int diff = (5 * (WerteW[RECHTS] - WerteW[LINKS])) / 2;
  Gruen();
  neunzig();


  else if (WerteA[LINKS] <= SCHWARZ ){
    
  }
  else {
    LoopGreenCounter = 0;
    OnFwd(OUT_A, V - diff);
    OnFwd(OUT_B, V + diff);
  }
}
