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
        
        # Definition du point qui servira d'origine au repere
        self.origin = (self.largeur/2,self.hauteur/2)
        
        # S'occupe du multi threading
        self.Mutex = Lock()
        
        # Affichage de l'origine
        self.PrintPointCartesien((0,0), '#FF0000')
    
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
        
        