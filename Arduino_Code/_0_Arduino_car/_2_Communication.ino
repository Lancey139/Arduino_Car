/*
 * Les fonctions présentent dans cet onglet sont celles permettant la gestion
 * de la communication établie via Bleutooth
 */

void setup_Serial_Comunication(int pBaud)
{
  Serial.begin(pBaud);
  mReadingHeader = false;
}

void Serial_Write(char * p_length, char * p_message)
{
  int l_length = atoi(p_length);
  
  // Envoi de l'entete
  Serial.write(Start);
  Serial.write(p_length[0]);
  Serial.write(p_length[1]);
  Serial.write(p_length[2]);
  Serial.write(End);

  // Envoi du message
  for( int i = 0; i < l_length; ++i)
  {
    Serial.write(p_message[i]);
  }

  Serial.flush();
  
} //Serial_Write()



int Serial_Read()
{
  byte l_incomingByte;

  while(Serial.available() > 0) 
  {
      // read the incoming byte:
      l_incomingByte = Serial.read();
      switch (l_incomingByte)
      {
        case Start:
          mReadingHeader = true;
          break;
        case End:
          mReadingHeader = false;
          m_sizeofMessage = atoi(m_buffer);
          //m_message = new char[m_sizeofMessage];
          for(int i = 0; i < 100; ++i)
          {
            m_message[i]=';';
          }
          
          m_cpt=0;
          break;
        default:
         if(mReadingHeader && m_cpt < SIZEOF_MESSAGESIZE)
          {
            m_buffer[m_cpt] = l_incomingByte;
            ++m_cpt;
          }
          Read_Message(l_incomingByte);
          break;
      }   
  }
}

void Read_Message(byte p_incomingByte)
{
  if( ! mReadingHeader)
  {
    if (m_cpt < m_sizeofMessage)
    {
        // read the incoming byte:
        m_message[m_cpt] = p_incomingByte;
        ++m_cpt;
    }
    
    if (m_cpt == m_sizeofMessage)
    {
      m_cpt =0;
      // Analyse la trame
      //Extraction de l'id
      // Valait char id[4] = ";;;\0"; a retester
      char id[4] = ";;;";
      
      for ( int i = 0; i < 3 ; ++i)
      {
        id[i] = m_message[i];
      }
      if( strcmp(id, "ID1") == 0)
      {
        int exemple = 1;
      }
    }
  }
}

int Convertion(int Centaine, int Dizaine, int Unite)
{
  return Centaine*100 + Dizaine *10 + Unite;
}

