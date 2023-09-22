#include "sys.h"

#include "FreeRTOS.h"
#include "task.h"

void sys_delay_ms(uint32_t time_ms)
{
	vTaskDelay(time_ms / portTICK_PERIOD_MS);
}

uint32_t sys_tick_ms()
{
	return xTaskGetTickCount();
}
