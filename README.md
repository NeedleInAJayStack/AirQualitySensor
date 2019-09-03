# Air Quality Sensor

This is a project by Jay Herron to create an indoor air quality sensor that contains the following components:

* SI7021: Temp and humidity
* CCS811: CO2 and VOC
* HPMA115: PM2.5 and PM10
* TSL2591: Ambient light

It was intended for the BuildingFit office as a cool prototype/conversation starter.

## Wiring

See each module's driver documentation for more information

### SI7021

* Vin <-> 3V3
* GND <-> GND
* SCL <-> I2C clock pin
* SDA <-> I2C data pin

### CCS811

* Vin <-> 3V3
* GND <-> GND
* SCL <-> I2C clock pin
* SDA <-> I2C data pin
* WAKE <-> GND

### HPMA115

* Vcc (2) <-> USB
* TX (6) <-> RX
* RX (7) <-> TX
* GND (8) <-> GND

### TSL2591

* Vin <-> 3V3
* GND <-> GND
* SCL <-> I2C clock pin
* SDA <-> I2C data pin