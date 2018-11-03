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

void Voiture_SerialCom::EnvoyerPosition(int pTableauAngle[gTailleTableauDistance], int pTableauDistance[gTailleTableauDistance])
{
	int lTaille = 0;

	String lString_data;
	char* lData;
	lString_data += String(gTailleTableauDistance) + ";";
	for(int i = 0 ; i < gTailleTableauDistance; ++i)
	{
		lString_data += String(pTableauAngle[i]);
		lString_data += ";";
		lTaille += 2;
	}
	for(int i = 0 ; i < gTailleTableauDistance; ++i)
	{
		lString_data += String(pTableauDistance[i]);
		lString_data += ";";
		lTaille += 2;
	}

	Serial_Write(lString_data);
}

void Voiture_SerialCom::ReadMessageFille()
{
	// Analyse du message recu
	Serial.println(mBufferMessage);
	switch(mBufferMessage[0])
	{
	case 'Z':
		mVoiture->SetToutDroit(1);
		break;
	case 'Q':
		mVoiture->SetLeft(1);
		break;
	case 'D':
		mVoiture->SetRight(1);
		break;
	case 'W':
		mVoiture->SetToutDroit(0);
		break;
	case 'A':
		mVoiture->SetModeAutomatique(true);
		break;
	case 'M':
		mVoiture->SetModeAutomatique(false);
		break;
	case 'V':
		mVoiture->SetModeSecurite(true);
		break;
	case 'B':
		mVoiture->SetModeSecurite(false);
		break;
	case 'F':
		mVoiture->SetRotation(true);
		break;
	case 'G':
		mVoiture->SetRotation(false);
		break;

	}
}

