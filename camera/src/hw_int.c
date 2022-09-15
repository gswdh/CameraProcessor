#include "hw_int.h"

#include "xspips.h"

static XSpiPs inst_spi_0 = {0};
static XSpiPs inst_spi_1 = {0};

static void hwi_spi0_init()
{
	XSpiPs_Config * conf = XSpiPs_LookupConfig(XPAR_XSPIPS_0_DEVICE_ID);
	if (conf == NULL) return;
	
	int32_t status = XSpiPs_CfgInitialize(&inst_spi_0, conf, conf->BaseAddress);
	if (status != XST_SUCCESS) return;

	status = XSpiPs_SelfTest(&inst_spi_0);
	if (status != XST_SUCCESS) return;
	
	status = XSpiPs_SetOptions(&inst_spi_0, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
	if (status != XST_SUCCESS) return;

	XSpiPs_SetClkPrescaler(&inst_spi_0, XSPIPS_CLK_PRESCALE_64);
}

static void hwi_spi1_init()
{
	XSpiPs_Config * conf = XSpiPs_LookupConfig(XPAR_XSPIPS_1_DEVICE_ID);
	if (conf == NULL) return;
	
	int32_t status = XSpiPs_CfgInitialize(&inst_spi_1, conf, conf->BaseAddress);
	if (status != XST_SUCCESS) return;

	status = XSpiPs_SelfTest(&inst_spi_1);
	if (status != XST_SUCCESS) return;
	
	status = XSpiPs_SetOptions(&inst_spi_1, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
	if (status != XST_SUCCESS) return;

	XSpiPs_SetClkPrescaler(&inst_spi_1, XSPIPS_CLK_PRESCALE_64);
}

static void hwi_gpioevf_init()
{

}

void hwi_init()
{
	// Init the HW
	hwi_spi0_init();
	hwi_spi1_init();
	hwi_gpioevf_init();
}

void hwi_spi0_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len)
{
	// 0x00 for the 0th SS line (of 3)
	XSpiPs_SetSlaveSelect(&inst_spi_0, (uint8_t)0x00);

	// Simply call the transfer function
	XSpiPs_PolledTransfer(&inst_spi_0, tx_data, rx_data, len);
}

void hwi_spi1_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len)
{
	// 0x00 for the 0th SS line (of 3)
	XSpiPs_SetSlaveSelect(&inst_spi_1, (uint8_t)0x00);

	// Simply call the transfer function
	XSpiPs_PolledTransfer(&inst_spi_1, tx_data, rx_data, len);	
}

void ecx_spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len) 
{
	return;
}

void ecx_reset(bool enable)
{
	return;
}

void ecx_enable_1V8(bool enable)
{
	return;
}

void ecx_enable_10V(bool enable)
{
	return;
}

