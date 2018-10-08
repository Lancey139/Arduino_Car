# -*- coding: utf-8 -*-
'''
Created on 4 oct. 2018

@author: nmeo
'''
import tkinter
import math
from InterfaceGraphique.Constantes import gVert

class FentrePrincipale(object):
    '''
    classdocs
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
        
        # Affichage de l'origine
        self.PrintPointCartesien((0,0), '#FF0000')
        
    def PrintPointCartesien(self, pTuple, pColor = gVert):
        """
        Affiche sur le canvas le point passé en paramètre
        pTuple correspond au coordinées carthésiennes
        """
        lX = pTuple[0] + self.origin[0]
        # L'axe des Y va du haut vers le bas sur le canvas donc on inverse ici
        lY = self.origin[1] - pTuple[1] 
        self.canvas.create_oval(lX-1, lY-1, lX+1 , lY+1, fill = pColor)
    
    def PrintPointPolaire(self, pAngle, pDistance, pColor = gVert):
        """
        Affiche sur le canvas le point passé en paramètre en coordonnées polaires
        """
        lXCarth = pDistance* math.cos(math.radians(pAngle))
        lYCarth = pDistance * math.sin(math.radians(pAngle))
        self.PrintPointCartesien((lXCarth,lYCarth), pColor)
        
        
        