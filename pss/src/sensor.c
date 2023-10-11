#include "sensor.h"

#include "gmax0505.h"

#include "sys.h"
#include "gpio.h"
//#include "i2c.h"

#include "logging.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "xgpio.h"

#define LOG_TAG "SENSOR"

#define SENSOR_GPIO_INPUT_PORT (0x01)
#define SENSOR_GPIO_OUTPUT_PORT (0x02)
#define SENSOR_GPIO_SYNC_EN (0x1000)
#define SENSOR_GPIO_SYNC_DONE (0x0001)
#define SENSOR_TRAINING_WORD (0xD0E)

XGpio sensor_gpio_pl = {0};

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

uint16_t sensor_read_training_word()
{
	uint8_t data[3] = {0};
	gmax_spi_read(214, data, 3);

	uint16_t word = 0x03D0;

	return word;
}

void sensor_init_control()
{
	XGpio_Initialize(&sensor_gpio_pl, XPAR_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&sensor_gpio_pl, SENSOR_GPIO_OUTPUT_PORT, 0x00000000);
	XGpio_SetDataDirection(&sensor_gpio_pl, SENSOR_GPIO_INPUT_PORT, 0xFFFFFFFF);
}

void sensor_set_training_word(uint16_t training_word)
{
	uint32_t data = XGpio_DiscreteRead(&sensor_gpio_pl, SENSOR_GPIO_OUTPUT_PORT);
	data &= ~0x0FFF;
	data |= (training_word & 0x0FFF);
	XGpio_DiscreteWrite(&sensor_gpio_pl, SENSOR_GPIO_OUTPUT_PORT, data);
}

void sensor_set_sync(bool en)
{
	uint32_t data = XGpio_DiscreteRead(&sensor_gpio_pl, SENSOR_GPIO_OUTPUT_PORT);
	data = en ? (data |= SENSOR_GPIO_SYNC_EN) : (data &= ~SENSOR_GPIO_SYNC_EN);
	XGpio_DiscreteWrite(&sensor_gpio_pl, SENSOR_GPIO_OUTPUT_PORT, data);
}

bool sensor_get_sync()
{
	uint32_t data = XGpio_DiscreteRead(&sensor_gpio_pl, SENSOR_GPIO_INPUT_PORT);
	return (bool)(data & SENSOR_GPIO_SYNC_DONE);
}

void sensor_sync_data(uint16_t training_word)
{
	// Check if it's done already
	if(sensor_get_sync())
	{
		return;
	}

	// Set the training word
	uint16_t word = sensor_read_training_word();
	sensor_set_training_word(word);


	// Wait for the syncing to be done
	while(!sensor_get_sync())
	{
		sys_delay_ms(1);
	}

	// Disable the syncing
	sensor_set_sync(false);
}

void sensor_start()
{
	// Power up the sensor
	gmax_start();

	// Get the data syncd
	sensor_init_control();
	sensor_sync_data(SENSOR_TRAINING_WORD);

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




