# Arduino_Car

Projet permettant à une voiture arduino car (http://www.freenove.com/) de se déplacer suivant 2 comportements: 
* Pilote Automatique : Grace à un capteur ultrason en rotation permanente à l'avant du véhicule, la voiture détecte les obstacles et les contourne. Dans le cas ou il n'y a pas d'obstacle, elle avance en ligne droite.
* Pilote Manuel : Via une interface Python et une liaison série établie via Bleutooth, un utilisateur peut prendre le controle du véhicule à distance pour le piloter. Il a sur l'interface une map permettant de visualiser ce que voit l'arduino car grace à son ultrason. Par ailleurs, il a également la possibilité de repasser en mode automatique.
 
