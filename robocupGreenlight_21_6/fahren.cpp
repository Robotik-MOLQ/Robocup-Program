#include <Arduino.h>
#include "fahren.h"
#include "meinePins.h"
#include <SPI.h>
byte PEData;

void schreibePEData(byte data) {
  digitalWrite(LICHT_CS, LOW);
  SPI.transfer(data);
  digitalWrite(LICHT_CS, HIGH);
}

byte Taster=0;
int leseTaster() {
  digitalWrite(LICHT_CS, LOW);
  delayMicroseconds(10);
  digitalWrite(LICHT_CS, HIGH);
  delayMicroseconds(10);
  Taster = SPI.transfer(0);
  return Taster;
}


void setLED(int led) {
  PEData &= 0xF0;
  PEData |= (led & 0x0F);
  schreibePEData(PEData);
}



void OnFwd(byte mot, int v)
{
  // prüfe auf erlaubten Wertebereich

  if (v < -255)
    v = -255;
  else if (v > 255)
    v = 255;
  byte richtung = 0;
  if (v >= 0) { // vorwärts fahren
    if (mot & OUT_A) {
      analogWrite(PWMA, v);
      PEData = PEData & ~32;
      PEData = PEData | 16;
      schreibePEData(PEData);
    }
    if (mot & OUT_B) {
      analogWrite(PWMB,  v);
      PEData = PEData & ~128;
      PEData = PEData | 64;
      schreibePEData(PEData);
    }
  }
  else {
    v = -v;
    if (mot & OUT_A) {
      analogWrite(PWMA, v);
      PEData = PEData | 32;
      PEData = PEData & ~16;
      schreibePEData(PEData);
    }
    if (mot & OUT_B) {
      analogWrite(PWMB, v);
      PEData = PEData | 128;
      PEData = PEData & ~64;
      schreibePEData(PEData);
    }
  }

}

void OnRev(byte mot, int v) {
  OnFwd(mot, -v);
}

void Off(byte mot) {
  byte richtung = 0;
  if (mot & OUT_A) {
    analogWrite(PWMA, 0);
    PEData = PEData & ~48;
    schreibePEData(PEData);
  }
  if (mot & OUT_B) {
    analogWrite(PWMB, 0);
    PEData = PEData & ~192;
    schreibePEData(PEData);
  }
}
