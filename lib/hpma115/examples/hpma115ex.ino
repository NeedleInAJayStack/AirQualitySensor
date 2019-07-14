// Uses the firmware to read the HPMA115 sensor.

#include "hpma115.h"

static HPMA115 hpma115 = HPMA115();

bool newData;
u_int16_t pm25;
u_int16_t pm10;

void setup() {
  Serial.begin(9600);
}

// when serial data arrives, process it.
void serialEvent1() {
  int status = hpma115.readData();
  if(status == 0) newData = true;
}

void loop() {
  if(newData) {
    // Get data
    pm25 = hpma115.getPM25();
    pm10 = hpma115.getPM10();

    newData = false;

    // Print the results
    Serial.print("PM2.5: "); Serial.println(pm25);
    Serial.print("PM10: "); Serial.println(pm10);
    Serial.println("---");
  }
}