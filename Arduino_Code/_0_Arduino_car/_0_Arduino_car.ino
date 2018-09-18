/*
Nicolas MEO
Entrée du programme arduino car.
Les includes et les variables globales seront présentées ici
*/
#include <Servo.h> //servo library

/*
 * Déclaration des variables globales
 */
Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 150;

// Distance en cm de détection d'un obstacle
int Obstacle = 40;

// Angle du servo moteur
int AngleServo = 90;
int SensRotation = 0;
int Increment = 5;

// Variable de déplacement
int Left = 0;
int Right = 0;
int TempoLeft = 0;
int TempoDroite = 0;

// Gestion du temps
int delay_ms = 10;

// Mode debug
int debug = 0; 

// Variables pour la communication
#define Start 'S'
#define End 'E'
#define SIZEOF_MESSAGESIZE 3

bool mReadingHeader;
char  m_message[100] ;
int m_sizeofMessage = 0;
char m_buffer[SIZEOF_MESSAGESIZE];
int m_cpt = 0;



