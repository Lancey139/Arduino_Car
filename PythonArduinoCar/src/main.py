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
    
    lInterface.PrintPointCartesien((10,10))
    
    mainWin.mainloop()