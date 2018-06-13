#include "compiler.hpp"
#include "vm.hpp"
#include "ast.hpp"
#include <cstdio>

int main(int argc, char** argv)
{
    using namespace vm;

    std::string fname;

    // Chargement et compilation du code
    // Si on ne spécifie pas de fichier en argument, le programme compilera
    // l'entrée standard (donc ce qu'on entre au clavier puis termine avec
    // Ctrl-D).
    if (argc >= 2) {
        fname = std::string(argv[1]);
    }
    Compiler c(fname);

    // Iniitialisation des variables de base (pour éviter des erreurs d'accès
    // mémoire si certaines ne sont pas initialisées dans l'assembleur).
    
    CPU::memory["Q"]        = 0.0;
    CPU::memory["Q_D"]      = 0.0;
    CPU::memory["Q_DES"]    = 0.0;
    CPU::memory["K_P"]      = 0.0;
    CPU::memory["CMD"]      = 0.0;

    CPU::registers[R1]      = 0.0;
    CPU::registers[R2]      = 0.0;
    CPU::registers[R3]      = 0.0;
    CPU::registers[R4]      = 0.0;

    for (int i = 0; i < 10; ++i) {
        c.run();
        CPU::memory["Q"] += CPU::memory["CMD"];
        printf("Q: %f, Q_DES: %f, CMD: %f\n",
               CPU::memory["Q"],
               CPU::memory["Q_DES"],
               CPU::memory["CMD"]
        );
    }

    printf("Done.\n");
    return 0;
}

