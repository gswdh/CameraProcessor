#include "gpio.h"

// Xilinx
#include "xparameters.h"
#include "xgpiops.h"
#include "xgpio.h"
#include "xil_printf.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

// Abstractions
#include "logging.h"
#include "sys.h"

#define LOG_TAG "GPIO"

#define GPIO_FPGA_PORT_CHANNEL (0x01)

XGpioPs gpio_ps = {0};
XGpio gpio_pl = {0};

TaskHandle_t gpio_task_handle = {0};

const gpio_pins_t gpio_outputs[] = {PSS_SPI_SCLK, SEN_SPI_NCS, DSP_SPI_NCS, PSS_SPI_MOSI,
SEN_SYS_NRESET_PIN,
DSP_NRESET_PIN,
PWR_SEN_3V6_EN_PIN,
PWR_EVF_AVDD_EN_PIN,
PWR_SEN_1V3_EN_PIN,
SEN_TEXP0_PIN,
PWR_SEN_3V3A_EN_PIN,
DSP_D_NC_PIN,
EVF_NRESET_PIN,
PWR_EVF_AVEE_EN_PIN,
PWR_SEN_4V1_EN_PIN,
PWR_SEN_N1V3A_EN_PIN,
PWR_VDISP_EN_PIN,
PSS_PMC_FLAG_PIN,
SEN_TEXP1_PIN,
PWR_SEN_0V7_EN_PIN};

const gpio_pins_t gpio_inputs[] = {
BTN_TOPLEFT_PIN,
PSS_SPI_MISO,
BTN_BTMRIGHT_PIN,
TMP_ALERT_PIN,
BTN_BTMLEFT_PIN,
TMP_THERM_PIN,
BTN_THUMB_PIN,
SEN_TDIG0_PIN,
SEN_TDIG1_PIN,
BTN_TOPRIGHT_PIN,
PMC_PSS_FLAG_PIN};

void gpio_init()
{
	// PS based GPIO
	XGpioPs_Config *gpio_config = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&gpio_ps, gpio_config, gpio_config->BaseAddr);

	// Inputs
	for(uint32_t i = 0; i < sizeof(gpio_inputs); i++)
	{
		XGpioPs_SetDirectionPin(&gpio_ps, gpio_inputs[i], GPIO_DIR_INPUT);
	}

	// Outputs
	for(uint32_t i = 0; i < sizeof(gpio_outputs); i++)
	{
		XGpioPs_SetDirectionPin(&gpio_ps, gpio_outputs[i], GPIO_DIR_OUTPUT);
		gpio_set(gpio_outputs[i], false);
		XGpioPs_SetOutputEnablePin(&gpio_ps, gpio_outputs[i], GPIO_OUTPUT_EN);		
	}

	// FPGA based GPIO
	XGpio_Initialize(&gpio_pl, XPAR_GPIO_0_DEVICE_ID);

	// All as outputs
	XGpio_SetDataDirection(&gpio_pl, GPIO_FPGA_PORT_CHANNEL, 0x00000000);

	// Look for state changes
	xTaskCreate(gpio_task, "GPIO Polling", 1024, NULL, tskIDLE_PRIORITY, &gpio_task_handle);
}

bool gpio_get(gpio_pins_t pin)
{
	return XGpioPs_ReadPin(&gpio_ps, (uint32_t)pin);
}

void gpio_set(gpio_pins_t pin, bool state)
{
	XGpioPs_WritePin(&gpio_ps, (uint32_t)pin, (uint32_t)state);
}

bool gpio_pl_get(uint32_t pin_mask)
{
	return false;
}

void gpio_pl_set(uint32_t pin_mask, bool state)
{
	uint32_t data = XGpio_DiscreteRead(&gpio_pl, GPIO_FPGA_PORT_CHANNEL);

	data = state ? (data |= pin_mask) : (data &= ~pin_mask);
	
	XGpio_DiscreteWrite(&gpio_pl, GPIO_FPGA_PORT_CHANNEL, data);
}

void gpio_task(void *params)
{
	uint32_t tick = xTaskGetTickCount();

	while (1)
	{
		if (xTaskGetTickCount() > (tick + 100))
		{
			tick = xTaskGetTickCount();

			gpio_pl_set(FPGA_LED_D0, true);
			sys_delay_ms(1);
			gpio_pl_set(FPGA_LED_D0, false);

			/*
			log_info(LOG_TAG, "TL = %u, TR = %u, BL = %u, BR = %u, TM = %u\n",
					gpio_get(BTN_TOPLEFT_PIN),
					gpio_get(BTN_TOPRIGHT_PIN),
					gpio_get(BTN_BTMLEFT_PIN),
					gpio_get(BTN_BTMRIGHT_PIN),
					gpio_get(BTN_THUMB_PIN));
					*/
		}
	}
}

