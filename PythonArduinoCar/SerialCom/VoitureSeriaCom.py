# -*- coding: utf-8 -*-
'''
Created on 8 oct. 2018

@author: nmeo
'''
import threading
from SerialCom.SerialCom import SerialCom

class VoitureSerialCom(SerialCom, threading.Thread):
    '''
    Assure la communication avec la voiture Arduino Car
    Hérite de la classe Sérial Com
    '''

    def __init__(self, pFenetrePrincipale, pPort, pBaud):
        '''
        Constructor
        '''
        super().__init__(pPort, pBaud)
        # Initialise le thread
        threading.Thread.__init__(self)
        
        # Indique l'état du thread
        self.Run = True
        
        # Lien vers la fenetre principale
        self.FenetrePrincipale = pFenetrePrincipale
        
        #Dictionnaire contenant pour clé l'angle auquel on a réalisé la mesure et pour valeur la mesure 
        self.DictionnaireMesure = {}
    
    def run(self):
        """
        Thread de la communication série
        """
        while self.Run:
            self.lireMessage()
    
    def lireBufferReception(self):
        """
        Methode permettant de lire le message provenant de l'arduino car
        pData contient le tableau recu sans l'entete
        """
        print(self.mBufferReception)
        lDataSplit = self.mBufferReception.split(';')
        lDataSplit.remove('')

        lNombreElement = int(lDataSplit[0])
        lAngleTab = lDataSplit[1:lNombreElement+1]
        lValeurTab = lDataSplit[lNombreElement+1:]
        
        # Calcul des angles correspondant aux mesures
        for lAngle, lValeur in zip(lAngleTab, lValeurTab):
                self.DictionnaireMesure[int(lAngle)] = int(lValeur)

        self.RemplirCanvas()
        
    def RemplirCanvas(self):
        """
        Cette méthode met a jour l'interface graphique apres reception  du buffer
        """
        self.FenetrePrincipale.SupprimerTag("TEMPSREEL")
        for lItem in self.DictionnaireMesure.items():
            self.FenetrePrincipale.PrintPointPolaire(lItem[0], lItem[1], "TEMPSREEL")
    
    def __str__(self):
        """
        Methode permettant d'afficher le dernier dictionnaire recu sur le canvas
        """
        for item in self.DictionnaireMesure.items():
            self.FenetrePrinciaple.PrintPointPolaire(item(0), item(1))
        