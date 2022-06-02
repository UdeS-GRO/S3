/**************************************************************************
 *                                                                         *
 * DAC2629 Driver				                                               *
 *                                                                         *
 ***************************************************************************
 *                                                                         * 
 *                                                                         *
 ***************************************************************************/

#include "DAC2629.h"
#include <Wire.h>


DAC2629::DAC2629() {
  status = DAC2629_OK;
  error_code = DAC2629_NO_ERROR;

 }


// Envoi sortie analogique au DAC A ou B
void DAC2629::DAC_out(unsigned int convertisseur, double volt) {

	unsigned int aout;
	unsigned int msb;
	unsigned int lsb;

	aout = (volt + ADJUST)*819;	// convertir volts en 12 bits 0-4095, 3.3v = 1241, 5v = 819
	msb = (aout & 0x0fff) >>4; // garde 12 bits et shift au msb
	lsb = (aout <<4); 	// mettre les 4 derniers bits à 0 au lsb
	

	Wire.beginTransmission(DAC2629_ADDR); // start transmission to device
	if(convertisseur == 1 ) Wire.write(DAC2629_COMMAND_DAC_A);             // send register address
	if(convertisseur == 2 ) Wire.write(DAC2629_COMMAND_DAC_B);             // send register address
	if(convertisseur == 3 ) Wire.write(DAC2629_COMMAND_DAC_C);             // send register address
	if(convertisseur == 4 ) Wire.write(DAC2629_COMMAND_DAC_D);             // send register address
	Wire.write(msb);                 // send MSB value to write
	Wire.write(lsb);                 // send LSB value to write
	Wire.endTransmission();         // end transmission
  
}




