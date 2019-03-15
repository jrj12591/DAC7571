#include <Wire.h>
#include <DAC7571.h>
DAC7571 dac;
const float Vdd = 5.0; //Set the voltage that the dac will run at
void setup() 
  {
    dac.begin();  //Initalize the DAC
  }
//Loop through Voltage from 0 to Vdd and back to 0 stepping at .01V incurements
void loop()
{
  for (int i = 0; i <= Vdd; i +=.01)
  {
    dac.writedac(i,Vdd);
  }
  for (int i = Vdd; i>= 0; i -= .01)
  {
    dac.writedac(i,Vdd);
  }
}
