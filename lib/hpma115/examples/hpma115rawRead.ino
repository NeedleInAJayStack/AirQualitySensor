// Prints the read PM2.5 and PM10 values

bool dataAvailable;
char dataBuf[32];
u_int16_t pm25;
u_int16_t pm10;

void setup() {
  Serial.begin(9600);

  // Setup HPMA115
  dataAvailable = false;
  Serial1.begin(9600);
}

// when serial data arrives, process it.
void serialEvent1() {
  dataAvailable = true;
}

void loop()
{
  if(dataAvailable) {
    memset(dataBuf,0,32); // Clears dataBuf
    dataAvailable = false;

    // Verify that the first two bits are the starting bits: 0x42, 0x4d
    // If not, just return and try again on a different event.
    dataBuf[0] = Serial1.read();
    if(dataBuf[0] != 0x42) return;
    dataBuf[1] = Serial1.read();
    if(dataBuf[1] != 0x4d) return;

    // If we make it this far, we have new data to retrieve
    Serial1.readBytes(dataBuf+2, 30);

    // Next, check the checksum
    uint16_t calc_checksum = 0;
    for(int i = 0; i < 30; i++) { // The checksum is computed by summing bytes 0 to 30
      calc_checksum += dataBuf[i];
    }
    uint16_t data_checksum = (dataBuf[30] << 8) + dataBuf[31];
    if(calc_checksum != data_checksum) {
      Serial.println("Checksum != Computed checksum");
      return;
    }

    // Finally, read the values
    pm25 = (dataBuf[6] << 8) + dataBuf[7];
    pm10 = (dataBuf[8] << 8) + dataBuf[9];

    // Print the results
    Serial.print("PM2.5: "); Serial.println(pm25);
    Serial.print("PM10: "); Serial.println(pm10);
    Serial.println("---");
  }
}