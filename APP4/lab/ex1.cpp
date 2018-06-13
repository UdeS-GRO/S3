#include <cstdio>
#include <thread>
#include <mutex>

// Espace anonyme pour les variables globales et partagées :
namespace {
    int somme_;     // Contiendra la somme (devrait être 50005000).
}

void accum(int d, int f)
{
    // Ajoute les nombres de d à f (inclusivement) à la variable somme_.
    for (int i = d; i <= f; ++i) {
        somme_ += i;
    }
}

int main(int argc, char** argv)
{
    // Ce programme tente d'obtenir la somme des entiers de 1 à 10000 en
    // divisant le travail en quatre fils indépendants.
    // La somme devrait être 50005000.
    // On répète le travail 100 fois pour vérifier si le résultat est constant.
    // On compte également le nombre d'essais valides.
    
    int succes = 0;
     
    for (int i = 0; i < 100; ++i) {
        somme_ = 0;

        // Démarre 4 fils avec chacun une portion égale de 1 à 10000 :
        std::thread t1(accum, 1,    2500);
        std::thread t2(accum, 2501, 5000);
        std::thread t3(accum, 5001, 7500);
        std::thread t4(accum, 7501, 10000);

        // À partir d'ici, les fils sont lancés et le contrôle est
        // immédiatement de retour sur le fil principal alors que les fils 
        // secondaires s'exécutent en parallèle.
        // Or, il faut attendre qu'ils aient terminé leur travail avant
        // d'afficher la somme.
        // Sinon, la somme ne sera certainement pas complète, en plus de causer
        // une erreur lorsque un fil secondaire est détruit alors qu'il est
        // toujours en exécution.
        // Le fil principal doit donc joindre son exécution à ces fils jusqu'à
        // ce que chacun des appels à la fonction "accum" soit terminé :

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // Chaque fil a terminé son travail, on peut maintenant afficher la
        // somme finale.
        
        printf("Somme: %d\n", somme_);

        if (somme_ == 50005000) {
            succes++;
        }
    }

    printf("Nombre de sommes justes (devrait être 100) : %d\n.", succes);

    return 0;
}

