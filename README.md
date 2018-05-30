# GRO_S3_Projet
Code d'exemple d'identification pour projet S3 génie robotique

## Guide
### Initialisation des dossiers
- Sur le RaspberryPi, ouvrir une invite de commande (CTRL + ALT + T)
- Exécuter la commande suivante:
```
git clone https://github.com/UdeS-GRO/GRO_S3_Projet.git
```
- Initialiser ArduinoIDE en le démarrant une première fois
- Copier le contenu du dossier */home/pi/GRO_S3_Projet/LibrairiesArduino*
  dans le dossier */home/pi/Arduino/Librairies*

### Initialisation de l'Arduino
- Connecter l'Arduino au RaspberryPI avec le cable USB
- Ouvrir le fichier */home/pi/GRO_S3_Projet/identification/CodeArduino/identification/identification.ino*
- Choisir le bon type de carte (Atmega2560(mega2560)) sous l'onglet *Tools -> Board*
- Choisir le bon port de communication serie correspondant à l'Arduino, sous l'onglet *Tools -> Port*
  - (Si vous n'avez pas le modèle de marque Arduino, il est possible que le nom ne s'affiche pas dans les ports disponible)
    - Dans ce cas, choisir le port USB0
- Vérifier et téléverser le programme sur l'arduino (Boutons Verify et Upload).

### Initialisation de l'application QT
- Ouvrir le fichier */home/pi/GRO_S3_Projet/identification/codeQt/identification.pro*
- Dans QtCreator sélectionner le bouton "Configure project"
  - (Si vous n'avez pas le modèle de marque Arduino vous devrai changer le port de communication dans le code *yourmainwindow.h*)
    - Dans ce cas, changer le port *ttyACM0* pour *ttyUSB0*
- Lancer l'application avec le bouton PLAY.
