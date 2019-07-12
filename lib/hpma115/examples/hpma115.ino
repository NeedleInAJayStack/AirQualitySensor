
// ISSUES
// * Even when reading the whole buffer, I only ever get two bytes: B,M. It's interesting that I don't get more trailing commas...

String readString;
bool dataAvailable;
char dataBuf[32];

void setup() {
  Serial.begin(9600);

  // Setup HPMA115
  dataAvailable = false;
  Serial1.begin(9600);
  // Enable auto send
//   Serial1.write(68);
//   Serial1.write(01);
//   Serial1.write(40);
//   Serial1.write(57);
}

// when serial data arrives, process it.
void serialEvent1() {
  dataAvailable = true;
}

void loop()
{
  if(dataAvailable) {
    memset(dataBuf,0,32); // Clears dataBuf

    Serial1.readBytes(dataBuf, 32);
    for(int i = 0; i <= 32; i += 1){
      readString = readString + dataBuf[i] + ","; // Add the character to the string
    }

    Serial.println("Received: " + readString); // Send the parsed string to Serial for debugging
    //parseCommand(readString); // Do something with the string...
    readString = ""; // Clear the string
  }
}