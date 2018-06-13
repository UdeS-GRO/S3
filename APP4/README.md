# S3APP4r-GRO300

Ce dépôt contient le code nécessaire pour la résolution de l'APP 4 de la session 3 du programme de génie robotique.

## Introduction

Premièrement, vous devez clôner ce dépôt sur votre espace de travail Linux (votre RaspberryPi, par exemple).
On vous suggère de tout d'abord créer un sous-dossier pour l'APP, puis d'y télécharger tout le contenu.

Ouvrez d'abord un terminal, puis entrez ces commandes (le "$" représente l'invite, et ce qui suit "#" des commentaires):

```
$ cd               # S'assure que vous êtes dans votre dossier personnel
$ mkdir s3app4r    # Créé un sous-dossier "s3app4r"
$ cd s3app4r       # Entre dans ce nouveau sous-dossier
```

Vous avez maintenant un dossier dans lequel travailler.
La prochaine ligne clône le dépôt.
N'oubliez pas le "." à la fin, il indique où clôner le dépôt.
Dans ce cas-ci, il s'agit du dossier en cours ("\~/s3app4r/", où "\~" représente votre dossier personnel.

```
$ git clone https://github.com/UdeS-GRO/S3APP4r-GRO300 .
```

## Laboratoire 

L'environnement de départ pour le laboratoire se trouve dans le dossier [lab/](lab/).
Or, la partie 2 sur l'Arduino doit être fait à partir du code de la
problématique.

## Problématique

L'environnement de départ pour la problématique se trouve dans le dossier [prob/](prob/).
La structure est très similaire à ce qu'y vous a été fourni dans le cadre du
projet de session.
En effet, le code Arduino dépend des mêmes librairies pour la communication avec
les moteurs, les capteurs, et le RaspberryPi par le port série.

