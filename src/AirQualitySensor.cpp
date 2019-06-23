/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"
// CCS811 Wiring
//
// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin
// Connect SDA to I2C data pin
// Connect WAKE to ground

// SI7021 Wiring
//
// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin
// Connect SDA to I2C data pin

#include "Adafruit_CCS811.h"
#include "Adafruit_Si7021.h"

// Static objects
void setup();
void loop();
#line 20 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"
static Adafruit_Si7021 si7021 = Adafruit_Si7021();
static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
//static HPMA115 hpma115 = HPMA115();


double temperature;
double humidity;
double eco2;
double tvoc;

void setup() {
  Serial.begin(9600);

  // Declare particle variables
  Particle.variable("temperature", temperature);
  Particle.variable("humidity", humidity);
  Particle.variable("eco2", eco2);
  Particle.variable("tvoc", tvoc);

  // Setup si7021
  si7021.begin();
  temperature = si7021.readTemperature();
  humidity = si7021.readHumidity();

  // Setup ccs811
  if(!ccs811.begin()){
    Serial.println("Failed to start ccs811 sensor! Please check your wiring.");
    while(1);
  }
  // Wait for sensor to be available
  while(!ccs811.available());
  // Set environmental data on ccs811 using si7021 readings
  ccs811.setEnvironmentalData(humidity, temperature);
}

void loop() {

  // Read si7021
  temperature = si7021.readTemperature();
  humidity = si7021.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print("C, Humidity: ");
  Serial.print(humidity, 2);
  Serial.println("%RH, ");

  // Read ccs811
  if(ccs811.available()){
    ccs811.readData();

    eco2 = ccs811.geteCO2();
    tvoc = ccs811.getTVOC();

    Serial.print("CO2: ");
    Serial.print(eco2);
    Serial.print("ppm, TVOC: ");
    Serial.print(tvoc);
    Serial.println("ppb");
  }
  else{
    Serial.println("ccs811 Sensor Unavailable!");
  }


  delay(1000); // Usually can't run faster than 1sec or else ccs811 sensor becomes unavailable.
}