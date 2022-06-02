/* Fonction de GRO tests
Marc Rousseau

*/


#include "Fonctions_GRO.h"


MPU9250 accelgyro;
I2Cdev   I2C_M;
EncodeurLS7366 encodeur;
Adafruit_INA219 ina219;
DAC2629 dac;

signed long count_value = 0;

Fonctions_GRO::Fonctions_GRO(){ 

}

void Fonctions_GRO::init() {

  pinMode(LOWBAT, INPUT); // vérification de l'indicateur de batterie faible
  if(!digitalRead(LOWBAT)){
  Serial.println(" init BATTERY OK    ");
  pinMode(BUZZER, OUTPUT); // config pin Buzzer en sortie
  buzzerOFF();
  
  Wire.begin(); // lib I2C
  accelgyro.initialize(); // initialise IMU
  moteursInit();  // initialise pour Drive MD13S
  encodeur.encodeurInit(); // initialise encodeurs LS7366
  encodeur.clearEncoderCount(); // clear encodeurs LS7366
  ina219.begin(); // initialise Capteur de courant INA219
  lectureEncodeurVexActif(); // active l'interrupt pour utiliser l'encodeur VEX sur D2-D3
    
  }
  else Serial.println(" init Low BATTERY     ");

}

/* ************** IMU ****************/

void Fonctions_GRO::lireAccel_Data(float *Axyz)
{
	int16_t ax, ay, az;
	
  accelgyro.getAcceleration(&ax, &ay, &az);
	//accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Axyz[0] = (double) ax / 16384;
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;

}

void Fonctions_GRO::lireGyro_Data(float *Gxyz)
{
    int16_t gx, gy, gz;
  
    accelgyro.getRotation(&gx, &gy, &gz);
  
    Gxyz[0] = (double) gx * 250 / 32768;
    Gxyz[1] = (double) gy * 250 / 32768;
    Gxyz[2] = (double) gz * 250 / 32768;
}

void Fonctions_GRO::lireMag_Data(float *Mxyz)
{
    int16_t mx, my, mz;
   uint8_t buffer_m[6];
    
    I2C_M.writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01); //enable the magnetometer
    delay(10);
    I2C_M.readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);

    mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0] ;
    my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2] ;
    mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4] ;

    Mxyz[0] = (double) mx * 1200 / 4096;
    Mxyz[1] = (double) my * 1200 / 4096;
    Mxyz[2] = (double) mz * 1200 / 4096;
}

void Fonctions_GRO::lireCap(float *cap)
{
  float Mxyz[3];
  float heading;
   
  lireMag_Data(Mxyz);
  
  heading = 180 * atan2(Mxyz[1], Mxyz[0]) / PI;
    if (heading < 0) heading += 360;
    
  *cap = heading;
}

void Fonctions_GRO::lireTemperature(float *temperature)
{ 
    int16_t temp;
    
    temp = accelgyro.getTemperature();
    *temperature = (double)temp/100;
  
}


/* ************** Moteurs DC ****************/

void Fonctions_GRO::moteursInit()
{
  pinMode(PWM1_STEP, OUTPUT);//
  pinMode(PWM2_STEP, OUTPUT);//
  pinMode(DIR1, OUTPUT);//
  pinMode(DIR2, OUTPUT);
  

// analogWrite(PWM1_STEP, pwm1>255? 255:pwm1);
// analogWrite(PWM1_STEP, pwm2>255? 255:pwm2);

}

void Fonctions_GRO::ControleMoteurs(int pwm1,int pwm2) {

    
    if (pwm1<0)
      {
         digitalWrite(DIR1, LOW);
         pwm1 =- pwm1;  //cchange to positive
      }
    else
      {
         digitalWrite(DIR1, HIGH);
      }
  
    if (pwm2<0)
      {
         digitalWrite(DIR2, LOW);
         pwm2 = -pwm2;
       }
    else
      {
         digitalWrite(DIR2, HIGH);
      }
  
  
    // Serial.print(pwm_l);  Serial.print("\t"); Serial.println(pwm_r);
      analogWrite(PWM1_STEP, pwm1>255? 255:pwm1);
      analogWrite(PWM2_STEP, pwm2>255? 255:pwm2);
  
}


void Fonctions_GRO::ControleMoteur1(int pwm1)
{
if (pwm1<0)
      {
         digitalWrite(DIR1, LOW);
         pwm1 =- pwm1;  //cchange to positive
      }
    else
      {
         digitalWrite(DIR1, HIGH);
      }

       analogWrite(PWM1_STEP, pwm1>255? 255:pwm1);
  
}

void Fonctions_GRO::ControleMoteur2(int pwm2)
{
  if (pwm2<0)
      {
         digitalWrite(DIR2, LOW);
         pwm2 = -pwm2;
       }
    else
      {
         digitalWrite(DIR2, HIGH);
      }
      
    analogWrite(PWM2_STEP, pwm2>255? 255:pwm2);
}

/* ************** Encodeurs ****************/

long Fonctions_GRO::lireEncodeur(int enc)
{
    long count_value; 
    count_value = encodeur.readEncoder(enc);
    return count_value;
  
}

void Fonctions_GRO::clearEncodeurCount()
{
    encodeur.clearEncoderCount();
}

/* ************** Courant ****************/

void Fonctions_GRO::lireCourant_mA(float *current_mA)
{

  *current_mA = ina219.getCurrent_mA();
  
}
 
void Fonctions_GRO::lireTensionBus(float *busvoltage)
{

  *busvoltage = ina219.getBusVoltage_V();
}

void Fonctions_GRO::lireTensionShunt(float *shuntvoltage)
{
  *shuntvoltage = ina219.getShuntVoltage_mV();
  
}

void Fonctions_GRO::lireTensionCharge(float *loadvoltage)
{
  *loadvoltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000);
  
}

 /* ************** Buzzer ****************/
 
void Fonctions_GRO::buzzerON()
{  
  digitalWrite(BUZZER,HIGH);
}
void Fonctions_GRO::buzzerOFF()
{
  digitalWrite(BUZZER,LOW); 
}

/* ************** Electroaimant ****************/

void Fonctions_GRO::electroAimantON(int pinElectroaimant)
{
  pinMode(pinElectroaimant, OUTPUT);
  digitalWrite(pinElectroaimant,HIGH);
  
}

void Fonctions_GRO::electroAimantOFF(int pinElectroaimant)
{
  pinMode(pinElectroaimant, OUTPUT);
  digitalWrite(pinElectroaimant,LOW);
  
  
}

/* ************** Encodeur Vex ****************/

void EncVex()    // Routine d'interruption de l'encodeur Vex
{
  if (!digitalRead(ENCVEX_CNT)){
   count_value += 1;
  }
  else{
    count_value -= 1;
  }  
   
}

void Fonctions_GRO::lectureEncodeurVexActif() // 90 pulses par tour
{
  pinMode(ENCVEX_INT, INPUT);//
  pinMode(ENCVEX_CNT, INPUT);//
  
 // attachInterrupt(0, EncVex,FALLING);
 attachInterrupt(ENCVEX_INT, EncVex,FALLING);
  
}

signed long Fonctions_GRO::lectureEncodeurVex()
{
return count_value;
  
}

void Fonctions_GRO::razEncodeurVex()
{

  count_value = 0;
}

/* ************** Convertisseur numérique à analogique ****************/

void Fonctions_GRO::CNA(unsigned int convertisseur, double volt)
{
  dac.DAC_out(convertisseur, volt);  
}


