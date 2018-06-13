# Code d'exemple d'identification pour projet S3 génie robotique

### Matériels requis
- RaspberryPi (avec image du projet)
- Arduino Mega2560
- Carte «hat» ArduinoX
- Moteurs DC avec leur contrôleur
- Potentiomètre Vex (sur le connecteur J19)

### Initialisation des dossiers (Ignorer cet étape si vous avez déjà cloné le dossier sur github)
- Sur le RaspberryPi, ouvrir une invite de commande (CTRL + ALT + T)
- Exécuter la commande suivante:
```
git clone https://github.com/UdeS-GRO/S3.git
```

### Initialisation des dossiers sur l'environnemnt de travail ArduinoIDE
- Initialiser les dossiers de ArduinoIDE en le démarrant une première fois
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
- Vous pouvez maintenant envoyer des pulses aux moteurs et sauvegarder un historique des états du système en format «.csv» sur le bureau.


## *Troubleshooting* 
### Si votre version locale du dossier S3 n'est plus à jour par rapport à gitHub
- Exécuter les commandes suivantes dans une invite de commande afin de récupérer et appliquer les modifications sur github:
```
cd ~/S3
git pull
```
