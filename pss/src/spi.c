#include "spi.h"

#include "gpio.h"

const gpio_pins_t cs_pins[] = {};

void spi_init()
{

}

void spi_write(uint8_t dev_cs, uint8_t * data, uint32_t len)
{
	spi_transfer(dev_cs, data, NULL, len);
}

void spi_read(uint8_t dev_cs, uint8_t * data, uint32_t len)
{
	spi_transfer(dev_cs, NULL, data, len);
}

void spi_transfer(uint8_t dev_cs, uint8_t * tx_data, uint8_t * rx_data, uint32_t len)
{

}
