#ifndef __HWIH__
#define __HWIH__

#include <stdint.h>
#include <string.h>

#include "ecx.h"

#define GPIO_EVF_1V8_EN	(0x00)
#define GPIO_EVF_10V_EN	(0x01)
#define GPIO_EVF_NRST	(0x02)

#define GPIO_DIR_OUTPUT (0x00)
#define GPIO_DIR_INPUT 	(0x01)

void hwi_init();
void hwi_spi0_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);
void hwi_spi1_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);



#endif

