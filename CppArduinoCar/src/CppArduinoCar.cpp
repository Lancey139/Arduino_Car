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

int gGestionIncrement = 0;
int gTempsExection = 0;

void setup()
{
	gVoiture = Voiture();
	gVoitureCom.begin(9600);
	// ServoMoteur surlequel repose le capteur Ultrason
	gServo.attach(pinServoMoteur);
	gServo.write(gAngleBas);
}

int CapteurUltraSon()
{
	// Mise a jour de la position du servomoteur
	gVoiture.OrienterCapteur(gAngleServo);
	gServo.write(gAngleServo);

	// Mesure sur le capteur Ultrason
	int lDistance = gVoiture.MesureDistance();

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

	// Déplacement du Servomoteur pour préparer la nouvelle mesure
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
	return lDistance;
}

void ObstacleOvoidance( int pDistance)
{
	// Détection d'un obstacle en fonction du seuil défini
	if(pDistance < gVoiture.GetObstacle() && gVoiture.GetRight() == 0 && gVoiture.GetLeft() == 0)
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

	// On effectue les ordres pendant 400 ms
	if (gVoiture.GetTempLeft() >= int((400/gVoiture.GetDelai())))
		gVoiture.SetLeft(0);
	if (gVoiture.GetTempRight() >= int((400/gVoiture.GetDelai())))
		gVoiture.SetRight(0);
}



void loop()
{


	// Delai de delay_ms ms entre 2 mesures
	// Le délai  sera défini en fonction du temps qu'on a mis a realiser
	// la mesure de distance
	if (gGestionIncrement >= int(gVoiture.GetDelai()/2))
	{
		gTempsExection = millis();

		int lDistance = CapteurUltraSon();
		ObstacleOvoidance(lDistance);

		gTempsExection = millis()- gTempsExection;

		if(gVoiture.GetDelai() - gTempsExection > 0)
		{
			// Calcul du nouvel incrément en prenant en compte le temps d'execution du code
			// Afin que les méthodes CapteurUltraSon + ObstacleOvoidance soient éxécutées
			// de manière régulière quelquesoit le temps d'éxécution de celle ci
			// La valeur de l'incrément calcul est donc :
			// (Temps entre 2 itérations - Temps excution des méthodes) / 2 -> Nombre de pas
			gGestionIncrement = (gVoiture.GetDelai() - (gVoiture.GetDelai() - gTempsExection)) / 2;
		}
	}

	// Lecture d'eventuelle message entrant
	gVoitureCom.Serial_Read();

	gGestionIncrement ++;
	delay(2);
}
