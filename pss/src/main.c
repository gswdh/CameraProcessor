// System includes

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// Xilinx includes
#include "xparameters.h"

// Peripheral includes
#include "gpio.h"
#include "stream.h"

// Abstraction includes
#include "gui.h"
#include "logging.h"
#include "sensor.h"

#define LOG_TAG "MAIN"

void strm_event_cb(strm_event_t evt)
{
	log_info(LOG_TAG, "Stream event = %u\n", evt);
}

void main_task(void * params)
{
	log_info(LOG_TAG, "Starting system.\n");

	// Perph inits (must be done before abstraction)
	gpio_init();
	strm_init(strm_event_cb);

	// Abstraction starts
	gui_start();
	sensor_start();

	vTaskDelete(NULL);	
}

int main(void)
{
	TaskHandle_t main_task_handle = {0};
	xTaskCreate(main_task, LOG_TAG, 1024, NULL, tskIDLE_PRIORITY, &main_task_handle);

	vTaskStartScheduler();
	
	return 0;
}






