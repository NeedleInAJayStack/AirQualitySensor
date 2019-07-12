// This simply will return the values that are read from the device connected to the serial1 pins
//
// According to the HPMA datasheet, the first two bits provided are: 0x42,0x46
// In decimal, these are: 66,77
// Which when converted to string using ASCII encoding is: B,M
//
// So the serial output of this is expected to be "BM"
// 

String readString;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
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