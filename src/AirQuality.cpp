/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/jay/dev/particle/AirQuality/src/AirQuality.ino"

// BELOW THIS LINE IS THE CCS811 TEST CODE

// #if defined(PARTICLE)
//  SYSTEM_THREAD(ENABLED)
// #endif

// #include "Adafruit_CCS811.h"

// Adafruit_CCS811 ccs;

// void setup() {
//   Serial.begin(9600);
  
//   Serial.println("CCS811 test");
  
//   if(!ccs.begin()){
//     Serial.println("Failed to start sensor! Please check your wiring.");
//     while(1);
//   }

//   //calibrate temperature sensor
//   while(!ccs.available());
//   float temp = ccs.calculateTemperature();
//   ccs.setTempOffset(temp - 25.0);
// }

// void loop() {
//   if(ccs.available()){
//     float temp = ccs.calculateTemperature();
//     if(!ccs.readData()){
//       Serial.print("CO2: ");
//       Serial.print(ccs.geteCO2());
//       Serial.print("ppm, TVOC: ");
//       Serial.print(ccs.getTVOC());
//       Serial.print("ppb   Temp:");
//       Serial.println(temp);
//     }
//     else{
//       Serial.println("ERROR!");
//       while(1);
//     }
//   }
//   else{
//     Serial.println("Sensor Unavailable!");
//   }
//   delay(500);
// }

// BELOW THIS LINE IS THE SI7021 TEST CODE

// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin (D1 on Photon/Electron)
// Connect SDA to I2C data pin  (D0 on Photon/Electron)


#include "Adafruit_Si7021.h"   // Use for Build IDE
// #include "Adafruit_Si7021.h"               // Use for local build

void setup();
void loop();
#line 61 "/home/jay/dev/particle/AirQuality/src/AirQuality.ino"
Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);
  Serial.println("Si7021 test");
  sensor.begin();
}

void loop() {
  sensor.reset();
  Serial.print("Humidity:    "); Serial.print(sensor.readHumidity(), 2);
  Serial.print("\tTemperature: "); Serial.println(sensor.readTemperature(), 2);
  delay(1000);
}


// BELOW THIS LINE IS THE MULTI-SENSOR CODE

// // This #include statement was automatically added by the Particle IDE.
// #include <Adafruit_CCS811.h>

// // This #include statement was automatically added by the Particle IDE.
// #include <Adafruit_Si7021.h>



// // Static objects
// static Adafruit_Si7021 si7021 = Adafruit_Si7021();
// static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
// //static HPMA115 hpma115 = HPMA115();


// double temperature;
// double humidity;
// double tvoc;
// double eco2;

// void setup() {
//   Serial.begin(9600);

//   // Declare particle variables
//   Particle.variable("temperature", temperature);
//   Particle.variable("humidity", humidity);
//   Particle.variable("tvoc", tvoc);
//   Particle.variable("eco2", eco2);

//   si7021.begin();

//   // Setup ccs811
//   if(!ccs811.begin()){
//     Serial.println("Failed to start sensor! Please check your wiring.");
//     while(1);
//   }
//   //calibrate temperature sensor
//   // while(!ccs811.available());
//   // float temp = ccs811.calculateTemperature();
//   // ccs811.setTempOffset(temp - 25.0);
// }

// void loop() {

//   Serial.print("\n");
//   Serial.println("Retrieving information from sensor:");

//   temperature = si7021.readTemperature();
//   humidity = si7021.readHumidity();
//   Serial.print("  Temperature: "); Serial.println(temperature, 2);
//   Serial.print("  Humidity: "); Serial.println(humidity, 2);


//   ccs811.readData();
//   tvoc = ccs811.getTVOC();
//   eco2 = ccs811.geteCO2();
//   Serial.print("  TVOC: "); Serial.println(tvoc, 2);
//   Serial.print("  eCO2: "); Serial.println(eco2, 2);

//   delay(5000);
// }