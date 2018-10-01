#include <Arduino.h>
#include "Voiture.h"
#include "Constantes.h"

Voiture gVoiture;
int gAngleServo = 90;
Servo gServo;
void setup()
{
	Serial.begin(9600);
	gVoiture = Voiture();

	// ServoMoteur surlequel repose le capteur Ultrason
	gServo.attach(pinServoMoteur);
	gServo.write(90);
}

void loop() {
	// Mise a jour de la position du servomoteur
	gVoiture.OrienterCapteur(gAngleServo);
	gServo.write(gAngleServo);

	// Mesure sur le capteur Ultrason
	int lDistance = gVoiture.MesureDistance();

	if (debug == 1)
	{
	  Serial.print("lDistance=");
	  Serial.print(lDistance);
	  Serial.print(" Angle mot = ");
	  Serial.println(gAngleServo);
	}

	// Déplacement du Servomoteur pour préparer la nouvelle mesure
	// Balayage de l'angle 30 a 170
	if (gVoiture.GetSensRotation() == 0)
	{
		gAngleServo+= gVoiture.GetIncrement();
		if (gAngleServo >= 170)
		{
			gVoiture.SetSensRotation(1);
		}
	}
	else
	{
		gAngleServo-=gVoiture.GetIncrement();
		if (gAngleServo <= 30)
		{
			gVoiture.SetSensRotation(0);
		}
	}

	// Détection d'un obstacle en fonction du seuil défini
	if(lDistance < gVoiture.GetObstacle() && gVoiture.GetRight() == 0 && gVoiture.GetLeft() == 0)
	{
		// Si le capteur était positionné entre 30 et 90
		// -> Déplacement à gauche
		if(gAngleServo < 90)
		{
			gVoiture.SetLeft(1);
			gVoiture.SetRight(0);
			gVoiture.SetTempLeft(0);
			gVoiture.SetTempRight(0);
		}
		else if (gAngleServo > 90)
		{
		// Si le capteur était positionné entre 90 et 170
		// -> Déplacement à gauche
			gVoiture.SetLeft(0);
			gVoiture.SetRight(1);
			gVoiture.SetTempLeft(0);
			gVoiture.SetTempRight(0);
		}

	}

	// Ordre donné aux roues
	if(gVoiture.GetRight() == 1)
		gVoiture.Droite();
	else if( gVoiture.GetLeft() == 1)
	   	gVoiture.Gauche();
	else
	  gVoiture.Avancer();

	// Mise a jour des ordres
	gVoiture.SetTempLeft(gVoiture.GetTempLeft() + 1);
	gVoiture.SetTempRight(gVoiture.GetTempRight() + 1);

	// On effectue les ordres pendant X ms
	if (gVoiture.GetTempLeft() > 20)
		gVoiture.SetLeft(0);
	if (gVoiture.GetTempRight() > 20)
		gVoiture.SetRight(0);

	// Delai de delay_ms ms entre 2 mesures
	delay(gVoiture.GetDelai());

}
