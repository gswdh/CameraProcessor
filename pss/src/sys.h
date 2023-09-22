#ifndef __SYS__
#define __SYS__

#include <stdint.h>

void sys_delay_ms(uint32_t time_ms);
uint32_t sys_tick_ms();

#endif