# -*- coding: utf-8 -*-
'''
Created on 7 oct. 2018

@author: Nicolas
'''

import serial

class SerialCom(object):
    """
    Classe en charge de la communication série avec l'arduino
    """
    def __init__(self, pPort, pBaud):
        self.mPort = pPort
        self.mBaud = pBaud
        self.mSocket = serial.Serial(pPort, pBaud , timeout=1)
        self.mStart = 'S'
        self.mEnd = 'E'
        self.mBufferEnteteEnvoi = []
        self.mBufferEnvoi = []
        self.mBufferEnteteReception = []
        self.mBufferReception = ""
        self.mEntete = False
        self.mTailleMessageEnCours = 0
       
        
    def lireMessage(self):
        lReturn = 0
        lByteLu = self.mSocket.read()
        lByteLu = lByteLu.decode()
        """
        Gestion de lecture de l'entete
        """
        if lByteLu == self.mStart:
            self.mEntete = True
        elif lByteLu == self.mEnd:
            self.mEntete = False
            self.lireEntete()
        elif self.mEntete:
            self.mBufferEnteteReception.append(lByteLu)
        elif self.mTailleMessageEnCours != 0:
            """
            Lecture du buffer
            """
            if self.mBufferReception.__len__() < self.mTailleMessageEnCours:
                #On rempli le buffer
                self.mBufferReception+=lByteLu
            if self.mBufferReception.__len__() == self.mTailleMessageEnCours:
                #Fin de la lecture du message
                self.mTailleMessageEnCours = 0
                self.lireBufferReception()
            
        return lReturn
            
    
    def lireEntete(self):
        if self.mBufferEnteteReception.__len__() == 3:
            lTaille = self.conversionEntier(self.mBufferEnteteReception[0],
                                          self.mBufferEnteteReception[1],
                                          self.mBufferEnteteReception[2])
            self.mTailleMessageEnCours = lTaille
            self.mBufferEnteteReception = []
            # On recoit une nouvelle entete on vide le buffer
            self.mBufferReception = ""
        else:
            print("Erreur lors de la lecture de l\'entete", self.mBufferEnteteReception)
            self.mTailleMessageEnCours =0
                
                
    def lireBufferReception(self):
        """
        Méthode à surcharger
        """
        print("Message recu", self.mBufferReception)
        
            
    def construireMessage(self, pContenu):
        """
        Construction du message
        """
        self.mBufferEnvoi = []
        
        for element in pContenu.replace('\'',''):
            self.mBufferEnvoi.append(element)
            self.mBufferEnvoi.append(';') 
            
        self.mBufferEnvoi.append("\0")
        """
        Construction de l'entete
        """
        self.mBufferEnteteEnvoi = []
        self.mBufferEnteteEnvoi.append( self.mStart)
        lTaille = 0
        for elem in self.mBufferEnvoi:
            lTaille += len(elem)
        self.mBufferEnteteEnvoi += self.conversionEntierToChar(lTaille)
        self.mBufferEnteteEnvoi.append(self.mEnd)
        self.sendMessage()
        
    
    def sendMessage(self):
        print(self.mBufferEnteteEnvoi + self.mBufferEnvoi)
        for elem in self.mBufferEnteteEnvoi + self.mBufferEnvoi:
            self.mSocket.write(elem.encode())
            
    def conversionEntier(self, pCentaine, pDizaine, pUnite):
        return int(pCentaine) *100 + int(pDizaine) *10 + int(pUnite)
    
    def conversionEntierToChar(self, pEntier):
        unite = int(pEntier%10)
        dizaine = int(((pEntier-unite)%100)/10)
        centaine = int((pEntier-10*dizaine-unite)/100)
        
        unite_char = chr((unite+48))
        dizaine_char = chr((dizaine+48))
        centaine_char = chr((centaine+48))
        
        return [centaine_char, dizaine_char, unite_char]
            
                
        
