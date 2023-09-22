#include "gui.h"

// Perphs
#include "spi.h"
#include "gpio.h"

// Abstractions
#include "sys.h"
#include "ssd1309z.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

#define SSD_SPI_CS_PIN (SPI_DEV_CS_1)

uint8_t gui_disp_buffer[GUI_DISP_BUFF_LEN] = {0};

TaskHandle_t gui_task_handle = {0};

void ssd_spi_write(uint8_t * data, uint32_t len)
{
	spi_write(SSD_SPI_CS_PIN, data, len);
}

void ssd_set_dc(bool en)
{
	gpio_set(DSP_D_NC_PIN, en);
}

void ssd_set_cs(bool en)
{
	return;
}

void ssd_set_rst(bool en)
{
	gpio_set(DSP_NRESET_PIN, en);
}

void ssd_pwr_cont(bool en)
{
	gpio_set(PWR_VDISP_EN_PIN, en);
}

void ssd_delay_ms(uint32_t time_ms)
{
	sys_delay_ms(time_ms);
}

void gui_start()
{
	ssd_init();

	gui_disp_buffer[0] = 0xFF;

	xTaskCreate(gui_task, "GUI", 1024, NULL, tskIDLE_PRIORITY, &gui_task_handle);
}

void gui_task(void * params)
{
	uint32_t tick = sys_tick_ms();

	while(1)
	{
		if(sys_tick_ms() > (tick + 100))
		{
			tick = sys_tick_ms();

			ssd_write_data(gui_disp_buffer, GUI_DISP_BUFF_LEN);
		}
	}
}

