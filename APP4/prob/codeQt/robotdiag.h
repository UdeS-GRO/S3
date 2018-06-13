#ifndef ROBOTDIAG_H
#define ROBOTDIAG_H

namespace robotdiag
{
    struct RobotState
    {
        int   id;       // Identifiant du moteur (0: réel)
        float t;        // Temps (en s) 
        float cur_cmd;  // Commande en cours
        float cur_pos;  // Position en cours
        float cur_vel;  // Vitesse en cours
    };

    void push_event(RobotState new_state);

    void init();

    void export_loop();

    void stop_and_join();
}

#endif

