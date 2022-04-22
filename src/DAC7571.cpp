/**************************************************************************/
/*!
    @file     DAC7571.cpp
    @author   JASON JOHNSTON
	
    
	Driver for the Texas Instrument DAC5571, DAC6571, DAC7571 DAC
	The DAC5571 is a 8 Bit Rail to Rail DAC
	The DAC6571 is a 10 Bit Rail to Rail DAC
	The DAC7571 is a 12 Bit Rail to Rail DAC
    
	Please Note This was orignaly dervied from the libraries for the ADS1015 created by Adafruit
	
    @section  HISTORY
    
	v1.0 - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
#include <Math.h>

#ifndef DAC7571_h
	#define DAC7571_h
		#include "DAC7571.h"
#endif		

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint16_t value) {
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)(value>>8));
  i2cwrite((uint8_t)value);
  Wire.endTransmission();
}
	
/**************************************************************************/
/*!
    @brief  Instantiates a new DAC5571 class w/appropriate properties
*/
/**************************************************************************/
DAC5571::DAC5571(uint8_t i2cAddress) 
{
   m_i2cAddress = i2cAddress;
   m_bitshift = 4;
}
/**************************************************************************/
/*!
    @brief  Instantiates a new DAC6571 class w/appropriate properties
*/
/**************************************************************************/
DAC6571::DAC6571(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_bitshift = 2;
}
/**************************************************************************/
/*!
    @brief  Instantiates a new DAC7571 class w/appropriate properties
*/
/**************************************************************************/
DAC7571::DAC7571(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_bitshift = 0; 
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void DAC5571::begin() {
  Wire.begin();
}

/**************************************************************************/
/*!
    @brief  Gets The Data From the ADC
*/
/**************************************************************************/
void DAC5571::writedac(float voltage, float Vdd)  //Input the desired voltage and the Voltage feeding the IC
{
	float bitvalue; //This is the total number of bits avaiable 8 Bit = 256, 10 Bit = 1024, 12 Bit = 4096  This is a float to allow calculations later easier
	uint16_t data_i;
	uint16_t data_config;
	//Check to see if requested voltage is greater than Vdd and if it is set the voltage to VDD
	if (voltage > Vdd)
	{
		voltage = Vdd;
	}
	//Determine the number of total bits based on the Chip being used
	if (m_bitshift = 0)  //DAC7571
	{
		bitvalue = 4096.0; //value set to float to allow for easier math below
	}
	else if (m_bitshift = 2)//DAC6571
	{
		bitvalue = 1024.0;
	}
	else if (m_bitshift = 4)//DAC7571
	{
		bitvalue = 256.0;
	}
	//Calculate the output number coresponding to the requested voltage
  data_i = round(voltage/(Vdd/bitvalue));
  /*Set the value to be send to the DAC
	Configuration Requred by the Dacs is as Follows
	
	For DAC5571
	
	Byte 1
	MSB		6		5		4		3		2		1		LSB
	0		0		PD1		PD2		D7		D6		D5		D4
	
	Byte 2
	MSB		6		5		4		3		2		1		LSB
	D3		D2		D1		D0		X		X		X		X
	
	For DAC6571
	
	Byte 1
	MSB		6		5		4		3		2		1		LSB
	0		0		PD1		PD2		D9		D8		D7		D6
	
	Byte 2
	MSB		6		5		4		3		2		1		LSB
	D5		D4		D3		D2		D1		D0		X		X
  
	For DAC6571
	
	Byte 1
	MSB		6		5		4		3		2		1		LSB
	0		0		PD1		PD2		D11		D10		D9		D8
	
	Byte 2
	MSB		6		5		4		3		2		1		LSB
	D7		D6		D5		D4		D3		D2		D1		D0
  
  */
  data_config =  REG_CONFIG_OP_NORMAL |  //Normal Operation Mode
                 data_i<<m_bitshift;	//Shift Vaue based on which dac is being used used
  writeRegister(m_i2cAddress,data_config); //Write Value to DAC

  return;
}




