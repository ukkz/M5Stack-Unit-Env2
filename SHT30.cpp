#include "SHT30.h"

SHT30::SHT30(){}

void SHT30::read(float* temp_c, float* temp_f, float* humi)
{
  unsigned int data[6];
  // Start I2C Transmission
  Wire.beginTransmission(ADDR);
  // Send measurement command
  Wire.write(0x2C);
  Wire.write(0x06);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(500);

  // Request 6 bytes of data
  Wire.requestFrom(ADDR, 6);

  // Read 6 bytes of data
  // cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  *temp_c = (float)((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  *temp_f = (*temp_c * 1.8) + 32.0;
  *humi = (float)((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
}

float SHT30::readTemperature(int type)
{
	float temp_c, temp_f, h;
  read(&temp_c, &temp_f, &h);
	switch(type) {
		case CELSIUS:
			return temp_c;
			break;
		case FAHRENHEIT:
			return temp_f;
			break;
		case KELVIN:
      return (temp_c + 273.15);
			break;
    default:
      return 0.0;
	};
}

float SHT30::readHumidity()
{
	float temp_c, temp_f, h;
  read(&temp_c, &temp_f, &h);
  return h;
}
