#include "spi.h"

#include "gpio.h"

#include "xparameters.h"
#include "xspi.h"
#include "xspi_l.h"

XSpi spi_pl = {0};

const gpio_pins_t cs_pins[] = {};

void spi_init()
{
	XSpi_Config *spi_pl_config = XSpi_LookupConfig(XPAR_SPI_0_DEVICE_ID);
	XSpi_CfgInitialize(&spi_pl, spi_pl_config, spi_pl_config->BaseAddress);
	XSpi_SetOptions(&spi_pl, XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION);
	XSpi_SetSlaveSelect(&spi_pl, 0x01);
	XSpi_Start(&spi_pl);
	XSpi_IntrGlobalDisable(&spi_pl);
}

void spi_write(uint8_t * data, uint32_t len)
{
	spi_transfer(data, NULL, len);
}

void spi_read(uint8_t * data, uint32_t len)
{
	spi_transfer(NULL, data, len);
}

void spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len)
{
	XSpi_Transfer(&spi_pl, tx_data, rx_data, len);
}
