void setup() 
{
  setup_Serial_Comunication(9600);
  
  // ServoMoteur surlequel repose le capteur Ultrason 
  myservo.attach(3);
  
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

  //Positionnement du servomoteur a 90 degres
   myservo.write(90);

   //Stop le robot
  _mStop();
} 

void loop() 
{
   // Mise a jour de la position du servomoteur
    myservo.write(AngleServo);

    // Mesure sur le capteur Ultrason
    int lDistance = Distance_test();

    if (debug == 1)
    {
      Serial.print("lDistance=");
      Serial.print(lDistance);
      Serial.print(" Angle mot = ");
      Serial.println(AngleServo);
    }

    // Déplacement du Servomoteur pour préparer la nouvelle mesure 
    // Balayage de l'angle 30 a 170
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

    // Détection d'un obstacle en fonction du seuil défini
    if(lDistance < Obstacle && Right == 0 && Left == 0)
    {
      // Si le capteur était positionné entre 30 et 90 
      // -> Déplacement à gauche 
      if(AngleServo < 90)
      {
        Left = 1;
        Right = 0;
        TempoLeft = 0;
        TempoDroite = 0;
      }
      else if (AngleServo > 90)
      {
        // Si le capteur était positionné entre 90 et 170 
        // -> Déplacement à gauche
        Right = 1;
        Left = 0;
        TempoDroite = 0;
        TempoLeft = 0;
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
    
    // On effectue les ordres pendant X ms 
    if (TempoLeft > 20)
      Left = 0;
    if (TempoDroite > 20)
      Right = 0;    

    // Delai de delay_ms ms entre 2 mesures
    delay(delay_ms);
                     
}

