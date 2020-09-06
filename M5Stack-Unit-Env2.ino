/*
    note: need add library Adafruit_BMP280 from library manage
*/

#include <M5Stack.h>
#include "SHT30.h"
#include <Wire.h> //The DHT12 uses I2C comunication.
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

SHT30 sht30;
Adafruit_BMP280 bme;

void setup() {
    M5.begin();
    M5.Power.begin();
    Wire.begin();

    M5.Lcd.setBrightness(10);

    Serial.println(F("ENV II Unit(SHT30 and BMP280) test..."));

    while (!bme.begin(0x76)){  
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
    }
    M5.Lcd.clear(BLACK);
    M5.Lcd.println("ENV Unit test...");
}

void loop() {
 
    float tmp = sht30.readTemperature();
    float hum = sht30.readHumidity();
    float pressure = bme.readPressure();
    Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  Pressure: %0.2fPa\r\n", tmp, hum, pressure);

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n", tmp, hum, pressure);

    delay(100);
}
