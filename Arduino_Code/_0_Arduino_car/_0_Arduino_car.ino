/*
From elegoo.com
Main de l'application ARDUI_CAR
*/
#include <Servo.h> //servo library
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

int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
void _mForward()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 Serial.println("go forward!");
}

void _mBack()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
 Serial.println("go back!");
}

void _mleft()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
 Serial.println("go left!");
}

void _mright()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 Serial.println("go right!");
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
} 
 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
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

void setup() 
{ 
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);
  // Initialisation des entrées sorties     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  //Positionnement du servomoteur a 90 degres
   myservo.write(90);

   //Stop le robot
  _mStop();
} 

void loop() 
{
    myservo.write(AngleServo);//setservo position according to scaled value
    int lDistance = Distance_test();
    /*
    Serial.print("lDistance=");
    Serial.print(lDistance);
    Serial.print(" Angle mot = ");
    Serial.println(AngleServo);
    */
    if (SensRotation == 0)
    {
      AngleServo+= Increment;
      if (AngleServo >= 170)
      {
        SensRotation = 1;
      }
    }
    else
    {
      AngleServo-=Increment;
      if (AngleServo <= 30)
      {
        SensRotation = 0;
      }
    }

    if(lDistance < Obstacle)
    {
      if(AngleServo < 90)
      {
        Left = 1;
        TempoLeft = 0;
      }
      else if (AngleServo > 90)
      {
        Right = 1;
        TempoDroite = 0;
      }
      
    }

    // Ordre donné aux roues
    if(Right ==1)
      _mright();
    else if( Left == 1)
       _mleft();
    else
       _mForward();

    // Mise a jour des ordres
    TempoLeft++;
    TempoDroite++;
    if (TempoLeft > 10)
      Left = 0;
    if (TempoDroite > 10)
      Right = 0;    
    
    delay(10);
                     
}



