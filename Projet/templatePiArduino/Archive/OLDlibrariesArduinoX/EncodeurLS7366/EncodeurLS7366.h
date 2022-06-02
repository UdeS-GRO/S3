/* Fonction de lecture des encodeurs
EncodeurLS7366

Marc Rousseau

*/

#include "Arduino.h"
#include <SPI.h>	//librairie Arduino

#ifndef EncodeurLS7366_h
#define EncodeurLS7366_h

/*
		LS7366 Breakout    -------------   Arduino
		-----------------                  -------
            MOSI   -------------------   MOSI (D51)
            MISO   -------------------   MISO (D50)
            SCK    -------------------   SCK (D52)
            SS1    -------------------   SS1 (D34)
            SS2    -------------------   SS2 (D35)
            GND    -------------------   GND
            VDD    -------------------   VCC (5.0V)
*/


// Slave Select pins for encoders 1 and 2
#define S1 34	// Encodeur 1
#define S2 35	// Encodeur 2
#define DFLAGM1 A14	// Encodeur 1 Flag
#define DFLAGM2 A15	// Encodeur 2 Flag


class EncodeurLS7366
{
  public:
    EncodeurLS7366();
    void encodeurInit();
	long readEncoder(int encoder);
	void clearEncoderCount();
      
};

#endif // EncodeurLS7366