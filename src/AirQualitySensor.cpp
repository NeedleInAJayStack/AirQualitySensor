/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"
// Example usage for Adafruit_SGP30 library.
// This library was modified/wrapped by SJB (https://github.com/dyadica)
// in order to work with Particle Photon & Core.

 #include "Particle.h"
 #include "Adafruit_SGP30.h"

 void setup();
void loop();
#line 8 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"
Adafruit_SGP30 sgp;

 void setup() {
   Serial.begin(9600);
   Serial.println("SGP30 test");

   if (! sgp.begin()){
     Serial.println("Sensor not found :(");
     while (1);
   }
   Serial.print("Found SGP30 serial #");
   Serial.print(sgp.serialnumber[0], HEX);
   Serial.print(sgp.serialnumber[1], HEX);
   Serial.println(sgp.serialnumber[2], HEX);

   // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
   // sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
 }

 int counter = 0;
 void loop() {
   if (! sgp.IAQmeasure()) {
     Serial.println("Measurement failed");
     return;
   }
   Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
   Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
   delay(1000);

   counter++;
   if (counter == 30) {
     counter = 0;

     uint16_t TVOC_base, eCO2_base;
     if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
       Serial.println("Failed to get baseline readings");
       return;
     }
     Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
     Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
   }
 }



// // See readme for wiring configuration

// #include <Adafruit_Sensor.h>
// #include "Adafruit_CCS811.h"
// #include "Adafruit_Si7021.h"
// #include "hpma115.h"
// #include "Adafruit_TSL2591.h"

// static Adafruit_Si7021 si7021 = Adafruit_Si7021();
// static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
// static HPMA115 hpma115 = HPMA115();
// static Adafruit_TSL2591 tsl2591 = Adafruit_TSL2591(2591);

// // Record last-read and update intervals
// long dataReadTime;
// int dataInterval = 1000;
// long ccs811EnvSetTime;
// int ccs811EnvInterval = 60000;

// bool hmpa115NewData;

// // Data variables
// double temperature;
// double humidity;
// int eco2;
// int tvoc;
// int pm25;
// int pm10;
// int light;

// // Limits
// int eco2ValidMin = 200;
// int eco2ValidMax = 8192;
// int tvocValidMin = 0;
// int tvocValidMax = 1187;



// void setup() {
//   Serial.begin(9600);

//   // Declare particle variables
//   Particle.variable("temperature", temperature);
//   Particle.variable("humidity", humidity);
//   Particle.variable("eco2", eco2);
//   Particle.variable("tvoc", tvoc);
//   Particle.variable("pm25", pm25);
//   Particle.variable("pm10", pm10);
//   Particle.variable("light", light);

//   // Setup SI7021
//   si7021.begin();
//   temperature = si7021.readTemperature();
//   humidity = si7021.readHumidity();

//   // Setup CCS811
//   if(!ccs811.begin()){
//     Serial.println("Error setting up CCS811;");
//     while(1);
//   }
//   // Wait for sensor to be available
//   while(!ccs811.available());
//   // Set environmental data on ccs811 using si7021 readings
//   ccs811.setEnvironmentalData(humidity, temperature);
  
//   // Setup TSL2591
//   tsl2591.begin();
//   tsl2591.setGain(TSL2591_GAIN_MED); // You can change this for different light situations
//   tsl2591.setTiming(TSL2591_INTEGRATIONTIME_300MS);

//   // Set time intervals
//   dataReadTime = millis();
//   ccs811EnvSetTime = millis();
// }

// // Process HPMA115 serial events
// void serialEvent1() {
//   int status = hpma115.readData();
//   if(status == 0) hmpa115NewData = true;
// }

// void loop() {
//   // Only read data on correct intervals
//   if(millis() - dataReadTime > dataInterval) {

//     // Read SI7021
//     temperature = si7021.readTemperature();
//     humidity = si7021.readHumidity();
//     Serial.print("Temperature: "); Serial.print(temperature, 2); Serial.println("C");
//     Serial.print("Humidity: "); Serial.print(humidity, 2); Serial.println("%RH");

//     // Read CCS811
//     if(ccs811.available()) {
//       uint8_t errorCode = ccs811.readData();
//       if(errorCode == 0) {
//         uint16_t eco2_temp = ccs811.geteCO2();
//         uint16_t tvoc_temp = ccs811.getTVOC();
        
//         // Check validity
//         if(eco2ValidMin <= eco2_temp && eco2_temp <= eco2ValidMax) {
//           eco2 = eco2_temp;
//           Serial.print("CO2: "); Serial.print(eco2); Serial.println("ppm");
//         }
//         else {
//           Serial.print("CO2 reading out of bounds: "); Serial.println(eco2_temp);
//         }
//         if(tvocValidMin <= tvoc_temp && tvoc_temp <= tvocValidMax) {
//           tvoc = tvoc_temp;
//           Serial.print("TVOC: "); Serial.print(tvoc); Serial.println("ppb");
//         }
//         else {
//           Serial.print("TVOC reading out of bounds: "); Serial.println(tvoc_temp);
//         }
//       }
//       else {
//         Serial.print("CCS811 error code: ");
//         Serial.println(errorCode);
//       }
//     }
//     else{
//       Serial.println("CCS811 Sensor Unavailable!");
//     }

//     // Read HPMA115
//     if(hmpa115NewData) {
//       pm25 = hpma115.getPM25();
//       pm10 = hpma115.getPM10();
//       hmpa115NewData = false;
//     }
//     Serial.print("PM2.5: "); Serial.print(pm25); Serial.println("microgram/m^3");
//     Serial.print("PM10: "); Serial.print(pm10); Serial.println("microgram/m^3");

//     // Read TSL2591. Record only visible light (infrared and fullspectrum are also available)
//     light = tsl2591.getLuminosity(TSL2591_VISIBLE);
//     Serial.print("Light: "); Serial.print(light); Serial.println("lux");

//     Serial.println("---");
//     dataReadTime = millis();


//     // Set CCS811 environmental data if we've reached the interval
//     if(millis() - ccs811EnvSetTime > ccs811EnvInterval) {
//       ccs811.setEnvironmentalData(humidity, temperature);
//       ccs811EnvSetTime = millis();
//       Serial.println("Environmental data set");
//     }
//   }
// }