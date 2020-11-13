#ifndef FAHREN_H
#define FAHREN_H

extern void OnFwd(byte mot, int v);
extern void OnRev(byte mot, int v);
extern void Off(byte mot);
extern int leseTaster();
extern void Gruen();

//////////////////////////////////////////
//Variablen
extern int GruenerPunkt;
extern int LoopGreenCounter;

#endif
