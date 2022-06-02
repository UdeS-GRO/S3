/* Fonction de lecture des encodeurs
EncodeurLS7366

Marc Rousseau

*/


#include "EncodeurLS7366.h"



EncodeurLS7366::EncodeurLS7366(){ 
  
	
}

void EncodeurLS7366::encodeurInit()
{

  // Set slave selects as outputs
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  // Set Flag as inputs
  pinMode(DFLAGM1, INPUT);
  pinMode(DFLAGM2, INPUT);

  // Raise select pins
  // Communication begins when you drop the individual select signsl
  digitalWrite(S1,HIGH);
  digitalWrite(S2,HIGH);
  
  SPI.begin();

   delayMicroseconds(500);  // provides some breathing room between SPI conversations

  // Initialize encoder 2
  //    Clock division factor: 0
  //    Negative index input
  //    free-running count mode
  //    x4 quatrature count mode (four counts per quadrature cycle)
  // NOTE: For more information on commands, see datasheet
  digitalWrite(S2,LOW);        // Begin SPI conversation
  SPI.transfer(0x88);                       // Write to MDR0
  SPI.transfer(0x03);                       // Configure to 4 byte mode
  digitalWrite(S2,HIGH);       // Terminate SPI conversation 

  delayMicroseconds(500);  // provides some breathing room between SPI conversations

  // Initialize encoder 1
  //    Clock division factor: 0
  //    Negative index input
  //    free-running count mode
  //    x4 quatrature count mode (four counts per quadrature cycle)
  // NOTE: For more information on commands, see datasheet
  digitalWrite(S1,LOW);        // Begin SPI conversation
  SPI.transfer(0x88);                       // Write to MDR0
  //SPI.transfer(0x03);                       // Configure to 4 byte mode
  SPI.transfer(0x03);                       // Configure to x1
  digitalWrite(S1,HIGH);       // Terminate SPI conversation 

 

}


long EncodeurLS7366::readEncoder(int encoder)
{

  // Initialize temporary variables for SPI read
  unsigned int count_1, count_2, count_3, count_4;
  long count_value;  
  
  // Read encoder 1
  if (encoder == 1) {
    digitalWrite(S1,LOW);      // Begin SPI conversation
    SPI.transfer(0x60);                     // Request count
    count_1 = SPI.transfer(0x00);           // Read highest order byte
    count_2 = SPI.transfer(0x00);           
    count_3 = SPI.transfer(0x00);           
    count_4 = SPI.transfer(0x00);           // Read lowest order byte
    digitalWrite(S1,HIGH);     // Terminate SPI conversation 
  }
  
  // Read encoder 2
  else if (encoder == 2) {
    digitalWrite(S2,LOW);      // Begin SPI conversation
    SPI.transfer(0x60);                      // Request count
    count_1 = SPI.transfer(0x00);           // Read highest order byte
    count_2 = SPI.transfer(0x00);           
    count_3 = SPI.transfer(0x00);           
    count_4 = SPI.transfer(0x00);           // Read lowest order byte
    digitalWrite(S2,HIGH);     // Terminate SPI conversation 
  }
  
  // Calculate encoder count
  count_value = (count_1 << 8) + count_2;
  count_value = (count_value << 8) + count_3;
  count_value = (count_value << 8) + count_4;
  
  return count_value;
  
}

void EncodeurLS7366::clearEncoderCount()
{
	 // Set encoder2's data register to 0
  digitalWrite(S2,LOW);      // Begin SPI conversation  
  // Write to DTR
  SPI.transfer(0x98);    
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(S2,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // Set encoder2's current data register to center
  digitalWrite(S2,LOW);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(S2,HIGH);     // Terminate SPI conversation 



	 // Set encoder1's data register to 0
  digitalWrite(S1,LOW);      // Begin SPI conversation  
  // Write to DTR
  SPI.transfer(0x98);    
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(S1,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // Set encoder1's current data register to center
  digitalWrite(S1,LOW);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(S1,HIGH);     // Terminate SPI conversation   
  
 

}

