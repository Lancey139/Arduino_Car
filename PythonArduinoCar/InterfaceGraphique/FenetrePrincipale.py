# -*- coding: utf-8 -*-
'''
Created on 4 oct. 2018

@author: nmeo
'''
import tkinter
import math
import threading
from threading import Lock

from InterfaceGraphique.Constantes import gVert
from SerialCom.VoitureSeriaCom import VoitureSerialCom


class ThreadGraphique(threading.Thread):
    """
    Thread en charge de l'interface graphique
    """
    def __init__(self):
        # Initialise le thread
        threading.Thread.__init__(self)

        
        # Indique l'état du thread
        self.EnCours = False
        
    def run(self):
        """
        Run l'interface graphique
        """
        self.EnCours = True

        self.MainWindows.mainloop()
        #Destruction de l'interface 
        del self.MainWindows
        self.EnCours = False     
    

class FentrePrincipale(object):
    '''
    Fentre principale de l'application
    Manage aussi le thread de l'interface série
    '''

    def __init__(self, pMainWin):
        '''
        Constructor
        '''
        self.mainWindows = pMainWin
        self.mainWindows.title("Arduino Car Interface")
        
        # Taille de l'ecran
        self.hauteur = 250
        self.largeur = 500
        
        # Creation du canvas qui contiendra la carte que l'on créer
        self.canvas = tkinter.Canvas(self.mainWindows , width = self.largeur, height = self.hauteur)
        self.canvas.pack()
        
        # Ajout des listener sur clavier et la fermeture
        self.mainWindows.bind("<Key>", self.Clavier)
        self.mainWindows.bind("<Destroy>", self.Destroy)
        
        # Definition du point qui servira d'origine au repere
        self.origin = (self.largeur/2,self.hauteur/2)
        
        # S'occupe du multi threading
        self.Mutex = Lock()
        
        # Affichage de l'origine
        self.PrintPointCartesien((0,0), '#FF0000')
        
        # Lien vers la communication seire
        self.VoitureSerialCom = None
    
    def PrintPointCartesien(self, pTuple, pTag, pColor = gVert):
        """
        Affiche sur le canvas le point passé en paramètre
        pTuple correspond au coordinées carthésiennes
        """
        lX = pTuple[0] + self.origin[0]
        # L'axe des Y va du haut vers le bas sur le canvas donc on inverse ici
        lY = self.origin[1] - pTuple[1] 
        
        self.Mutex.acquire()
        self.canvas.create_oval(lX-1, lY-1, lX+1 , lY+1, fill = pColor, tags  = pTag)
        self.Mutex.release()
        
    
    def PrintPointPolaire(self, pAngle, pDistance, pTag, pColor = gVert):
        """
        Affiche sur le canvas le point passé en paramètre en coordonnées polaires
        """
        lXCarth = pDistance* math.cos(math.radians(pAngle))
        lYCarth = pDistance * math.sin(math.radians(pAngle))
        self.PrintPointCartesien((lXCarth,lYCarth), pTag, pColor)
    
    def SupprimerTag(self, pTag):
        """
        Supprime les éléments du graph identifié par ce tag
        """    
        self.Mutex.acquire()
        self.canvas.delete(pTag)
        self.Mutex.release()
        
    def Clavier(self, event):
        """
        Evenement appeler sur appui d'une touche sur le clavier
        """
        lChar = repr(event.char)
        lChar= lChar.upper()
        self.VoitureSerialCom.envoyerCommande(lChar)
        
    def DemarrerThreadSerie(self, pPortCom, pBaud):
        """
        Méthode permettant d'initialiser la connection serie
        """
        # Initialisation de la communication série
        self.VoitureSerialCom = VoitureSerialCom(self, pPortCom, pBaud)
        self.VoitureSerialCom.start()
        
    def StopThreadSerie(self):
        """
        Methde permettant de stopper le thread serie
        """
        self.VoitureSerialCom.Run = False
        while self.VoitureSerialCom.is_alive():
            # On attend la fermeture du thread
            pass
    
    def Destroy(self, event):
        """
        Methode appelle a la fermeture de la fenetre
        """
        self.StopThreadSerie()
        
    
        
        