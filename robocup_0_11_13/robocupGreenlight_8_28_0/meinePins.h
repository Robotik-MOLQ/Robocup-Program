#ifndef MEINEPINS_H
#define MEINEPINS_H
//#define DEBUG         // Debug-Features: Lichtwertaugabe; Radiusausgabe; Loopausgabe;

               // Abbiegerichtung an Kreuzungen
#define LINKS 0  
#define RECHTS 1


// Chip select für den 74HC595
#define LICHT_CS A0
#define SE_LI A7
#define SE_MI A6 
#define SE_RE A2
#define SE_SI A6
 
#define LED_R     2   //P2
#define LED_G     4   //P3
#define LED_W     1   //P1
#define LED_A     8   //P4
#define LED_SI    2
#define ANZ_LEDs  4
#define ANZ_LS    3

//Taster



//Motoren
#define OUT_A  1
#define OUT_B  2
#define OUT_AB 3
#define PWMA 3     // Motor links
#define PWMB 5     // Motor rechts

extern void setLED(int led);

// Universelle Variablen

#define V 70
#define ABBIEGE_DELAY 80 //80 standard
#define SCHWARZ  10
#define GRUENSCHWELLE  15
#define SILBER  50

#endif
