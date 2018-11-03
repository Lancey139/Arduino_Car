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
#include "Voiture.h"

class Voiture_SerialCom : public Serial_Com
{
public:

	Voiture_SerialCom();
	virtual ~Voiture_SerialCom();
	void EnvoyerPosition(int pTableauAngle[gTailleTableauDistance], int pTableauDistance[gTailleTableauDistance]);
	void ReadMessageFille();
	void SetVoiture(Voiture* pVoiture){mVoiture = pVoiture;};

private:
	Voiture* mVoiture;
};

#endif /* SRC_VOITURESERIALCOM_H_ */
