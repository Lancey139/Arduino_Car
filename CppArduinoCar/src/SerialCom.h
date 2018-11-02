/*
 * SerialCom.h
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#ifndef SRC_SERIALCOM_H_
#define SRC_SERIALCOM_H_

#include "Arduino.h"
#include "Constantes.h"

class Serial_Com {
public:
	Serial_Com();
	virtual ~Serial_Com();
	void Serial_Write(String pMessage);
	void Serial_Read();
	void Read_Message(byte pIncomingByte);
	virtual void ReadMessageFille();
	void begin(int pBaud);

private:
	// Header en cours de lecture
	bool mReadingHeader = false;

	// Taille du message recu
	int mSizeofMessage = 0;

	// Contenu du header
	char mBufferHeader[SIZEOF_MESSAGESIZE];

	//Compteur
	int mCompteur = 0;

	//Compteur Header
	int mCompteurHeader = 0;

protected:
	// Contenu du message
	char* mBufferMessage;
};

#endif /* SRC_SERIALCOM_H_ */
