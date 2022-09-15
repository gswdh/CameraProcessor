#ifndef __ECXH__
#define __ECXH__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Need to be implemented by the system
void ecx_spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);
void ecx_reset(bool enable);

// To be called by the system
void ecx_init();


// Private
static void ecx_load_regs();




#endif


