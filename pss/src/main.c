// System includes

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// Xilinx includes
#include "xil_printf.h"
#include "xparameters.h"

// Peripheral includes
#include "gpio.h"

// Abstraction includes

int main(void)
{
	gpio_init();

	xil_printf("Hello from Freertos example main\n");

	volatile int start = 0;

	if (start == 1)
	{
		// Make sure the sensor starts in reset
		gpio_set(SEN_SYS_NRESET_PIN, false);

		// VDDIO is already on

		// 1V3 reg
		gpio_set(PWR_SEN_1V3_EN_PIN, true);

		// 3V3A reg
		gpio_set(PWR_SEN_3V3A_EN_PIN, true);

		// Array suppply etc.
		gpio_set(PWR_SEN_3V6_EN_PIN, true);
		gpio_set(PWR_SEN_1V3_EN_PIN, true);
		gpio_set(PWR_SEN_0V7_EN_PIN, true);
		gpio_set(PWR_SEN_4V1_EN_PIN, true);
		gpio_set(PWR_SEN_N1V3A_EN_PIN, true);

		// Out of reset
		gpio_set(SEN_SYS_NRESET_PIN, true);
	}

	vTaskStartScheduler();

	for (;;)
		;
}






