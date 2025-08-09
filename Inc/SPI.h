
#ifndef SPI_H_
#define SPI_H_

void spi_init(void);

void GPIO_init(void);

void spi1_transmit(uint8_t *data, uint32_t size);

void spi1_receiver(uint8_t *data, uint32_t size);

void cs_enable(void);

void cs_disable(void);


#endif /* SPI_H_ */
