// MAIN!
#include "main.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// Xilinx includes
#include "xil_printf.h"
#include "xparameters.h"

// Driver includes
#include "hw_int.h"
#include "ecx.h"

int main(void)
{
    // Start init
    xil_printf("Camera starting.\n");

    // Init the hardware
    hwi_init();

    // Init the EVF
    ecx_init();






    // Tasks
    //xTaskCreate(prvRxTask, (const char *)"GB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xRxTask);


    // Run the scheduler
    vTaskStartScheduler();

    while(1)
    {

    }
}
