// CCS811 Wiring
//
// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin
// Connect SDA to I2C data pin
// Connect WAKE to ground
//
// SI7021 Wiring
//
// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin
// Connect SDA to I2C data pin
//
// HPMA Wiring
//
// Vcc (2) <-> USB
// TX (6) <-> RX
// RX (7) <-> TX
// GND (8) <-> GND

#include "Adafruit_CCS811.h"
#include "Adafruit_Si7021.h"
#include "hpma115.h"

// Static objects
static Adafruit_Si7021 si7021 = Adafruit_Si7021();
static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
static HPMA115 hpma115 = HPMA115();

// Record last-read and update intervals
long si7021ReadTime;
int si7021Interval = 1000;
long ccs811ReadTime;
int ccs811Interval = 1000;
long hpma115ReadTime;
int hpma115Interval = 1000;

// Time tracking for ccs811 environmental settings
long ccs811EnvSetTime;
int ccs811EnvInterval = 60000;

bool hmpa115NewData;

double temperature;
double humidity;
double eco2;
double tvoc;
double pm25;
double pm10;


void setup() {
  Serial.begin(9600);

  // Declare particle variables
  Particle.variable("temperature", temperature);
  Particle.variable("humidity", humidity);
  Particle.variable("eco2", eco2);
  Particle.variable("tvoc", tvoc);
  Particle.variable("pm25", pm25);
  Particle.variable("pm10", pm10);

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
  si7021ReadTime = millis();
  ccs811ReadTime = millis();
  ccs811EnvSetTime = millis();
}

// Process HPMA115 serial events
void serialEvent1() {
  int status = hpma115.readData();
  if(status == 0) hmpa115NewData = true;
}

void loop() {

  // Read si7021
  if(millis() - si7021ReadTime > si7021Interval) {
    temperature = si7021.readTemperature();
    humidity = si7021.readHumidity();
    si7021ReadTime = millis();

    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print("C, Humidity: ");
    Serial.print(humidity, 2);
    Serial.println("%RH");
  }

  // Read ccs811
  if(millis() - ccs811ReadTime > ccs811Interval){
    if(ccs811.available()) {
      if(millis() - ccs811EnvSetTime > ccs811EnvInterval) { // Set environmental data every minute
        ccs811.setEnvironmentalData(humidity, temperature);
        ccs811EnvSetTime = millis();
        Serial.println("Environmental data set");
      }

      uint8_t errorCode = ccs811.readData();
      if(errorCode == 0) {
        eco2 = ccs811.geteCO2();
        tvoc = ccs811.getTVOC();

        Serial.print("CO2: ");
        Serial.print(eco2);
        Serial.print("ppm, TVOC: ");
        Serial.print(tvoc);
        Serial.println("ppb");
      }
      else {
        Serial.print("CCS811 error code: ");
        Serial.println(errorCode);
      }
    }
    else{
      Serial.println("ccs811 Sensor Unavailable!");
    }
    ccs811ReadTime = millis();
  }

  // Read HPMA115
  if(millis() - hpma115ReadTime > hpma115Interval){
    if(hmpa115NewData) {
      pm25 = hpma115.getPM25();
      pm10 = hpma115.getPM10();
      hmpa115NewData = false;
    }

    Serial.print("PM2.5: ");
    Serial.print(pm25);
    Serial.print("microgram/m^3, PM10: ");
    Serial.print(pm10);
    Serial.println("microgram/m^3");

    hpma115ReadTime = millis();
  }
}