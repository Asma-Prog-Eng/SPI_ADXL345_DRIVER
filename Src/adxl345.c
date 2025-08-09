
#include "stm32f4xx.h"

#include "ADxl345.h"

#include "SPI.h"

uint8_t received_address = 0x0;

void Delay_Ms(int n) ;

void adxl_init(void) {

	// enable spi gpio

	GPIO_init();

	// init spi

	spi_init();

	// read device id , should be 0xE5 to confirm that SPI communication is correct

	adxl_read_address(DEVICE_ID);


    // set device in standby mode

	 adxl_write(POWER_CTL_R, RESERT);

	// set range of DATA to +-4g


	adxl_write(DEVICE_FORMAT_R, FOUR_G );

	// set device in measurement mode

	adxl_write(POWER_CTL_R, SET_MEASURE_B);

}


void adxl_write(uint8_t address, uint8_t value) {

	uint8_t data[2] = {};

	// enable multi-byte, place address and data into buffer

	data[0] |= address;

	data[0] |= MULTI_BYTE_EN;

	data[1] = value;

	//pull cs line low to enable slave
	cs_enable();

	// transmit data and address
	spi1_transmit(data, 2);


	// pull cs line high to disable slave
	cs_disable();

}


void adxl_read_values(uint8_t address, uint8_t *data_rec ,uint32_t size){

	// enable multi-byte, read operation and place address into buffer

	address |= (uint8_t) MULTI_BYTE_EN ;

	address |= (uint8_t) READ_OPERATION;

	//pull cs line low to enable slave
	cs_enable();

	// transmit address
	spi1_transmit(&address, 1);
	spi1_receiver(data_rec,size);

	// pull cs line high to disable slave
	cs_disable();


}

void adxl_read_address(uint8_t address) {

	// Place read bit into address

	address |= READ_OPERATION;


	//pull cs line low to enable slave

	cs_enable();

	// transmit address

	spi1_transmit(&address, 1);

	spi1_receiver(&received_address,1);

	// pull cs line high to disable slave

	cs_disable();

}


