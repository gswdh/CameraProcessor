#ifndef __HWIH__
#define __HWIH__

#include <stdint.h>
#include <string.h>

#include "ecx.h"

void hwi_init();
void hwi_spi0_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);
void hwi_spi1_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);



#endif

