#ifndef FAHREN_H
#define FAHREN_H

extern void OnFwd(byte mot, int v);
extern void OnRev(byte mot, int v);
extern void Off(byte mot);
extern int leseTaster();
extern void Gruen();
extern void neunziglinks(int diff);
extern void neunzigrechts(int diff);

//////////////////////////////////////////
//Variablen
extern int GruenerPunkt;
extern int LoopGreenCounter;

#endif
