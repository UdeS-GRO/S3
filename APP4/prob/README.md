# S3APP4r - Problématique

Ce dossier contient le code de départ pour la résolution de la problématique de
l'APP 4 de la session 3 du programme de génie robotique.
Il est très similaire au code fourni pour le projet de session, et dépend des
mêmes librairies pour le code Arduino.
Nous assumons donc que vous avez déjà correctement installé le contenu du
dossier "librairieArduino/" du projet sur votre poste de travail ou RaspberryPi.

Pour résoudre la problématique, vous devrez travailler dans deux fichiers :
ExemplePID.ino pour l'implémentation du PID et la communication des variables
d'état sur l'Arduino, et robotdiag.cpp pour la partie synchronisation dans
l'application Qt.
En effet, pour la remise de votre solution, vous n'aurez à transmettre que ces
deux fichiers.

Vous êtes évidemment invités à consulter le contenu des autres fichiers de
l'application Qt, puisque ceux-ci vous serons probablement utiles dans le cadre
du projet de conception.
Or, la solution de la problématique peut être entièrement contenue dans ces deux
fichiers.

## Analyse du temps d'exécution du PID

Pour vous aidez dans l'écriture du pseudo-code vous permettant d'analyser le
temps d'exécution de votre PID, un assembleur primitif pour la machine virtuelle
simplifiée est disponible dans le sous-dossier [vm_asm](vm_asm/).

