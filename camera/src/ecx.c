#include "ecx.h"

__attribute__((weak)) void ecx_spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len) 
{
	return;
}

__attribute__((weak)) void ecx_reset(bool enable)
{
	return;
}

__attribute__((weak)) void ecx_enable_1V8(bool enable)
{
	return;
}

__attribute__((weak)) void ecx_enable_10V(bool enable)
{
	return;
}

__attribute__((weak)) void ecx_delay_ms(uint32_t time_ms)
{
	return;
}

static void ecx_write_reg(uint8_t reg, uint8_t * data, uint32_t len)
{
	uint8_t * tx_data = malloc(len + 1);
	if(tx_data == NULL) return;
	tx_data[0] = reg;
	memcpy(tx_data + 1, data, len);
	ecx_spi_transfer(tx_data, NULL, sizeof(tx_data));
	free(tx_data);
}

static void ecx_read_reg(uint8_t reg, uint8_t * data, uint32_t len)
{
	// Set the read pointer
	uint8_t read_en[2] = {0x81, reg};
	ecx_spi_transfer(read_en, NULL, 0x02);

	// Read
	uint8_t * rx_data = malloc(len + 1);
	if(rx_data == NULL) return;
	ecx_spi_transfer(read_en, rx_data, len + 1);
	memcpy(data, rx_data + 1, len);
	free(rx_data);
}

static void ecx_exit_ps0()
{
	uint8_t reg = 0;
	ecx_read_reg(0x00, &reg, 0x01);

	// Reset the PS0 bit
	reg &= ~0x01;

	ecx_write_reg(0x00, &reg, 0x01);
}

static void ecx_exit_ps1()
{
	uint8_t reg = 0;
	ecx_read_reg(0x00, &reg, 0x01);

	// Reset the PS1 bit
	reg &= ~0x02;

	ecx_write_reg(0x00, &reg, 0x01);
}

void ecx_init()
{
	// 1. Set XCLR to low and turn on 1.8V power supply, then the panel should be initialized.
	ecx_reset(true);
	ecx_delay_ms(1);
	ecx_enable_1V8(true);
	ecx_enable_10V(true);

	// 2. After completion of 1.8 V power supply rising, set XCLR to high, then the panel changes to PS (Power-saving) mode within 16 msec.
	ecx_reset(false);
	ecx_delay_ms(1);

	// 3. Executing serial setting 1.
	ecx_write_reg(0x00, (uint8_t*)ecx_conf, sizeof(ecx_conf));

	// 4. Executing PS0 (Power-saving)-off by serial setting 2, 200usec later, it can be valid to input data . 
	ecx_exit_ps0();
	ecx_delay_ms(1);

	// 5. Executing PS1 (Power-saving)-off by serial setting 3, then the panel should be in normal state. 
	ecx_exit_ps1();
	ecx_delay_ms(1);
}

void ecx_deinit()
{

}
