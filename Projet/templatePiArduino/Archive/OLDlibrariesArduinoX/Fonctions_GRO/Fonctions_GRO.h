/* Fonctions pour GRO tests

Marc Rousseau

*/



#ifndef Fonctions_GRO_h
#define Fonctions_GRO_h

//#include "Arduino.h"
#include "Wire.h"   // librairie Arduino
#include "I2Cdev.h"   // librairie Grove_IMU_10DOF_v2.0-master
#include "MPU9250.h"   // librairie Grove_IMU_10DOF_v2.0-master
#include "EncodeurLS7366.h" // librairie EncodeurLS7366
#include "Adafruit_INA219.h" // librairie Adafruit_INA219
#include "DAC2629.h" // librairie convertisseur DAC LTC2629

//motor  define
#define PWM1_STEP 5  //M1
#define DIR1 30

#define PWM2_STEP 6   //M2
#define DIR2 31

#define LOWBAT 12
#define BUZZER 36   // pin de Buzzer

#define ENCVEX_INT 2  // utilisation possible de l'encodeur Vex sur le grove D2-D3 interrupt
#define ENCVEX_CNT 3




class Fonctions_GRO
{
  public:
    Fonctions_GRO();
    void init();
    
    // IMU
	  void lireAccel_Data(float *Axyz);
    void lireGyro_Data(float *Gxyz);
    void lireMag_Data(float *Mxyz);
    void lireCap(float *cap);
    void lireTemperature(float *temperature);

    // Drive MD13S
    void moteursInit();
    void ControleMoteurs(int pwm1,int pwm2); // commande moteur signée (fwd + 255 / rev - 255) 0 = Brake
    void ControleMoteur1(int pwm1); // commande moteur signée (fwd + 255 / rev - 255) 0 = Brake
    void ControleMoteur2(int pwm2); // commande moteur signée (fwd + 255 / rev - 255) 0 = Brake

    // Encodeurs LS7366
    long lireEncodeur(int enc);
    void clearEncodeurCount();

    // Capteur de courant INA219
    void lireCourant_mA(float *current_mA);
    void lireTensionBus(float *busvoltage);
    void lireTensionShunt(float *shuntvoltage);
    void lireTensionCharge(float *loadvoltage);

    // Buzzer
    void buzzerON();
    void buzzerOFF();

    // Electroaimant
    void electroAimantON(int pinElectroaimant);
    void electroAimantOFF(int pinElectroaimant);

    // Encodeur Vex (D2-D3)
    void lectureEncodeurVexActif();
    signed long lectureEncodeurVex();
    void razEncodeurVex();

    // CNA
    void CNA(unsigned int convertisseur, double volt);

       

    
};

#endif // Fonctions_GRO
