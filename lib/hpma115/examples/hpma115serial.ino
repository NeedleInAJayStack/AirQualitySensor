// Prints the complete Serial buffer from the HPMA115, showing the integer value of each byte.

bool dataAvailable;
char dataBuf[32];

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

    Serial.println("---");
    Serial.println("Data from HMPA");
    Serial1.readBytes(dataBuf, 32);
    for(int i = 0; i < 32; i += 1){
      u_int8_t val = dataBuf[i]; // Declare as integer so we can see it correctly
      Serial.print(i); Serial.print(": "); Serial.println(val); // Print the buffer integer
    }
  }
}