#include "robotdiag.h"
#include "robotsim.h"
#include <vector>
#include <queue>
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace robotdiag;

namespace {
    bool run_;                      // Indique si le fil d'exportation
                                    // fonctionne.

    std::queue<RobotState>  queue_; // File d'attente à l'exportation.
    std::vector<RobotState> data_;  // Toutes les données reçues.

    std::thread export_thread_;
}

// Fonction d'initialisation appelée une fois au démarrage.
void robotdiag::init()
{
    // Démarre le simulateur:
    robotsim::init(8, 10, 3);   // Spécifie le nombre de moteurs à simuler (8)
                                // et le délai moyen entre les événements
                                // (10 ms) plus ou moins un nombre aléatoire
                                // (3 ms).

    // Indique que le système de diagnostic fonctionne (mis à 'false') lors de
    // la fermeture pour interrompre le fil d'exportation).
    run_ = true;

    // Démarrage du système d'exportation.
    export_thread_ = std::thread(export_loop);

}

void robotdiag::push_event(RobotState evt)
{
    // Conserve toutes les données
    data_.push_back(evt);
    // Ajoute le dernier événement à la file d'exportation
    queue_.push(evt);

}

// Fonction d'exportation vers CSV.
// Vérifie constamment si de nouvelles données sont disponibles.
// Si c'est le cas, les exportent ligne par ligne dans
// "/tmp/robotdiag.csv".
void robotdiag::export_loop()
{
    FILE* out = fopen("/tmp/robotdiag.csv", "w");

    if (out == NULL) {
        printf("ERROR: Cannot open output file.\n");
        return;
    }

    // En-tête du fichier CSV, respectez le format.
    fprintf(out, "motor_id;t;pos;vel;cmd\n");

    while (run_) {
        while (!queue_.empty()) {
            RobotState evt = queue_.front();
            queue_.pop();

            // TODO: Format csv à compléter 
            fprintf(out, "%d;%f;\n", evt.id, evt.cur_pos);
        }
    }

    fclose(out);
}

// Fonction appellée à la fermeture de l'application.
// Écrit des statistiques à l'écran.
void robotdiag::stop_and_join()
{
    run_ = false;

    robotsim::stop_and_join();
    export_thread_.join();

    printf("Final vector size: %zu\n", data_.size());
}
