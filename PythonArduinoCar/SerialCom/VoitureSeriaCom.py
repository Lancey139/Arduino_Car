'''
Created on 8 oct. 2018

@author: nmeo
'''
from SerialCom import SerialCom

class VoitureSerialCom(SerialCom):
    '''
    Assure la communication avec la voiture Arduino Car
    H�rite de la classe Serial Com
    '''

    def __init__(self, pFenetrePrincipale):
        '''
        Constructor
        '''
        # Lien vers la fenetre principale
        self.FenetrePrinciaple = pFenetrePrincipale
        
        #Dictionnaire contenant pour cl� l'angle auquel on a r�alis� la mesure et pour valeur la mesure 
        self.DictionnaireMesure = {}
        
        # Contient le pas d'incr�mentation du moteur
        self.PasIncrementation = 0 
        
        #Contient l'angle bas du balayage
        self.AngleBas = 0
        
        #Contient l'angle haut du balayge
        self.AngleHaut = 0
    
    
    def LireMessageVoiture(self, pData):
        """
        M�thode permettant de lire le message provenant de l'arduino car
        pData contient le tableau recu sans l'entete
        """
        lDataSplit = pData.split(';')
        self.AngleBas = lDataSplit[0]
        self.AngleHaut =  lDataSplit[1]
        self.PasIncrementation = lDataSplit[2]
        
        self.DictionnaireMesure.clear()
        
        #TODO a completer
    
    
    def AfficherMesure(self):
        """
        M�thode permettant d'afficher le dernier dictionnaire recu sur le canvas
        """
        for item in self.DictionnaireMesure.items():
            self.FenetrePrinciaple.PrintPointPolaire(item(0), item(1))
        