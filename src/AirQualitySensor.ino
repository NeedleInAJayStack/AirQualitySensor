// See readme for wiring configuration

#include <Adafruit_Sensor.h>
#include "Adafruit_SGP30.h"
#include "Adafruit_Si7021.h"
#include "hpma115.h"
#include "Adafruit_TSL2591.h"

static Adafruit_Si7021 si7021 = Adafruit_Si7021();
static Adafruit_SGP30 sgp30 = Adafruit_SGP30();
static HPMA115 hpma115 = HPMA115();
static Adafruit_TSL2591 tsl2591 = Adafruit_TSL2591(2591);

// Record last-read and update intervals
long refreshTime;
const int refreshInterval = 1; // in seconds
bool hmpa115NewData;

// Data variables
double temperature;
double humidity;
int eco2;
int tvoc;
int pm25;
int pm10;
int light;

// Runtime modifiers
bool debugMessages = false;

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

  startupSensors();
  setRefreshTime();
}

void serialEvent1() {
  processHpma115Event();
}

void loop() {
  if(shouldRefreshData()) {
    refreshData();
    if(debugMessages) {
      printDebugMessage();
    }
    setRefreshTime();
  }
}

// HELPER METHODS

void startupSensors() {
  si7021.begin();

  if(!sgp30.begin()) {
    Serial.println("SGP30 sensor not found");
    while (1);
  }

  tsl2591.begin();
  tsl2591.setGain(TSL2591_GAIN_MED); // You can change this for different light situations
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void setRefreshTime() {
  refreshTime = Time.now() + refreshInterval;
}

void processHpma115Event() {
  int status = hpma115.readData();
  if(status == 0) {
    hmpa115NewData = true;
  }
}

bool shouldRefreshData() {
  return Time.now() > refreshTime;
}

void refreshData() {
  temperature = si7021.readTemperature();
  humidity = si7021.readHumidity();

  if(!sgp30.IAQmeasure()) {
    Serial.println("SGP30 measurement failed");
    return;
  }
  tvoc = sgp30.TVOC;
  eco2 = sgp30.eCO2;

  if(hmpa115NewData) {
    pm25 = hpma115.getPM25();
    pm10 = hpma115.getPM10();
    hmpa115NewData = false;
  }

  // Record only visible light (infrared and fullspectrum are also available)
  light = tsl2591.getLuminosity(TSL2591_VISIBLE);
}

void printDebugMessage() {
  Serial.print("Temperature: "); Serial.print(temperature, 2); Serial.println("C");
  Serial.print("Humidity: "); Serial.print(humidity, 2); Serial.println("%RH");
  Serial.print("TVOC: "); Serial.print(tvoc); Serial.println("ppb");
  Serial.print("eCO2: "); Serial.print(eco2); Serial.println("ppm");
  Serial.print("PM2.5: "); Serial.print(pm25); Serial.println("microgram/m^3");
  Serial.print("PM10: "); Serial.print(pm10); Serial.println("microgram/m^3");
  Serial.print("Light: "); Serial.print(light); Serial.println("lux");
  Serial.println("---");
}