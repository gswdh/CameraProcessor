#include "gpio.h"

// Xilinx
#include "xparameters.h"
#include "xgpiops.h"
#include "xil_printf.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

XGpioPs gpio_dev = {0};

TaskHandle_t gpio_task_handle = {0};

const gpio_pins_t gpio_outputs[] = {SEN_SYS_NRESET_PIN,
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

void gpio_init()
{
	XGpioPs_Config *gpio_config = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&gpio_dev, gpio_config, gpio_config->BaseAddr);

	// Inputs
	XGpioPs_SetDirectionPin(&gpio_dev, BTN_TOPLEFT_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, BTN_BTMRIGHT_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, TMP_ALERT_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, BTN_BTMLEFT_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, TMP_THERM_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, BTN_THUMB_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, SEN_TDIG0_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, SEN_TDIG1_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, BTN_TOPRIGHT_PIN, GPIO_DIR_INPUT);
	XGpioPs_SetDirectionPin(&gpio_dev, PMC_PSS_FLAG_PIN, GPIO_DIR_INPUT);

	// Outputs
	for(uint32_t i = 0; i < sizeof(gpio_outputs); i++)
	{
		XGpioPs_SetDirectionPin(&gpio_dev, gpio_outputs[i], GPIO_DIR_OUTPUT);
		gpio_set(gpio_outputs[i], false);
		XGpioPs_SetOutputEnablePin(&gpio_dev, gpio_outputs[i], GPIO_OUTPUT_EN);		
	}

	// Look for state changes
	xTaskCreate(gpio_task, "GPIO Polling", 1024, NULL, tskIDLE_PRIORITY, &gpio_task_handle);
}

bool gpio_get(gpio_pins_t pin)
{
	return XGpioPs_ReadPin(&gpio_dev, (uint32_t)pin);
}

void gpio_set(gpio_pins_t pin, bool state)
{
	XGpioPs_WritePin(&gpio_dev, (uint32_t)pin, (uint32_t)state);
}

void gpio_task(void *params)
{
	uint32_t tick = xTaskGetTickCount();

	while (1)
	{
		if (xTaskGetTickCount() > (tick + 50))
		{
			tick = xTaskGetTickCount();

			//xil_printf("TL = %u, BR = %u\n", gpio_get(BTN_TOPLEFT_PIN), gpio_get(BTN_BTMRIGHT_PIN));
		}
	}
}

