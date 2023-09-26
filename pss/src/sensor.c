#include "sensor.h"

#include "gmax0505.h"

#include "sys.h"
#include "gpio.h"
//#include "i2c.h"

#include "logging.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

#define LOG_TAG "SENSOR"

TaskHandle_t sensor_task_handle = {0};

void gmax_set_nreset(bool en)
{
	gpio_set(SEN_SYS_NRESET_PIN, en);
}

void gmax_pwr_0V7(bool en)
{
	gpio_set(PWR_SEN_0V7_EN_PIN, en);
}

void gmax_pwr_N1V3(bool en)
{
	gpio_set(PWR_SEN_N1V3A_EN_PIN, en);
}

void gmax_pwr_1V3(bool en)
{
	gpio_set(PWR_SEN_1V3_EN_PIN, en);
}

void gmax_pwr_3V3A(bool en)
{
	gpio_set(PWR_SEN_3V3A_EN_PIN, en);
}

void gmax_pwr_3V6(bool en)
{
	gpio_set(PWR_SEN_3V6_EN_PIN, en);
}

void gmax_pwr_4V1(bool en)
{
	gpio_set(PWR_SEN_4V1_EN_PIN, en);
}

static void nop_delay()
{
	const uint32_t n = 2;
	for(uint32_t i = 0; i < n; i++)
	{
		asm("nop");
	}
}

void gmax_spi_write(uint8_t reg, uint8_t * data, uint32_t len)
{
	// Make sure the clock line and en is low
	gpio_set(PSS_SPI_SCLK, false);
	gpio_set(SEN_SPI_NCS, false);

	// Give some timing
	nop_delay();

	// Set the data to true for a write operation and enable
	gpio_set(PSS_SPI_MOSI, true);
	gpio_set(SEN_SPI_NCS, true);

	nop_delay();

	// Clock the write bit in
	gpio_set(PSS_SPI_SCLK, true);
	nop_delay();

	// Clock the reg address out first
	for(uint8_t j = 0; j < 8; j++)
	{
		// Start with a falling edge and clock the data out
		gpio_set(PSS_SPI_SCLK, false);
		gpio_set(PSS_SPI_MOSI, (reg >> (7 - j)) & 0x01);

		// Hold time
		nop_delay();

		// Rising clock edge
		gpio_set(PSS_SPI_SCLK, true);

		// Hold time
		nop_delay();
	}	

	// Now clock out the data
	for(uint32_t i = 0; i < len; i++)
	{
		uint8_t b = data[i];

		// Go through the bits
		for(uint8_t j = 0; j < 8; j++)
		{
			// Start with a falling edge and clock the data out
			gpio_set(PSS_SPI_SCLK, false);
			gpio_set(PSS_SPI_MOSI, (b >> (7 - j)) & 0x01);

			// Hold time
			nop_delay();

			// Rising clock edge
			gpio_set(PSS_SPI_SCLK, true);

			// Hold time
			nop_delay();
		}
	}

	// Need a falling edge to finish
	gpio_set(PSS_SPI_SCLK, false);

	// Hold time
	nop_delay();

	// End transaction with en to false
	gpio_set(SEN_SPI_NCS, false);
}

void gmax_spi_read(uint8_t reg, uint8_t * data, uint32_t len)
{
	// Make sure the clock line and en is low
	gpio_set(PSS_SPI_SCLK, false);
	gpio_set(SEN_SPI_NCS, false);

	// Give some timing
	nop_delay();

	// Reset the data to true for a write operation and enable
	gpio_set(PSS_SPI_MOSI, false);
	gpio_set(SEN_SPI_NCS, true);

	nop_delay();

	// Clock the write bit in
	gpio_set(PSS_SPI_SCLK, true);
	nop_delay();

	// Clock the reg address out first
	for(uint8_t j = 0; j < 8; j++)
	{
		// Start with a falling edge and clock the data out
		gpio_set(PSS_SPI_SCLK, false);
		gpio_set(PSS_SPI_MOSI, (reg >> (7 - j)) & 0x01);

		// Hold time
		nop_delay();

		// Rising clock edge
		gpio_set(PSS_SPI_SCLK, true);

		// Hold time
		nop_delay();
	}

	// Create one clock cycle spacing
	gpio_set(PSS_SPI_SCLK, false);
	nop_delay();
	gpio_set(PSS_SPI_SCLK, true);
	nop_delay();


	// Now clock out the data
	for(uint32_t i = 0; i < len; i++)
	{
		data[i] = 0;

		// Go through the bits
		for(uint8_t j = 0; j < 8; j++)
		{
			// Start with a falling edge and clock the data out
			gpio_set(PSS_SPI_SCLK, false);
			
			// Hold time
			nop_delay();

			// Rising clock edge
			gpio_set(PSS_SPI_SCLK, true);
			data[i] |= (gpio_get(PSS_SPI_MISO) << (7 - j));

			// Hold time
			nop_delay();
		}
	}

	// Need a falling edge to finish
	gpio_set(PSS_SPI_SCLK, false);

	// Hold time
	nop_delay();

	// End transaction with en to false
	gpio_set(SEN_SPI_NCS, false);
}

bool gmax_get_tdig0()
{
	return false;
}

bool gmax_get_tdig1()
{
	return false;
}

void gmax_set_texp0(bool en)
{

}

void gmax_set_texp1(bool en)
{

}

void gmax_i2c_read(uint8_t reg_addr, uint8_t *data, uint16_t length)
{

}

void gmax_i2c_write(uint8_t reg_addr, uint8_t *data, uint16_t length)
{

}

bool gmax_get_temp_therm()
{
	return false;
}

bool gmax_get_temp_alert()
{
	return false;
}

void gmax_delay_ms(uint32_t time_ms)
{
	sys_delay_ms(time_ms);
}

void sensor_start()
{
	// Power up the sensor
	gmax_start();

	// Start the running task
	xTaskCreate(sensor_task, LOG_TAG, 1024, NULL, tskIDLE_PRIORITY, &sensor_task_handle);
}

void sensor_task(void * params)
{
	while(1)
	{
		sys_delay_ms(100);
	}
}




