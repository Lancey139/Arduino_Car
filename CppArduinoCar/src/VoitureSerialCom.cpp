/*
 * VoitureSerialCom.cpp
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#include "VoitureSerialCom.h"
#include "Arduino.h"


Voiture_SerialCom::Voiture_SerialCom()
{
}

Voiture_SerialCom::~Voiture_SerialCom() {
}

void Voiture_SerialCom::EnvoyerPosition(int pAngleBas, int pAngleHaut, int pIncrement, int pSens, int pTableauDistance[gTailleTableauDistance])
{
	int lTaille = 0;

	String lString_data;
	char* lData;
	lString_data += String(pAngleBas) + ";";
	lString_data += String(pAngleHaut) + ";";
	lString_data += String(pIncrement) + ";";
	lString_data += String(pSens) + ";";
	for(int i = 0 ; i < gTailleTableauDistance; ++i)
	{
		lString_data += String(pTableauDistance[i]);
		lString_data += ";";
		lTaille += 2;
	}

	Serial_Write(lString_data);

}

