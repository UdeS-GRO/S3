/**************************************************************************
 *                                                                         *
 * DAC2629					                                           *
 *                                                                         *
 ***************************************************************************
 *                                                                         * 
 *                                                                         *
 ***************************************************************************/
#include "Arduino.h"

#ifndef DAC2629_h
#define DAC2629_h

/* -- DAC2629 address --*/
#define DAC2629_ADDR 0x72  // DAC2629 address 

/* ------- Register names ------- */
#define DAC2629_COMMAND_DAC_A 0x30
#define DAC2629_COMMAND_DAC_B 0x31
#define DAC2629_COMMAND_DAC_C 0x32
#define DAC2629_COMMAND_DAC_D 0x33


#define DAC2629_OK    1 // no error
#define DAC2629_NO_ERROR   0 // initial state

//#define DAC2629_DELAY  70    // 70ms
#define	ADJUST	.01	// Pour ajuster précision, manque .01 volt


class DAC2629
{
public:
  bool status;           // set when error occurs 
                         // see error code for details
  byte error_code;       // Initial state

  DAC2629();
  void DAC_out(unsigned int convertisseur, double volt);
  
 
};

#endif
