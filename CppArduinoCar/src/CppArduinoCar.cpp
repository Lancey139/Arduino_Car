#include <Arduino.h>
#include "Voiture.h"
#include "Constantes.h"
#include "VoitureSerialCom.h"

Voiture gVoiture;
int gAnglePrecedent = 0;
int gAngleServo = gAngleBas;
Servo gServo;
Voiture_SerialCom gVoitureCom;

int gTableauDistance[gTailleTableauDistance];
int gTableauAngle[gTailleTableauDistance];
int gCompteurElement = 0;

void setup()
{
	gVoiture = Voiture();
	gVoitureCom.begin(9600);
	// ServoMoteur surlequel repose le capteur Ultrason
	gServo.attach(pinServoMoteur);
	gServo.write(gAngleBas);
}

void loop() {
	// Mise a jour de la position du servomoteur
	gVoiture.OrienterCapteur(gAngleServo);
	gServo.write(gAngleServo);

	// Mesure sur le capteur Ultrason
	int lDuree = millis() ;
	int lDistance = gVoiture.MesureDistance();
	lDuree = millis() - lDuree;

	// Remplissage du tableua distance
	if(gCompteurElement <gTailleTableauDistance && gCompteurElement >= 0)
	{
		if (lDistance == gAcquisitionFausse)
		{
			gTableauDistance[gCompteurElement] = 100;
		}
		else
		{
			gTableauDistance[gCompteurElement] = lDistance;
		}
		gTableauAngle[gCompteurElement] = gAnglePrecedent;
	}

	if (debug == 1)
	{
	  Serial.print("lDistance=");
	  Serial.print(lDistance);
	  Serial.print(" Angle mot = ");
	  Serial.println(gAnglePrecedent);
	}

	// D�placement du Servomoteur pour pr�parer la nouvelle mesure
	// Balayage de l'angle gAngleBas a gAngleHaut
	if (gVoiture.GetSensRotation() == 0)
	{
		if (gAngleServo > gAngleHaut - gIncrement)
		{
			gVoiture.SetSensRotation(1);
			gVoitureCom.EnvoyerPosition(gTableauAngle , gTableauDistance);

			gAnglePrecedent = gAngleServo;
			gAngleServo-= gIncrement;
			gCompteurElement--;
		}
		else
		{
			gAnglePrecedent = gAngleServo;
			gAngleServo+= gIncrement;
			gCompteurElement++;
		}
	}
	else
	{
		if (gAngleServo < gAngleBas + gIncrement)
		{
			gVoiture.SetSensRotation(0);
			gVoitureCom.EnvoyerPosition(gTableauAngle , gTableauDistance);

			gAnglePrecedent = gAngleServo;
			gAngleServo+= gIncrement;
			gCompteurElement++;
		}
		else
		{
			gAnglePrecedent = gAngleServo;
			gAngleServo-= gIncrement;
			gCompteurElement--;
		}
	}

	// D�tection d'un obstacle en fonction du seuil d�fini
	if(lDistance < gVoiture.GetObstacle() && gVoiture.GetRight() == 0 && gVoiture.GetLeft() == 0)
	{
		// Si le capteur �tait positionn� entre 30 et 90
		// -> D�placement � gauche
		if(gAngleServo < 90)
		{
			gVoiture.SetLeft(1);
			gVoiture.SetRight(0);
			gVoiture.SetTempLeft(0);
			gVoiture.SetTempRight(0);
		}
		else if (gAngleServo > 90)
		{
		// Si le capteur �tait positionn� entre 90 et 170
		// -> D�placement � gauche
			gVoiture.SetLeft(0);
			gVoiture.SetRight(1);
			gVoiture.SetTempLeft(0);
			gVoiture.SetTempRight(0);
		}

	}

	// Ordre donn� aux roues
	if(gVoiture.GetRight() == 1)
	{
		gVoiture.Droite();
		gVoiture.SetTempRight(gVoiture.GetTempRight() + 1);
	}
	else if( gVoiture.GetLeft() == 1)
	{
		gVoiture.SetTempLeft(gVoiture.GetTempLeft() + 1);
	   	gVoiture.Gauche();
	}
	else
	  gVoiture.Avancer();

	// On effectue les ordres pendant X ms
	if (gVoiture.GetTempLeft() > 20)
		gVoiture.SetLeft(0);
	if (gVoiture.GetTempRight() > 20)
		gVoiture.SetRight(0);

	// Delai de delay_ms ms entre 2 mesures
	// Le d�lai  sera d�fini en fonction du temps qu'on a mis a realiser
	// la mesure de distance
	if(gVoiture.GetDelai() - lDuree > 0)
	{
		delay(gVoiture.GetDelai() - lDuree);
	}
}
