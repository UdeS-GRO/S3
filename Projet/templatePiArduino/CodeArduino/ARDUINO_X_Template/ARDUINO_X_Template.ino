
/* Fonctions de départ pour le shield Arduino_X */ 


#include "SimpleTimer.h" // librairie de chronometres
#include "ArduinoJson.h" // librairie de syntaxe JSON
#include "Fonctions_GRO.h"
#include <SPI.h> // librairie Communication SPI


/* Constantes */
#define BAUD            115200 // Frequence de transmission serielle
#define UPDATE_PERIODE_GEN  100  // Periode (ms) d'envoie d'etat general

Fonctions_GRO fonction; // fonctions supplémentaires

// Moteurs
int pwm1 = 0;
int pwm2 = 0;

// Encodeurs
signed long encoder1count = 0;
signed long encoder2count = 0;

// Electroaimant
int pinElectroaimant = 32;  // selection Grove possible ... D2, D8, D32

// Lectures Analogique
int potVex = 0;

// Lecture encodeur Vex
signed long encodervex = 0;  // selection Grove possible ... D2-D3 interrupt

// Autres variables globales

float   des_vel_ = 0.0;     // la consigne en vitesse.
bool    should_send_;       // Indique qu'on est prêt à transmettre l'état.
SimpleTimer timer;          // objet pour chronometre
bool state_transmit_; 
bool state_electroaimant_;   

// Message objects
StaticJsonBuffer<500> jsonBuffer;
JsonVariant pi_msg = jsonBuffer.createObject();
JsonObject& state_msg = jsonBuffer.createObject();


/* Fonctions et rappels(callbacks) generaux */

void timerCallback(){
  /* Rappel du chronometre */
  should_send_ = true;
}

void analyseMessage(JsonVariant msg){
  /* Fonction d'analyse du message recu */
  JsonVariant parse_msg;

  // Determiner si le message est un succes
  if (!msg.success()) {
//    Serial.println("parseObject() failed");
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

  /*Si il y a commande d'Action sur l'aimant */
  parse_msg =  msg["aimant"];
  String buff_str1 = msg["aimant"];
  if(parse_msg.success()){
    if (buff_str1.equals("true")){
      state_electroaimant_ = true;
    }
    if (buff_str1.equals("false")){
      state_electroaimant_ = false;
    }
  }
  
  /*Si il y a commande de changement
  de vitesse desiree*/
  parse_msg =  msg["set_des_vel"];
  if (parse_msg.success()) {
    des_vel_ = msg["set_des_vel"];
  }
  
  
}

void serialEvent(){
  /* Rappel lors de reception sur port serie */
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Serial);
  pi_msg = root;
}


void send_state_data(){
  /* Fonction pour envoie de l'etat */
  state_msg.printTo(Serial); // Met le message en attente dans le port serie
  Serial.println();// Envoie le message
}



void run_Sequence(){
  
  pwm1 = des_vel_;
  pwm2 = des_vel_;

  fonction.ControleMoteurs(pwm1,pwm2);

  if(state_electroaimant_) fonction.electroAimantON(pinElectroaimant);
  else fonction.electroAimantOFF(pinElectroaimant);

  }


void updateState(){

    // Lecture Potentiomètre VEX sur A5
   potVex = analogRead(A5);

    // Lecture des pulses d'encodeurs
    encoder1count = fonction.lireEncodeur(1); 
    encoder2count = fonction.lireEncodeur(2);
  
    // Lecture encodeur Vex (D2-D3)
    encodervex = fonction.lectureEncodeurVex();
    if(encodervex > 600) fonction.razEncodeurVex(); // exemple de remise à 0
   // Serial.print(" Encodeur Vex =  "); Serial.println(encodervex); 
 
    state_msg["enc_1"] = encoder1count;
    state_msg["enc_2"] = encoder2count;
    state_msg["pot_vex"] = potVex;
    state_msg["encodeur_vex"] = encodervex;
    state_msg["des_vel"] = des_vel_;
    state_msg["etat_electroaimant"] = state_electroaimant_;
    
    send_state_data();
    
    should_send_ = false;
}


void setup()
{
    Serial.begin(BAUD); // Initialisation de la communication serielle 
  while (!Serial) continue;

   fonction.init();

    timer.setInterval(UPDATE_PERIODE_GEN, timerCallback);// Initialisation du timer
    state_transmit_ = false; // met à true pour pas attendre la commande "READ en continue" du PI si non connecté// false;
    should_send_ == false;

    delay(1000);
    
}

void loop() {

/* Fonction de la boucle principale*/
  if(should_send_ == true && state_transmit_ == true){
    updateState();
    run_Sequence();
  }

  timer.run();
  analyseMessage(pi_msg);

}


