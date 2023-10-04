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

#define GUI_DSP_DC_PIN (FPGA_DEBUG_7)
#define GUI_DSP_NRST_PIN (FPGA_DEBUG_5)

uint8_t gui_disp_buffer[SSD_DISP_BUFFER_LEN] = {0};

TaskHandle_t gui_task_handle = {0};

void ssd_spi_write(uint8_t * data, uint32_t len)
{
	spi_write(data, len);
}

void ssd_set_dc(bool en)
{
	gpio_pl_set(GUI_DSP_DC_PIN, en);
}

void ssd_set_cs(bool en)
{
	return;
}

void ssd_set_rst(bool en)
{
	gpio_pl_set(GUI_DSP_NRST_PIN, en);
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

			ssd_update_display(gui_disp_buffer);
		}
	}
}

