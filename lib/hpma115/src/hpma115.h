/*
 * Project Particle Squared
 * Description: Particle powered PM2.5 and air quality sensor
 * Author: Jared Wolff
 * Date: 2/26/2019
 * License: GNU GPLv3
 */

#define HPMA115_H

#include "application.h"

#define HPMA115_BAUD 9600

// Standard customer use protocol
#define HPMA115_HEAD                  0x68
#define HPMA115_READ_MEASUREMENT      0x04
#define HPMA115_START_MEASUREMENT     0x01
#define HPMA115_STOP_MEASUREMENT      0x02
#define HPMA115_SET_COEFF             0x08
#define HPMA115_READ_COEFF            0x10
#define HPMA115_START_AUTO_SEND_CMD   0x40
#define HPMA115_STOP_AUTO_SEND_CMD    0x20



#define HPMA115_SUCCESS        0
#define HPMA115_NO_DATA_AVAIL  2
#define HPMA115_READING_CNT    3

// typedef enum {
//   READY,
//   DATA_AVAILABLE,
//   DATA_PROCESS,
//   DATA_READ,
//   DISABLED
// } hpma115_state_t;

// typedef struct {
//   uint16_t pm25;
//   uint16_t pm10;
// } hpma115_data_t;

// typedef void (*hpma115_cb)(hpma115_data_t * p_data);

// typedef struct {
//   hpma115_cb callback;
//   uint8_t enable_pin;
// } hpma115_init_t;

class HPMA115 {
  public:
    HPMA115(void);
    int readData();
    int processData();
    uint16_t getPM25();
    uint16_t getPM10();
  protected:
    bool atStart = false;
    char dataBuf[32];
    u_int16_t pm25;
    u_int16_t pm10;
    void readToStart();
};