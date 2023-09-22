#include "spi.h"

#include "xparameters.h"
#include "xspips.h"

XSpiPs spi_dev = {0};

void spi_init()
{
	XSpiPs_Config *spi_conf = XSpiPs_LookupConfig(XPAR_XSPIPS_0_DEVICE_ID);

	XSpiPs_CfgInitialize(&spi_dev, spi_conf, spi_conf->BaseAddress);

	XSpiPs_SelfTest(&spi_dev);

	XSpiPs_SetOptions(&spi_dev, XSPIPS_MANUAL_START_OPTION | XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);

	XSpiPs_SetClkPrescaler(&spi_dev, XSPIPS_CLK_PRESCALE_8);
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
	// Preset which device will be communicated with
	XSpiPs_SetSlaveSelect(&spi_dev, dev_cs);

	// Do the transfer
	XSpiPs_PolledTransfer(&spi_dev, tx_data, rx_data, len);
}
