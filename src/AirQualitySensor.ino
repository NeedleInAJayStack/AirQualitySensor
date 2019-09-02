// CCS811 Wiring
//
// Vin <-> 3V3
// GND <-> GND
// SCL <-> I2C clock pin
// SDA <-> I2C data pin
// WAKE <-> GND
//
// SI7021 Wiring
//
// Vin <-> 3V3
// GND <-> GND
// SCL <-> I2C clock pin
// SDA <-> I2C data pin
//
// HPMA Wiring
//
// Vcc (2) <-> USB
// TX (6) <-> RX
// RX (7) <-> TX
// GND (8) <-> GND
//
// Photosensor
// Short pin <-> 3V3
// Long pin <-> A5, GND(through 220 Ohm resistor)

#include "Adafruit_CCS811.h"
#include "Adafruit_Si7021.h"
#include "hpma115.h"

static Adafruit_Si7021 si7021 = Adafruit_Si7021();
static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
static HPMA115 hpma115 = HPMA115();
static int photoPin = A5;

// Record last-read and update intervals
long dataReadTime;
int dataInterval = 1000;
long ccs811EnvSetTime;
int ccs811EnvInterval = 60000;

bool hmpa115NewData;

// Data variables
double temperature;
double humidity;
int eco2;
int tvoc;
int pm25;
int pm10;
int light;

// Limits
int eco2ValidMin = 200;
int eco2ValidMax = 8192;
int tvocValidMin = 0;
int tvocValidMax = 1187;



void setup() {
  Serial.begin(9600);

  // Declare particle variables
  Particle.variable("temperature", temperature);
  Particle.variable("humidity", humidity);
  Particle.variable("eco2", eco2);
  Particle.variable("tvoc", tvoc);
  Particle.variable("pm25", pm25);
  Particle.variable("pm10", pm10);
  Particle.variable("light", light);

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
  
  // Set time intervals
  dataReadTime = millis();
  ccs811EnvSetTime = millis();
}

// Process HPMA115 serial events
void serialEvent1() {
  int status = hpma115.readData();
  if(status == 0) hmpa115NewData = true;
}

void loop() {
  // Only read data on correct intervals
  if(millis() - dataReadTime > dataInterval) {
    
    // Read si7021
    temperature = si7021.readTemperature();
    humidity = si7021.readHumidity();
    Serial.print("Temperature: "); Serial.print(temperature, 2); Serial.println("C");
    Serial.print("Humidity: "); Serial.print(humidity, 2); Serial.println("%RH");

    // Read ccs811
    if(ccs811.available()) {
      if(millis() - ccs811EnvSetTime > ccs811EnvInterval) { // Set environmental data every minute
        ccs811.setEnvironmentalData(humidity, temperature);
        ccs811EnvSetTime = millis();
        Serial.println("Environmental data set");
      }

      uint8_t errorCode = ccs811.readData();
      if(errorCode == 0) {
        uint16_t eco2_temp = ccs811.geteCO2();
        uint16_t tvoc_temp = ccs811.getTVOC();
        
        // Check validity
        if(eco2ValidMin <= eco2_temp && eco2_temp <= eco2ValidMax) {
          eco2 = eco2_temp;
          Serial.print("CO2: "); Serial.print(eco2); Serial.println("ppm");
        }
        else {
          Serial.print("CO2 reading out of bounds: "); Serial.println(eco2_temp);
        }
        if(tvocValidMin <= tvoc_temp && tvoc_temp <= tvocValidMax) {
          tvoc = tvoc_temp;
          Serial.print("TVOC: "); Serial.print(tvoc); Serial.println("ppb");
        }
        else {
          Serial.print("TVOC reading out of bounds: "); Serial.println(tvoc_temp);
        }
      }
      else {
        Serial.print("CCS811 error code: ");
        Serial.println(errorCode);
      }
    }
    else{
      Serial.println("CCS811 Sensor Unavailable!");
    }

    // Read HPMA115
    if(hmpa115NewData) {
      pm25 = hpma115.getPM25();
      pm10 = hpma115.getPM10();
      hmpa115NewData = false;
    }
    Serial.print("PM2.5: "); Serial.print(pm25); Serial.println("microgram/m^3");
    Serial.print("PM10: "); Serial.print(pm10); Serial.println("microgram/m^3");

    // Read Photosensor
    light = analogRead(photoPin);
    Serial.print("Light: "); Serial.println(light);

    Serial.println("---");
    dataReadTime = millis();
  }
}