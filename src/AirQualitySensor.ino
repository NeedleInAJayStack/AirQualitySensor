// BELOW THIS LINE IS THE MULTI-SENSOR CODE - WORKING

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


// BELOW THIS LINE IS THE CCS811 TEST CODE - WORKING

// // Connect Vin to 3-5VDC
// // Connect GND to ground
// // Connect SCL to I2C clock pin (D1 on Photon/Electron)
// // Connect SDA to I2C data pin  (D0 on Photon/Electron)F
// // Connect WAKE to ground

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

//   // Wait for sensor to be available
//   while(!ccs.available());
//   // Calibrate temperature sensor
//   float temp = ccs.calculateTemperature();
//   ccs.setTempOffset(temp - 25.0);
// }

// void loop() {
//   if(ccs.available()){
//     float temp = ccs.calculateTemperature();
//     ccs.readData();

//     Serial.print("CO2: ");
//     Serial.print(ccs.geteCO2());
//     Serial.print("ppm, TVOC: ");
//     Serial.print(ccs.getTVOC());
//     Serial.print("ppb   Temp:");
//     Serial.println(temp);
//   }
//   else{
//     Serial.println("Sensor Unavailable!");
//   }
//   delay(1000); // Usually can't run faster than 1sec or else sensor becomes unavailable.
// }

// BELOW THIS LINE IS THE SI7021 TEST CODE - WORKING

// // Connect Vin to 3-5VDC
// // Connect GND to ground
// // Connect SCL to I2C clock pin
// // Connect SDA to I2C data pin


// #include "Adafruit_Si7021.h"   // Use for Build IDE
// // #include "Adafruit_Si7021.h"               // Use for local build

// Adafruit_Si7021 sensor = Adafruit_Si7021();

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Si7021 test");
//   sensor.begin();
// }

// void loop() {
//   Serial.print("Humidity:    "); Serial.print(sensor.readHumidity(), 2);
//   Serial.print("\tTemperature: "); Serial.println(sensor.readTemperature(), 2);
//   delay(1000);
// }