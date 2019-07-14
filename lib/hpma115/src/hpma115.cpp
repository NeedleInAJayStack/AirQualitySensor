/*
 * Description: Honeywell HPMA115SO sensor w/ standard connector. See readme for more details
 * Author: Jay Herron
 * Date: 7/14/2019
 */

#include "hpma115.h"

HPMA115::HPMA115(void){
  // Set up serial
  Serial1.begin(HPMA115_BAUD);
}

/*
 * Reads the data from the Serial1 stream. Returns:
 * 
 * 0: Data processed succesfully
 * 1: Could not find start
 * 2: Not enough data available yet.
 * 2: Checksums don't agree
 */
int HPMA115::readData() {
  // Exit if we are not at the start, and cannot find it.
  if(!atStart) readToStart();
  if(!atStart) return 1;

  // Exit if we don't have enough data to read a full message.
  if(Serial1.available() < 30) return 2;

  // Read the data.
  Serial1.readBytes(dataBuf+2, 30);

  // Check the checksum
  uint16_t calc_checksum = 0;
  for(int i = 0; i < 30; i++) { // The checksum is computed by summing bytes 0 to 30
    calc_checksum += dataBuf[i];
  }
  uint16_t data_checksum = (dataBuf[30] << 8) + dataBuf[31];
  if(calc_checksum != data_checksum) {
    return 4;
  }

  // Read and save the values
  pm25 = (dataBuf[6] << 8) + dataBuf[7];
  pm10 = (dataBuf[8] << 8) + dataBuf[9];

  // Clean out the data buffer
  memset(dataBuf,0,32);

  // Verify that we are at the start on the next iteration in case we miss a message.
  atStart = false; 
  return 0;
}

/*
 * Reads the existing stream until there are no more available items or it matches the start sequence.
 * 
 * If the start is found, the 'atStart' variable is set to true, the Serial buffer will begin after the
 *  start sequence and the data buffer is cleared and filled with the start sequence.
 */
void HPMA115::readToStart(){
  int availableBytes = Serial1.available();
  if(availableBytes < 2) return; // Wait until we have at least 2 bytes to determine where we are in the stream

  // Find the start in the available bytes. Start is indicated by: 0x42, 0x4d
  bool foundStart = false;
  int index = 0;
  while(index < availableBytes && !foundStart){
    int val = Serial1.read();
    if(val == 0x42) {
      int secondVal = Serial1.read();
      if(secondVal == 0x4d) {
        foundStart = true;
      }
    }
    index = index + 1;
  }
  if(foundStart) {
    atStart = true;

    // Prepare data buffer by cleaning and filling in with start sequence
    dataBuf[0] = 0x42;
    dataBuf[1] = 0x4d;
  }
}

uint16_t HPMA115::getPM25() {
  return pm25;
}

uint16_t HPMA115::getPM10() {
  return pm10;
}