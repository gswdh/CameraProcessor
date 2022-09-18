#ifndef __ECXH__
#define __ECXH__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

extern const uint8_t * ecx_conf;

// Need to be implemented by the system
void ecx_spi_transfer(uint8_t * tx_data, uint8_t * rx_data, uint32_t len);
void ecx_reset(bool enable);
void ecx_enable_1V8(bool enable);
void ecx_enable_10V(bool enable);
void ecx_delay_ms(uint32_t time_ms);

// To be called by the system
void ecx_init();
void ecx_deinit();

// Private
static void ecx_exit_ps0()
static void ecx_exit_ps1();
static void ecx_write_reg(uint8_t reg, uint8_t * data, uint32_t len);
static void ecx_read_reg(uint8_t reg, uint8_t * data, uint32_t len);

#endif


