/*
 * Voiture.h
 *
 *  Created on: 30 sept. 2018
 *      Author: Nicolas
 */

#ifndef VOITURE_H_
#define VOITURE_H_

#include <Servo.h>
#include "Constantes.h"

class Voiture {
public:
	Voiture();
	virtual ~Voiture();
	void Avancer();
	void Reculer();
	void Gauche();
	void Droite();
	void Stop();
	int MesureDistance();
	void OrienterCapteur(int pAngle);

	// Getter et Setter
	int GetPositionCapteur() { return mPositionCapteur; };
	void SetPositionCapteur(int pValue) { mPositionCapteur = pValue; };
	int GetObstacle() { return mObstacle; };
	int GetAngleServo() { return mAngleServo; };
	int GetSensRotation() { return mSensRotation; };
	void SetSensRotation(int pValue) { mSensRotation = pValue; };
	int GetLeft() { return mLeft; };
	void SetLeft(int pValue) { mLeft = pValue; };
	int GetRight() { return mRight; };
	void SetRight(int pValue) { mRight = pValue; };
	int GetTempLeft() { return mTempoLeft; };
	void SetTempLeft(int pValue) { mTempoLeft = pValue; };
	int GetTempRight() { return mTempoDroite; };
	void SetTempRight(int pValue) { mTempoDroite = pValue; };
	int GetDelai() { return mDelay_ms; };

private:
	int mPositionCapteur = 90;
	// Distance en cm de détection d'un obstacle
	int mObstacle = 40;

	// Angle du servo moteur
	int mAngleServo = 90;
	int mSensRotation = 0;

	// Variable de déplacement
	int mLeft = 0;
	int mRight = 0;
	int mTempoLeft = 0;
	int mTempoDroite = 0;

	// Gestion du temps
	int mDelay_ms = gDelayAsservissement;

};

#endif /* VOITURE_H_ */
