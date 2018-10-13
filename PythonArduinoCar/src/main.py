# -*- coding: utf-8 -*-
'''
Created on 1 oct. 2018

@author: Nicolas
'''
from InterfaceGraphique.FenetrePrincipale import FentrePrincipale
from SerialCom.VoitureSeriaCom import VoitureSerialCom
import tkinter

if __name__ == '__main__':
    print("*** Démarrage du programme Arduino Car ***")
    
    # Contient l'acces a la fentre principale
    lMainWindows =  tkinter.Tk()
    lMainInterface = FentrePrincipale(lMainWindows)
    
    # Initialisation de la communication série
    lVoitureSerialCom = VoitureSerialCom(lMainInterface, "COM6", 9600)
    lVoitureSerialCom.start()
    
    lMainWindows.mainloop()
    
    lVoitureSerialCom.Run = False
    while lVoitureSerialCom.is_alive():
        # On attend la fermeture du thread
        pass
    
    print("*** Fin du programme Arduino Car ***")