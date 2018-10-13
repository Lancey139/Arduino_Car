/*
 * VoitureSerialCom.h
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#ifndef SRC_VOITURESERIALCOM_H_
#define SRC_VOITURESERIALCOM_H_

#include "SerialCom.h"
#include "Constantes.h"

class Voiture_SerialCom : public Serial_Com
{
public:

	Voiture_SerialCom();
	virtual ~Voiture_SerialCom();
	void EnvoyerPosition(int pAngleBas, int pAngleHaut, int pIncrement, int pSens, int pTableauDistance[gTailleTableauDistance]);
};

#endif /* SRC_VOITURESERIALCOM_H_ */
