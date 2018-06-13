#include <cstdio>
#include <cmath>
#include <cstdlib>

int main(int argc, char** argv)
{
    float x = 0.0;
    float y = 0.0;

    // La boucle incrémentera 100 fois de 0.1 la variable x.
    // Elle calcule y = sin(x * pi), et affiche les valeurs
    // de x et y.
    // Lorsque y == 0.0, on ajoute "!!!" à la fin de la ligne. 
    for (int i = 0; i < 101; ++i) {
        y = sin(x * M_PI);

        // Note: "%9f" indique qu'on souhaite avoir exactement 9 caractères
        // pour afficher la valeur, incluant les décimales et le signe.
        // Si la valeur prend moins de 9 caractères, printf aligne à droite et
        // ajoute des espaces à gauche.
        // Ceci permet d'aligner visuellement les valeurs en colonnes.
        printf("x: %9f, sin(x * pi): %9f ", x, y);
        if (y == 0.0) {                           
            printf("!!!");                        
        }                                         
        printf("\n");

        x += 0.1;
    }

    return 0;
}
