#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stddef.h>

#define SPI_DEV_CS_0 (0)
#define SPI_DEV_CS_1 (1)
#define SPI_DEV_CS_2 (2)

void spi_init();
void spi_write(uint8_t * data, uint32_t len);
void spi_read(uint8_t * data, uint32_t len);
void spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);

#endif
