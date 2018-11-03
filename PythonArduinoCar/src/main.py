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
    lMainInterface.DemarrerThreadSerie("COM8", 9600)

    lMainWindows.mainloop()

    print("*** Fin du programme Arduino Car ***")