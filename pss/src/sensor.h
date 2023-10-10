#ifndef __SNSR__
#define __SNSR__

#include <stdbool.h>
#include <stdint.h>

void sensor_init_control();
void sensor_set_training_word(uint16_t training_word);
void sensor_set_sync(bool en);
bool sensor_get_sync();
void sensor_sync_data(uint16_t training_word);

void sensor_start();
void sensor_task(void * params);

#endif