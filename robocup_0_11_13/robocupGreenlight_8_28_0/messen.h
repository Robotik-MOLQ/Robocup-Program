#ifndef MESSEN_H
#define MESSEN_H

#define LINKS 0
#define RECHTS 1

//          Variablen
extern int WerteW[ANZ_LS];
extern int WerteA[ANZ_LS];
extern int WerteG[ANZ_LS];
extern int WerteR[ANZ_LS];
extern int WertS;
extern long TimeV;
extern long TimeW;
extern int Richtung;

//          Funktionen von messen.h
extern void zeigeLichtSeriell();
extern void messeLicht();
extern void LEDTest();
extern void kalibrierenJaNein();


//         Andere Funktionen
void kalibrieren();
void zeigeMinMax ();
void LichtUmrechnen ();
extern void KreuzungErkennen();


void SpeichereMinMax();
void LeseMinMax();

void hardwareInit ();

#endif
