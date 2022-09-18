#include "hw_int.h"

#include "xspips.h"
#include "xgpio.h"
#include "FreeRTOS.h"
#include "task.h"

static XSpiPs inst_spi_0 = {0};
static XSpiPs inst_spi_1 = {0};

static XGpio inst_gpio_0 = {0};

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
	// EVF GPIO
	int32_t status = XGpio_Initialize(&inst_gpio_0, XPAR_AXI_EVF_GPIO_1_DEVICE_ID);
	if (status != XST_SUCCESS) return;

	// Set this channel (EVF only have one channel) as an output
	XGpio_SetDataDirection(&inst_gpio_0, 0, GPIO_DIR_OUTPUT);
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
	hwi_spi0_transfer(tx_data, rx_data, len);
}

void ecx_enable_reset(bool enable)
{
	if(!enable) XGpio_DiscreteWrite(&inst_gpio_0, 0, GPIO_EVF_NRST);
	else XGpio_DiscreteClear(&inst_gpio_0, 0, GPIO_EVF_NRST);
}

void ecx_enable_1V8(bool enable)
{
	if(enable) XGpio_DiscreteWrite(&inst_gpio_0, 0, GPIO_EVF_1V8_EN);
	else XGpio_DiscreteClear(&inst_gpio_0, 0, GPIO_EVF_1V8_EN);
}

void ecx_enable_10V(bool enable)
{
	if(enable) XGpio_DiscreteWrite(&inst_gpio_0, 0, GPIO_EVF_10V_EN);
	else XGpio_DiscreteClear(&inst_gpio_0, 0, GPIO_EVF_10V_EN);
}

void ecx_delay_ms(uint32_t time_ms)
{
	vTaskDelay(time_ms / portTICK_PERIOD_MS);
}
