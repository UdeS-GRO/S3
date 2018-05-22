# GRO_S3_Projet
Codes d'exemples pour projet S3 génie robotique

## Guide
### Initialisation des dossiers
- Sur le raspberryPi, ouvrir une invite de commande (CTRL + ALT + T)
- Executer la commande suivante 
```
git clone https://github.com/UdeS-GRO/GRO_S3_Projet.git
```
- Initialiser ArduinoIDE en le démarant une première fois
- Tranférer le contenu du dossier /home/pi/GRO_S3_Projet/LibrairiesArduino vers /home/pi/Arduino/Librairies

### Initialisation de l'Arduino
- Connecter l'Arduino au raspberryPI avec le cable USB
- Ouvrir le fichier /home/pi/GRO_S3_Projet/identification/CodeArduino/identification/identification.ino
- Choisir le bon type de carte Atmega2560(mega2560) sous l'onglet Tools->Board
- Choisir le bon port de communication serie correspondant à l'Arduino, sous l'onglet Tools->Port
- Vérifier et téléverser le programme sur l'arduino (Boutons Verify et Upload).

### Initialisation de l'application QT
- Ouvrir le fichier /home/pi/GRO_S3_Projet/identification/codeQt/identification.pro
- Dans QtCreator sélectionner le bouton "Configure project"
- Lancer l'application avec le bouton PLAY.
