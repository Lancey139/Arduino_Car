/*
 * Voiture.cpp
 *
 *  Created on: 30 sept. 2018
 *      Author: Nicolas
 */

#include "Voiture.h"
#include "Constantes.h"

Voiture::Voiture() {
	/*
	* Initialisation des entrées sorties
	*/
	// Ultrason
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
	// Déplacement
	pinMode(in1,OUTPUT);
	pinMode(in2,OUTPUT);
	pinMode(in3,OUTPUT);
	pinMode(in4,OUTPUT);
	pinMode(ENA,OUTPUT);
	pinMode(ENB,OUTPUT);



	//Stop le robot
	Stop();
}

Voiture::~Voiture() {
}

void Voiture::Avancer()
{
	analogWrite(ENA,ABS);
	analogWrite(ENB,ABS);
	digitalWrite(in1,HIGH);
	digitalWrite(in2,LOW);
	digitalWrite(in3,LOW);
	digitalWrite(in4,HIGH);

	if (debug == 1)
		Serial.println("go forward!");
}

void Voiture::Reculer()
{
	analogWrite(ENA,ABS);
	analogWrite(ENB,ABS);
	digitalWrite(in1,LOW);
	digitalWrite(in2,HIGH);
	digitalWrite(in3,HIGH);
	digitalWrite(in4,LOW);
	if (debug == 1)
		Serial.println("go back!");
}

void Voiture::Gauche()
{
	analogWrite(ENA,ABS);
	analogWrite(ENB,ABS);
	digitalWrite(in1,HIGH);
	digitalWrite(in2,LOW);
	digitalWrite(in3,HIGH);
	digitalWrite(in4,LOW);
	if (debug == 1)
		Serial.println("go left!");
}

void Voiture::Droite()
{
	analogWrite(ENA,ABS);
	analogWrite(ENB,ABS);
	digitalWrite(in1,LOW);
	digitalWrite(in2,HIGH);
	digitalWrite(in3,LOW);
	digitalWrite(in4,HIGH);
	if (debug == 1)
		Serial.println("go right!");
}

void Voiture::Stop()
{
	digitalWrite(ENA,LOW);
	digitalWrite(ENB,LOW);
	if (debug == 1)
		Serial.println("Stop!");
}

int Voiture::MesureDistance()
{
	digitalWrite(Trig, LOW);
	delayMicroseconds(2);
	digitalWrite(Trig, HIGH);
	delayMicroseconds(20);
	digitalWrite(Trig, LOW);
	float Fdistance = pulseIn(Echo, HIGH);
	Fdistance= Fdistance/58;
	return (int)Fdistance;
}

void Voiture::OrienterCapteur(int pAngle)
{
	mAngleServo = pAngle;
}
