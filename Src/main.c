/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Asma Askri
 * @brief          : Main program body
 ******************************************************************************
 * Bare metal SPI Driver implementation to interface with ADXl345 accelerometer
 * Data axis are read for adxl345 and dislayed on debbuger mode
 * as well as the device ID
 ******************************************************************************
 **/
#include "stm32f4xx.h"

#include <stdint.h>

#include "adxl345.h"


// following variables are set as global for debugging purposes

uint8_t data_rec[6];

double xg = 0.0, yg =0.0 , zg = 0.0;

int16_t x, y, z;

extern uint8_t received_address;


int main(void)


{

	adxl_init();


   while(1) {


	   adxl_read_values(DATA_START_ADDR, data_rec,6);

	   x = (int16_t)((data_rec[1]<<8 )|data_rec[0]);

	   y = (int16_t) ((data_rec[3]<<8)|data_rec[2]);

	   z =  (int16_t) ((data_rec[5]<<8 )|data_rec[4]);

	   xg = (x * 0.0078 );

	   yg =  (y * 0.0078 );

	   zg =  (z * 0.0078 );

	   // simple delay for monitoring purposes

	   for (int i = 0; i < 525000; i++){};

	   }



}


