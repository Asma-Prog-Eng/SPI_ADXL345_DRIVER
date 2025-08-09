

#ifndef ADCXL345_H_
#define ADCXL345_H_

#include <stdint.h>

#include "SPI.h"

#define DEVICE_FORMAT_R        0x31
#define POWER_CTL_R            0x2D
#define DATA_START_ADDR        0x32
#define DATA_FORMAT_R          0x31
#define DEVICE_ID              0x00

#define FOUR_G                 0x01
#define RESERT                 0x00
#define SET_MEASURE_B          0x08
#define MULTI_BYTE_EN          0x40
#define READ_OPERATION         0x80

void adxl_init(void);


void adxl_read_values(uint8_t address, uint8_t *data_rec, uint32_t size );


void adxl_write(uint8_t address, uint8_t value);


void adxl_read_address(uint8_t address);

#endif /* ADCXL345_H_ */
