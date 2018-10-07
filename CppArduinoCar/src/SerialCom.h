/*
 * SerialCom.h
 *
 *  Created on: 7 oct. 2018
 *      Author: Nicolas
 */

#ifndef SRC_SERIALCOM_H_
#define SRC_SERIALCOM_H_

#include "Arduino.h"

class Serial_Com {
public:
	Serial_Com();
	virtual ~Serial_Com();
	void Serial_Write(String pMessage);
	void begin(int pBaud);
};

#endif /* SRC_SERIALCOM_H_ */
