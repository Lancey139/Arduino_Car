# -*- coding: utf-8 -*-
'''
Created on 4 oct. 2018

@author: nmeo
'''
from tkinter import *
import math
import threading
from threading import Lock

from InterfaceGraphique.Constantes import gVert, gModeAuto, gModeManuel,\
    gModeBalayage, gNModeBalayage, gModeSecurite, gNModeSecurite, gNToutDroit,\
    gToutDroit, gGauche, gDroite, gCommandeAutoClavier
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
        
        # Création du panel
        self.panel = PanedWindow(self.mainWindows, orient=HORIZONTAL)
        
        # Creation du canvas qui contiendra la carte que l'on créer
        self.canvas = Canvas(self.panel , width = self.largeur, height = self.hauteur)
        self.panel.add(self.canvas)
        
        # Creation des éléments graphiques
        
        #Panel des radios bouttons
        self.panel_radio =  PanedWindow(self.panel, orient=VERTICAL, width = 200, relief = 'sunken')
        
        labelAutoManu = Label(text = "Choix Auto / Manuel", anchor = W)
        self.ValeurAutoManu = [ gModeAuto, gModeManuel]
        self.VarAutoManu = StringVar()
        self.VarAutoManu.set( self.ValeurAutoManu[0])
        self.panel_radio.add(labelAutoManu)
        self.RadioButtonModeAuto = Radiobutton(self.panel_radio, variable=self.VarAutoManu, value = gModeAuto,
                                                text="Mode Automatique", anchor = W, command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeAuto)
        self.RadioButtonModeManu = Radiobutton(self.panel_radio, variable=self.VarAutoManu, value = gModeManuel,
                                                text="Mode Manuel", anchor = W,command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeManu)
        
        labelBalai = Label(text = "Choix Balyage / Non Balyage", anchor = W)
        
        self.ValeurBalai = [ gModeBalayage, gNModeBalayage]
        self.VarBalai = StringVar()
        self.VarBalai.set( self.ValeurBalai[0])
        
        self.panel_radio.add(labelBalai)
        self.RadioButtonModeBalai = Radiobutton(self.panel_radio, variable=self.VarBalai,
                                                 value = gModeBalayage, text="Mode Balayage", anchor = W, command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeBalai)
        self.RadioButtonModeNBalai = Radiobutton(self.panel_radio, variable=self.VarBalai,
                                                  value = gNModeBalayage, text="Mode Non Balayage", anchor = W, command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeNBalai)
        
        labelSecu = Label(text = "Choix Sécurité / Non Sécurisé", anchor = W)
        
        self.ValeurSecu = [ gModeSecurite, gNModeSecurite]
        self.VarSecu = StringVar()
        self.VarSecu.set( self.ValeurSecu[0])
        
        self.panel_radio.add(labelSecu)
        self.RadioButtonModeSecu = Radiobutton(self.panel_radio, variable=self.VarSecu,
                                                value = gModeSecurite, text="Mode Securisé", anchor = W,command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeSecu)
        self.RadioButtonModeNSecu = Radiobutton(self.panel_radio, variable=self.VarSecu,
                                                 value = gNModeSecurite, text="Mode Non Sécurisé", anchor = W,command = self.ListenerRadio)
        self.panel_radio.add(self.RadioButtonModeNSecu)
        
        self.panel_radio.pack(side=TOP, expand=Y, fill=BOTH, pady=2, padx=2)
        # Ajout d'un deuxieme panel indiquant les touches de controle
        self.panel_control =  PanedWindow(self.panel, orient=VERTICAL, width = 150, relief = 'sunken')
        
        self.panel_control.add(Label(text = "Rappel des control : " ,anchor = W))
        self.panel_control.add(Label(text = "Tout droit : " + gToutDroit ,anchor = W))
        self.panel_control.add(Label(text = "Gauche : " + gGauche ,anchor = W))
        self.panel_control.add(Label(text = "Droite : " + gDroite ,anchor = W))
        self.panel_control.add(Label(text = "" ,anchor = W))
        
        self.panel_control.pack(side=LEFT, expand=Y, fill=BOTH, pady=2, padx=2)
        
        self.panel.add(self.panel_radio)
        self.panel.add(self.panel_control)
        self.panel.pack(side=TOP, expand=Y, fill=BOTH, pady=2, padx=2)
        
        # Ajout des listener sur clavier et la fermeture
        self.mainWindows.bind("<Key>", self.ClavierAppui)
        self.mainWindows.bind("<KeyRelease>", self.ClavierRelache)
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
        
    def ClavierAppui(self, event):
        """
        Evenement appeler sur appui d'une touche sur le clavier
        """
        lChar = repr(event.char)
        lChar= lChar.upper()
        lChar = lChar.replace("\'","")
        if lChar in gCommandeAutoClavier:
            self.VoitureSerialCom.envoyerCommande(lChar)
        
    def ClavierRelache(self, event):
        """
        Evenement appeler sur relache d'une touche sur le clavier
        """
        lChar = repr(event.char)
        lChar= lChar.upper()
        lChar = lChar.replace("\'","")
        if (lChar == 'Z'):
            self.VoitureSerialCom.envoyerCommande(gNToutDroit)
        
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
        
    def ListenerRadio(self):
        """
        Listener sur les boutons radios
        On envoie les commandes correspondantes
        """
        self.VoitureSerialCom.envoyerCommande(self.VarAutoManu.get())
        self.VoitureSerialCom.envoyerCommande(self.VarBalai.get())
        self.VoitureSerialCom.envoyerCommande(self.VarSecu.get())
        
    
        
        