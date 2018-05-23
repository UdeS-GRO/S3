/* Code permetant la caracterisation du chariot/pendule
 * Auteurs: Jean-Samuel Lauzon, 
 *          Jonathan Vincent
 *          
 * date:    8 avril 2018
*/

#include "SimpleTimer.h" // librairie de chronometres
#include "ArduinoJson.h" // librairie de syntaxe JSON
#include <Servo.h> //librairie Servo
#include <SPI.h> // librairie Communication SPI
#include "IRremote_GRO.h" // librairie Capteur InfraRouge
#include "IRremoteInt_GRO.h" // librairie Capteur InfraRouge
#include "LCD_LK162.h"  // afficheur LCD 16x2
#include "Fonctions_GRO.h" // Librairie de fonction GRO



/* Constantes */
#define BAUD            115200 // Frequence de transmission serielle
#define UPDATE_PERIODE  100  // Periode (ms) d'envoie d'etat general
#define CMD_MIN         -255 // Commande min (pour PID).
#define CMD_MAX         255 // Commande max (pour PID).

/* Variables globales */
Servo monServoA, monServoB;  // pour tester le contrôle de 2 servos testés sur D8-D9
Fonctions_GRO fonction; // fonctions supplémentaires

// IMU (accelerometre)
float Axyz[3];

// Encodeurs
signed long encoder1count = 0;
signed long encoder2count = 0;

// Capteurs de courant
float current_mA = 0;
float loadvoltage = 0;

// Electroaimant
int pinElectroaimant = 32;  // selection Grove possible ... D2, D8, D32

// Lectures Analogique
int potvex = 0;

// Servo
int servo_MoteurA_pin = 8; // selection Grove possible D2-D3, D8-D9, D32-D33
int servo_MoteurB_pin = 9; // selection Grove possible D2-D3, D8-D9, D32-D33

// Autres variables globales
bool    should_send_;       // Indique qu'on est prêt à transmettre l'état.
SimpleTimer updateTimer;    // objet chronometre
String commande;            // string 
bool state_transmit_;                 

// Variable pour impulsion
long dureePulse  = 0;  // Periode (ms) d'envoie d'etat general
long pulsePWM = 0;
bool startPulse = false;
bool timerRunning = false;

// objects pour envoie de Messages
StaticJsonBuffer<500> jsonBuffer;
JsonVariant pi_msg = jsonBuffer.createObject();
JsonObject& state_msg = jsonBuffer.createObject();
                                                                                                                                                                                                                                                                                                                                                                                                                

/* Fonctions et rappels(callbacks) generaux */
static inline int8_t sgn(int val) {
 if (val < 0) return -1;
 if (val==0) return 0;
 return 1;
}

void updateTimerCallback(){
  /* Rappel du chronometre */
  should_send_ = true;
}

void serialEvent(){
  /* Rappel lors de reception sur port serie */
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& msg = jsonBuffer.parseObject(Serial);
  JsonVariant parse_msg;

  // Determiner si le message est un succes
  if (!msg.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  
  /*Si il y a commande de lecture
  en continue*/
  parse_msg =  msg["pulse"];
  String buff_str = msg["pulse"];
  if(parse_msg.success()){
    if (buff_str.equals("true")){
      startPulse = true;
    }
  }
  
  /*Si il y a une commande de 
  changement de valeur de PWM*/
  parse_msg =  msg["set_PWM"];
  if (parse_msg.success()) {
    pulsePWM = msg["set_PWM"];
  }

  parse_msg =  msg["set_duration"];
  if (parse_msg.success()) {
    dureePulse = msg["set_duration"];
  }
}


void send_state_data(){
  /* Fonction pour envoie de l'etat */
  state_msg.printTo(Serial); // Met le message en attente dans le port serie
  Serial.println();// Envoie le message
}

void startMotorsPulse(){
  /* Fonction du controlleur de vitesse*/
    fonction.ControleMoteurs(pulsePWM,pulsePWM);
}
void pulseCallback(){
  /*Rappel du chronometre pour arreter les moteurs*/
  fonction.ControleMoteurs(0,0);
  timerRunning = false;
}

void updateState(){
  // lire accelerometre
  fonction.lireAccel_Data(Axyz);
  // Lecture des pulses d'encodeurs
  encoder1count = fonction.lireEncodeur(1); 
  encoder2count = fonction.lireEncodeur(2);
  fonction.clearEncodeurCount();

  // lectures du capteur de courant
  fonction.lireCourant_mA(&current_mA);
  fonction.lireTensionCharge(&loadvoltage);

  // Lecture Potentiomètre VEX sur A5
  potvex = analogRead(A5);
  
  // Mise a jour du JSON
  state_msg["accel_x"] = Axyz[0];
  state_msg["accel_y"] = Axyz[1];
  state_msg["accel_z"] = Axyz[2];
  state_msg["current"] = current_mA;
  state_msg["load_voltage"] = loadvoltage; 
  state_msg["pot_vex"] = potvex;
  send_state_data();
  should_send_ = false;
}

/* Fonction d'initialisation et boucle principale*/
void setup(){
  Serial.begin(BAUD); // Initialisation de la communication serielle 
  while (!Serial) continue;

  fonction.init();
  monServoA.attach(servo_MoteurA_pin);
  monServoB.attach(servo_MoteurB_pin);

  updateTimer.setInterval(UPDATE_PERIODE, updateTimerCallback);// Initialisation du timer periodique
  state_transmit_ = false;
  should_send_ == false;



}

void loop() {
  /* Fonction de la boucle principale*/
  if(should_send_ == true){
    updateState();
  }
  if(startPulse == true){
    startMotorsPulse();
    updateTimer.setTimeout(dureePulse, pulseCallback); //inititialisation du timer unique
    startPulse = false;
  }
  updateTimer.run();
}

