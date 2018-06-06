# Code d'exemple d'identification pour projet S3 génie robotique

### Initialisation des dossiers (Ignorer cet étape si vous avez déjà cloné le git)
- Sur le RaspberryPi, ouvrir une invite de commande (CTRL + ALT + T)
- Exécuter la commande suivante:
```
git clone https://github.com/UdeS-GRO/S3.git
```
### Initialisation des dossiers Arduino (Si la première utilisation de ArduinoIDE)
- Initialiser ArduinoIDE en le démarrant une première fois
- Copier le contenu du dossier */home/pi/S3/Projet/LibrairiesArduino*
  dans le dossier */home/pi/Arduino/Librairies*

### Initialisation de l'Arduino
- Connecter l'Arduino au RaspberryPI avec le cable USB
- Ouvrir le fichier */home/pi/S3/Projet/identification/CodeArduino/identification/identification.ino*
- Choisir le bon type de carte (Atmega2560(mega2560)) sous l'onglet *Tools -> Board*
- Choisir le bon port de communication serie correspondant à l'Arduino, sous l'onglet *Tools -> Port*
  - (Si vous n'avez pas le modèle de marque Arduino, il est possible que le nom ne s'affiche pas dans les ports disponible)
    - Dans ce cas, choisir le port USB0
- Vérifier et téléverser le programme sur l'arduino (Boutons Verify et Upload).

### Initialisation de l'application QT
- Ouvrir le fichier */home/pi/S3/Projet/identification/codeQt/identification.pro*
- Dans QtCreator sélectionner le bouton "Configure project"
  - (Si vous n'avez pas le modèle de marque Arduino vous devrai changer le port de communication dans le code *yourmainwindow.h*)
    - Dans ce cas, changer le port *ttyACM0* pour *ttyUSB0*
- Lancer l'application avec le bouton PLAY.
