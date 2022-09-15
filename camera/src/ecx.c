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

void ecx_init()
{

}

static void ecx_load_regs()
{

}
