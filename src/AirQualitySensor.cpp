/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"

void setup();
void loop();
#line 2 "/home/jay/dev/particle/AirQualitySensor/src/AirQualitySensor.ino"
String readString;

void setup() {
  Serial.begin(9600);

  // Setup HPMA115
  Serial1.begin(9600);
  // Enable auto send
  Serial1.write(68);
  Serial1.write(01);
  Serial1.write(40);
  Serial1.write(57);
}

void loop()
{
  while (Serial1.available()) // While receiving characters over serial...
  {
    delay(3); // Necessary delay
    char value = Serial1.read(); // Read the byte integer value
    readString = readString + value + ","; // Add the character to the string
  }

  readString.trim();

  if (readString.length() > 0) // If a string has been read...
  {
    Serial.println("Received: " + readString); // Send the parsed string to Serial for debugging
    //parseCommand(readString); // Do something with the string...
    readString = ""; // Clear the string
  }
}


// // CCS811 Wiring
// //
// // Connect Vin to 3-5VDC
// // Connect GND to ground
// // Connect SCL to I2C clock pin
// // Connect SDA to I2C data pin
// // Connect WAKE to ground

// // SI7021 Wiring
// //
// // Connect Vin to 3-5VDC
// // Connect GND to ground
// // Connect SCL to I2C clock pin
// // Connect SDA to I2C data pin

// #include "Adafruit_CCS811.h"
// #include "Adafruit_Si7021.h"

// // Static objects
// static Adafruit_Si7021 si7021 = Adafruit_Si7021();
// static Adafruit_CCS811 ccs811 = Adafruit_CCS811();
// //static HPMA115 hpma115 = HPMA115();


// double temperature;
// double humidity;
// double eco2;
// double tvoc;
// uint32_t timeEnvSet;

// void setup() {
//   Serial.begin(9600);

//   // Declare particle variables
//   Particle.variable("temperature", temperature);
//   Particle.variable("humidity", humidity);
//   Particle.variable("eco2", eco2);
//   Particle.variable("tvoc", tvoc);

//   // Setup si7021
//   si7021.begin();
//   temperature = si7021.readTemperature();
//   humidity = si7021.readHumidity();

//   // Setup ccs811
//   if(!ccs811.begin()){
//     Serial.println("Failed to start ccs811 sensor! Please check your wiring.");
//     while(1);
//   }
//   // Wait for sensor to be available
//   while(!ccs811.available());
//   // Set environmental data on ccs811 using si7021 readings
//   ccs811.setEnvironmentalData(humidity, temperature);
//   timeEnvSet = Time.now();
// }

// void loop() {

//   // Read si7021
//   temperature = si7021.readTemperature();
//   humidity = si7021.readHumidity();

//   Serial.print("Temperature: ");
//   Serial.print(temperature, 2);
//   Serial.print("C, Humidity: ");
//   Serial.print(humidity, 2);
//   Serial.println("%RH");

//   // Read ccs811
//   if(ccs811.available()){

//     if(Time.now() - timeEnvSet > 60) { // Set environmental data every minute
//       ccs811.setEnvironmentalData(humidity, temperature);
//       timeEnvSet = Time.now();
//       Serial.println("Environmental data set");
//     }

//     uint8_t errorCode = ccs811.readData();
//     if(errorCode == 0) {
//       eco2 = ccs811.geteCO2();
//       tvoc = ccs811.getTVOC();

//       Serial.print("CO2: ");
//       Serial.print(eco2);
//       Serial.print("ppm, TVOC: ");
//       Serial.print(tvoc);
//       Serial.println("ppb");
//     }
//     else {
//       Serial.print("CCS811 error code: ");
//       Serial.println(errorCode);
//     }
//   }
//   else{
//     Serial.println("ccs811 Sensor Unavailable!");
//   }
  
//   Serial.println("---");
//   delay(1000); // CCS811 sensor only provides readings every 1sec.
// }