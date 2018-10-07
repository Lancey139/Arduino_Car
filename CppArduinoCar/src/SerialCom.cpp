/*
 * SerialCom.cpp
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#include "SerialCom.h"
#include "Constantes.h"

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

