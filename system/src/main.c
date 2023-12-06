// FreeRTOS includes.
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// Xilinx includes.
#include "xil_printf.h"
#include "xparameters.h"

int main( void )
{
	xil_printf("Camera system starting.\n");
	vTaskStartScheduler();
	for( ;; );
}
