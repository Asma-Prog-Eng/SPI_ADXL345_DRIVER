/*
 * SPI.c
 *
 *  Created on: Jul 30, 2025
 *      Author: asmae
 */

#define      GPIOBEN            (1U << 1)

#define      GPIODEN            (1U << 3)

#define      SPI2EN             (1U << 14)

#define      GPIOB_MODER_2      (0x2 << 26)

#define      GPIOB_MODER_3      (0x2 << 28)

#define      GPIOB_MODER_4      (0x2 << 30)

#define      AF5_2              (0x5 << 20)

#define      AF5_3              (0x5 << 24)

#define      AF5_4              (0x5 << 28)

#define      CR1_SSM            (1U << 9)

#define      CR1_DFF            (1U << 11)

#define      CR1_SSI            (1U << 8)

#define      CR1_LSB           (1U << 7)

#define      CR1_MSTR          (1U << 2)

#define      CR1_SPE           (1U << 6)

#define      CR1_BR            (1U << 3)

#define     CR1_CPHA           (1U << 0)

#define     CR1_CPOL           (1U << 1)

#define     CR1_RXON           (1U << 10)

#define      SR_TXE            (1U << 1)

#define      SR_RXNE           (1U << 0)

#define      SR_BSY            (1U << 7)




#include "stm32f4xx.h"

#include "SPI.h"

void spi_init(void){


	// enable clock access for spi2

	 RCC->APB1ENR |= SPI2EN ;

	 SPI2->CR1 = 0;

	 // enable software slave management

     SPI2->CR1 |= CR1_SSM | CR1_SSI;

     // Select data frame to 8-bit

     SPI2->CR1 &= ~CR1_DFF  ;

     // set Baud rate to 1 Mhz

     SPI2->CR1|= CR1_BR ;

     // enable Mode 1

     SPI2->CR1 |= (CR1_CPHA | CR1_CPOL );

     // enable full duplex

     SPI2->CR1 &= ~CR1_RXON ;


     // configure LSBFIRST bit as MSB first

     SPI2->CR1 &= ~CR1_LSB;

	 // select the SPI in master mode

     SPI2->CR1 |= CR1_MSTR  ;

	 // enable the SPI peripheral

     SPI2->CR1 |= CR1_SPE;
}


void GPIO_init(void) {


	// enable clock access for port B and D

	RCC->AHB1ENR |=  GPIOBEN | GPIODEN ;

	// enable alternate mode for PB13, PB14 and P15

	GPIOB->MODER |= (GPIOB_MODER_2 | GPIOB_MODER_3 | GPIOB_MODER_4);

	// enable output mode for PD12

	GPIOD->MODER |= (1U << 24);

	GPIOD->MODER &= ~(1U << 25);

	// set alternate function to AF05 for PB13, PB14 and PB15

    GPIOB->AFR[1] |= (AF5_2 | AF5_3 | AF5_4);




}


void spi1_transmit(uint8_t *data, uint32_t size) {

	uint32_t i =0;

	volatile uint8_t temp;

	while (i < size) {
	//for (i = 0 ; i < size ; i++) {

		// wait till transmit buffer is empty

		while(!(SPI2->SR & SR_TXE)) {;}

		// write the data to the data register

		SPI2->DR = *(data+i);
		i++;

	}

	// wait till transmit buffer is empty
	while(!(SPI2->SR & SR_TXE)) {;}

    //wait untill SPI bus is free
    while((SPI2->SR & SR_BSY)){;}

	// clear OVR flag

	temp = SPI2->DR;
	temp = SPI2->SR;

}

void spi1_receiver(uint8_t *data, uint32_t size) {

	uint32_t i = 0;

	while (size) {

		// send dummy data

		SPI2->DR = 0;

		// wait till receiver buffer is not empty

		while(!(SPI2->SR & SR_RXNE)) {;}

		*(data+i)= SPI2->DR;

        size--;

        i++;
	}


}


void cs_enable(void){

	 GPIOD->ODR &= ~(1U << 12);

}

void cs_disable(void){

	 GPIOD->ODR |= (1U << 12);

}



