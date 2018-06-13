/* Code d'exemple pour controle PID sur Arduino
 * Auteurs: Jean-Samuel Lauzon, 
 *          Jonathan Vincent
 *          François Ferland
 *          
 * date:    8 avril 2018
*/

/* Fonctions de départ pour le shield Arduino_X */ 


#include "SimpleTimer.h"    // Librairie de chronomètres
#include "ArduinoJson.h"    // Librairie de syntaxe JSON
#include "Fonctions_GRO.h"  // Librairie S3 GRO (capteurs, actionneurs)
#include <SPI.h>            // librairie Communication SPI


/* Constantes */
#define BAUD                115200  // Fréquence de transmission sérielle (bauds)
#define UPDATE_PERIOD_MS    100     // Periode (ms) d'envoie d'etat general

// Les valeurs suivantes correspondent au moteur de test
// TODO: Assurez-vous d'avoir les bonnes valeurs !
#define MOTOR_ENC_CPR       300     // Nombre de cycles par tour de l'encodeur
#define MOTOR_GB_RATIO      100.0   // Ratio de la transmission du moteur (100:1)
          
// Temps (en s) d'un cycle :
const float DT          = UPDATE_PERIOD_MS / 1000.0;
// Facteur de conversion encodeur -> tr/s :
const float ENC_TO_VEL  = 1.0 / (MOTOR_ENC_CPR * MOTOR_GB_RATIO * DT);


/* Variables globales */
Fonctions_GRO s3gro;                // Objet pour l'accès aux actionneurs/capteurs

// Moteurs
int motor1_pwm_   = 0;              // Sortie en PWM du moteur 1 (0..255)
int motor2_pwm_   = 0;              // Sortie en PWM du moteur 2

// Encodeurs (compteur entre cycles)
signed long motor1_enc_count_ = 0;
signed long motor2_enc_count_ = 0;  

// État du moteur à contrôler
float t_        = 0.0;              // Temps depuis le démarrage, en s.
float cur_vel_  = 0.0;              // Vitesse en tr/s.
float des_vel_  = 0.0;              // Consigne (vitesse désirée) en tr/s.
float cur_pos_  = 0.0;              // Position, en nombre de tours.

// Configuration du PID
float K_P = 0.0;                    // Facteur P du PID
float K_I = 0.0;                    // Facteur I du PID.
float K_D = 0.0;                    // Facteur D du PID.

// État du PID (inutilisé pour l'instant, à compléter)
float P_     = 0;                   // Terme proportionnel
float I_     = 0;                   // Terme de l'intégrale
float D_     = 0;                   // Terme de la dérivée 
float err_I_ = 0;                   // Intégrale de l'erreur
float min_I_ = -100;                // Valeur minimale de l'intégrale
float max_I_ =  100;                // Valeur maximale de l'intégrale
float last_err_ = 0;                // Erreur du cycle précédent

// Contrôle du temps
bool    should_send_;               // Indique qu'on est prêt à transmettre l'état.
SimpleTimer timer;                  // objet du chronomètre

bool state_transmit_;    

// Gestion du message JSON
StaticJsonBuffer<500> json_buffer_;
// Message provenant du Pi :
JsonVariant           pi_msg_     = json_buffer_.createObject();
// Message d'état à transmettre au Pi :
JsonObject&           state_msg_  = json_buffer_.createObject();


/* Fonctions et rappels(callbacks) */

// Retourne le signe d'un entier (-1 négatif, +1 positif, 0 zéro)
static inline int8_t sgn(int val) {
  if (val <  0) return -1;
  if (val == 0) return 0;
  return 1;
}

void timerCallback(){
  /* Rappel du chronometre */
  should_send_ = true;          // Indique qu'on est prêt à mettre à jour et transmettre
}

void analyseMessage(JsonVariant msg){
  /* Fonction d'analyse du message recu */
  JsonVariant parse_msg;

  // Determiner si le message est un succes
  if (!msg.success()) {
    // Condition d'erreur : On ignore.
    return;
  }
  
  /*Si il y a commande de lecture
  en continue*/
  parse_msg =  msg["read"];
  String buff_str = msg["read"];
  if(parse_msg.success()){
    if (buff_str.equals("true")){
      state_transmit_ = true;
    }
    if (buff_str.equals("false")){
      state_transmit_ = false;
    }
  }
  
  /*Si il y a commande de changement
  de vitesse desiree*/
  parse_msg =  msg["set_des_vel"];
  if (parse_msg.success()) {
    des_vel_ = msg["set_des_vel"];
  }

    /*Si il y a commande de changement
  de de parametres PID*/
  parse_msg = msg["set_PID"];
  if (parse_msg.success()) {
      K_P = msg["set_PID"][0];
      K_I = msg["set_PID"][1];
      K_D = msg["set_PID"][2];
  }
  
  
}

void serialEvent(){
  /* Rappel lors de reception sur port serie */
  StaticJsonBuffer<500> json_buffer_in;
  JsonObject& root = json_buffer_in.parseObject(Serial);
  pi_msg_ = root;
  analyseMessage(pi_msg_);

}


void sendStateData(){
  /* Fonction pour envoie de l'etat */
  state_msg_.printTo(Serial); // Met le message en attente dans le port serie
  Serial.println();// Envoie le message
}

void runPID(){
  
  float new_cmd = 0.0;
  /* Fonction du controlleur de vitesse */
  
  /* La sortie du PID doit être inscrite dans la variable "new_cmd".
     Cette variable est ensuite filtrée pour éviter des sauts de commandes lors
     de changements de signes.
     En effet, il faut envoyer au moins une commande nulle (0,0) aux moteurs
     avant de changer de direction.
     C'est le rôle du code qui suit dans la fonction, et vous pouvez le laisser
     intact.
     
  */
  
  // Pour s'assurer de passer par zero si changement de signe
  if (sgn(new_cmd)+sgn(motor1_pwm_)==0){
     s3gro.ControleMoteurs(0,0);
  }

  // Si reinitialisation des moteurs
  if (des_vel_ == 0){
    motor1_pwm_ = 0;
    motor2_pwm_ = 0;
    err_I_ = 0;
    last_err_ = 0;
  }
  else{
    // Sinon envoie de la commande calculée au moteur 1
    motor1_pwm_ = (int)new_cmd;
    motor2_pwm_ = 0;
  }

  s3gro.ControleMoteurs(motor1_pwm_, motor2_pwm_);

}

void updateState(){

    // Temps depuis le démarrage:
    t_ += DT;
    
    // Lecture des pulses d'encodeurs
    motor1_enc_count_ = s3gro.lireEncodeur(1); 
    motor2_enc_count_ = s3gro.lireEncodeur(2);
    
    cur_vel_ = ENC_TO_VEL * (motor1_enc_count_);
    cur_pos_ += cur_vel_ * DT;  // Intégrateur simple de la position.
    
    s3gro.clearEncodeurCount();

    state_msg_["ts"]      = t_;
    state_msg_["enc_1"]   = motor1_enc_count_;
    state_msg_["enc_2"]   = motor2_enc_count_;
    state_msg_["des_vel"] = des_vel_;

    // TODO: Variables d'états manquantes: position, vitesse, commande.
    
    
    sendStateData();
    
    should_send_ = false;
}


void setup()
{
  Serial.begin(BAUD); // Initialisation de la communication serielle 
  while (!Serial) continue;

  s3gro.init();

  timer.setInterval(UPDATE_PERIOD_MS, timerCallback);// Initialisation du timer
  
  state_transmit_ = false; // met à true pour pas attendre la commande "READ en continue" du PI si non connecté// false;
  should_send_    = false;

  delay(1000);
    
}

void loop() {

  /* Fonction de la boucle principale*/
  if(should_send_ == true && state_transmit_ == true){
    updateState();
    runPID();
  }

  timer.run();

}

