/*
 * Constantes du projet
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include <Arduino.h>

// Variables pour la communication
#define Start 'S'
#define End 'E'
#define SIZEOF_MESSAGESIZE 3

// Battement du moteur
const int gAngleBas = 30;
const int gAngleHaut = 170;
const int gIncrement = 5;
const int gTailleTableauDistance = (gAngleHaut - gAngleBas) / gIncrement;

//Assination des pins
const int Echo = A4;
const int Trig = A5;
const int in1 = 6;
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;
const int ENA = 5;
const int ENB = 11;
const int ABS = 150;
const int pinServoMoteur = 3;

// Mode debug
const int debug = 0;

#endif /* CONSTANTES_H_ */
