# -*- coding: utf-8 -*-
'''
Created on 1 oct. 2018

@author: Nicolas
'''
import tkinter
from InterfaceGraphique.FenetrePrincipale import FentrePrincipale

if __name__ == '__main__':
    print("*** Démarrage du programme Arduino Car ***")
    mainWin = tkinter.Tk()
    lInterface = FentrePrincipale(mainWin)
    
    for j in range(0,10):
        for i in range(0,360):
            lInterface.PrintPointPolaire(i, j*10)

    
    mainWin.mainloop()