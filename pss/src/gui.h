#ifndef _GUI_H_
#define _GUI_H_

#include <stdbool.h>
#include <stdint.h>

#define GUI_DISP_BUFF_LEN (8192)

void gui_start();
void gui_task(void * params);

#endif