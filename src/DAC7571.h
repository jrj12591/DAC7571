/**************************************************************************/
/*!
	@file     DAC7571.h
    @author   JASON JOHNSTON
	
    
	Driver for the Texas Instrument DAC5571, DAC6571, DAC7571 DAC
	The DAC5571 is a 8 Bit Rail to Rail DAC
	The DAC6571 is a 10 Bit Rail to Rail DAC
	The DAC7571 is a 12 Bit Rail to Rail DAC
    
	Please Note This was orignaly dervied from the libraries for the ADS1015 created by Adafruit
	
    @section  HISTORY
    
	v1.0 - First release

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>


/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
	const uint8_t ADDRESS_0 = 0x4C;	//A0 = GND
	const uint8_t ADDRESS_1 = 0x4D;	// A1 = VCC
/*=========================================================================*/

/*=========================================================================
    CONFIG REGISTER
    -----------------------------------------------------------------------*/
	const uint16_t REG_CONFIG_OP_NORMAL = 0x0000;	//Normal Operation
	const uint16_t REG_CONFIG_OP_1KGND = 0x1000;	//1K to AGND PWD
	const uint16_t REG_CONFIG_OP_100KGND = 0x2000;	//100K to AGND, PWD
	const uint16_t REG_CONFIG_OP_HIIMP = 0x3000;	//High Impedance, PWD 
/*=========================================================================*/




//Define the DAC557 Class
class DAC5571
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress; // Declare address veriable
   uint8_t m_bitshift;	// Declare bitshift veriable

 public:
  DAC5571(uint8_t i2cAddress = ADDRESS_0);
  void begin(void);
  void writedac(float voltage, float Vdd);
 private:
};


//Define the DAC6571 Class using the DAC5571 class as the base.

class DAC6571: public DAC5571
{
 public:
	DAC6571(uint8_t i2cAddress = ADDRESS_0);
 private:
};
//Define the DAC7571 Class using the DAC5571 class as the base.
class DAC7571: public DAC5571
{
 public:
	DAC7571(uint8_t i2cAddress = ADDRESS_0);
 private:
};
