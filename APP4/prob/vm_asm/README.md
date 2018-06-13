# Assembleur pour machine virtuelle simplifiée

Pour tester votre pseudo-code assembleur, vous pouvez utliser le programme
"machine" fourni ici.
Vous pouvez compiler le programme avec make, comme pour les exercices du
laboratoire.

Lisez d'abord le code contenu dans "machine.cpp" pour connaître les variables
d'état simulées. 
Ensuite, vous pouvez regarder l'implémentation partielle d'un PID dans le
fichier "test.pid".

Pour tester votre programme, vous pouvez utiliser l'exécutable de cette façon :

    $ ./machine pid.asm

Le résultat de 10 exécutions du programme s'afficheront, ou un message d'erreur
vous indiquera que votre programme a un problème de syntaxe. 

## Conception

L'assembleur a été conçu à l'aide des outils Flex et Bison.
Le code source décrivant la grammaire du langage se trouve dans le dossier ref/.
Les fichiers parser.cpp, parser.hpp et tokens.cpp ont été générés
automatiquement à partir de ces fichiers sources.

