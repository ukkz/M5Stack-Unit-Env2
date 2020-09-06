#ifndef SHT30_h 
#define SHT30_h 
#include "Arduino.h"
#include "Wire.h"

#define ADDR        0x44
#define CELSIUS		  1
#define KELVIN		  2
#define FAHRENHEIT	3

class SHT30
{
	public:
		SHT30();
		float readTemperature(int type = CELSIUS);
		float readHumidity();
	private:
		void read(float* temp_c, float* temp_f, float* humi);
};

#endif
