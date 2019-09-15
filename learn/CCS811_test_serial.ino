// Prints the complete Serial buffer from the CCS811, showing the integer value of each byte.
// You must comment out the "private" section of Adafruit_CCS811 to access the read method.


#include "Adafruit_CCS811.h"


static Adafruit_CCS811 ccs811 = Adafruit_CCS811();

bool dataAvailable;
char dataBuf[32];

void setup() {
  Serial.begin(9600);

  // Setup CCS811
  if(!ccs811.begin(CCS811_ADDRESS)){
    Serial.println("Error setting up CCS811;");
    while(1);
  }

  // Try setting the drive mode to 10sec to see if it helps with readings
  ccs811.setDriveMode(CCS811_DRIVE_MODE_10SEC);
}

void loop()
{
  if(ccs811.available()){

    Serial.println("---");
    Serial.println("Data from CCS811:");

		uint8_t buf[8];

		//ccs811.read(CCS811_ALG_RESULT_DATA, buf, 8);
    uint8_t num = 8;
    uint8_t pos = 0;

    while(pos < num){

      uint8_t read_now = min((uint8_t)32, (uint8_t)(num - pos));
      Wire.beginTransmission(CCS811_ADDRESS);
      Wire.write(CCS811_ALG_RESULT_DATA + pos);
      Wire.endTransmission();
      Wire.requestFrom(CCS811_ADDRESS, read_now);

      for(int i=0; i<read_now; i++){
        uint8_t val = Wire.read();
        Serial.print(i); Serial.print(": "); Serial.println(val); // Print the buffer integer
        buf[pos] = val;
        pos++;
      }
    }

    Serial.println("Interpreted:");
    uint16_t eCO2 = ((uint16_t)buf[0] << 8) | ((uint16_t)buf[1]);
    Serial.print("eCO2"); Serial.print(": "); Serial.println(eCO2);

		uint16_t TVOC = ((uint16_t)buf[2] << 8) | ((uint16_t)buf[3]);
    Serial.print("TVOC"); Serial.print(": "); Serial.println(TVOC);

    uint8_t error = buf[5];
    Serial.print("error"); Serial.print(": "); Serial.println(error);

    uint8_t current = (uint8_t)buf[6] >> 2;
    Serial.print("current"); Serial.print(": "); Serial.println(current);

    uint16_t voltage = (((uint16_t)buf[6] & 3) << 8) | ((uint16_t)buf[7]); //(((uint16_t)buf[6] << 8) | ((uint16_t)buf[7])) & 1023
    Serial.print("voltage"); Serial.print(": "); Serial.println(voltage);
	}
}

