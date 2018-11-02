/*
 * SerialCom.cpp
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#include "SerialCom.h"


Serial_Com::Serial_Com()
{

}

Serial_Com::~Serial_Com()
{
}

void Serial_Com::begin(int pBaud)
{
	Serial.begin(pBaud);
}


void Serial_Com::Serial_Write(String pMessage)
{
  int l_length = pMessage.length();
  String lStringTaille;
  if(l_length > 100)
  {
	  lStringTaille = String(l_length);
  }
  else if(l_length > 10)
  {
	  lStringTaille = "0";
	  lStringTaille += String(l_length);
  }
  else
  {
	  lStringTaille = "00";
	  lStringTaille += String(l_length);
  }

  // Envoi de l'entete
  Serial.write(Start);
  Serial.write(lStringTaille.charAt(0));
  Serial.write(lStringTaille.charAt(1));
  Serial.write(lStringTaille.charAt(2));
  Serial.write(End);

  // Envoi du message
   Serial.write(pMessage.c_str());

  Serial.flush();
}


void Serial_Com::Serial_Read()
{
  byte lIncomingByte;

  while(Serial.available() > 0)
  {
      // read the incoming byte:
	  lIncomingByte = Serial.read();
      switch (lIncomingByte)
      {
        case Start:
          mReadingHeader = true;
          break;
        case End:
          // Fin de la lecture du header
          mReadingHeader = false;
          //Lecture de la taille du message
          mSizeofMessage = atoi(mBufferHeader);

          // Supression de l'ancien message
          delete mBufferMessage;

          // Création du nouveau buffer
          mBufferMessage = new char[mSizeofMessage + 1];
          mBufferMessage[mSizeofMessage] = '\0';

          // Reinit des compteurs
          mCompteurHeader=0;
          mCompteur=0;
          break;

        default:
         // Si on lit un buffer on l'implémente
         if(mReadingHeader && mCompteurHeader < SIZEOF_MESSAGESIZE)
          {
        	 mBufferHeader[mCompteurHeader] = lIncomingByte;
            ++mCompteur;
          }

          Read_Message(lIncomingByte);
          break;
      }
  }
}


void Serial_Com::Read_Message(byte pIncomingByte)
{
  if( ! mReadingHeader)
  {
		if (mCompteur < mSizeofMessage)
		{
			// read the incoming byte:
			mBufferMessage[mCompteur] = pIncomingByte;
			++mCompteur;
		}

		if (mCompteur == mSizeofMessage)
		{
			// Traitement du message recu dans la classe fille
			ReadMessageFille();
		}
    }
}

void Serial_Com::ReadMessageFille()
{
	// Méthode a surcharger
}




