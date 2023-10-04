#include "stream.h"

// Xilinx
#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"

// Abstractions
#include "logging.h"
#include "sys.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

#define LOG_TAG "STRM"

XAxiDma dma = {0};

#define MEM_BASE_ADDR		(XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000)
#define TX_BD_SPACE_BASE	(MEM_BASE_ADDR)
#define TX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x00000FFF)
#define RX_BD_SPACE_BASE	(MEM_BASE_ADDR + 0x00001000)
#define RX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x00001FFF)
#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00300000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x004FFFFF)

void strm_init(strm_callback cb)
{
	// Init the DMA
	XAxiDma_Config *dma_config = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
	XAxiDma_CfgInitialize(&dma, dma_config);

	// Disable interrupts
	XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	// Start the task
	TaskHandle_t strm_task_handle = {0};
	xTaskCreate(strm_task, LOG_TAG, 1024, NULL, tskIDLE_PRIORITY, &strm_task_handle);
}

void strm_tx(uint8_t * data, uint32_t len)
{
	Xil_DCacheFlushRange((UINTPTR)data, len);
	XAxiDma_SimpleTransfer(&dma, (UINTPTR)data, len, XAXIDMA_DMA_TO_DEVICE);
}

void strm_rx(uint8_t * data, uint32_t len)
{
	Xil_DCacheFlushRange((UINTPTR)data, len);
	XAxiDma_SimpleTransfer(&dma, (UINTPTR)data, len, XAXIDMA_DEVICE_TO_DMA);
}

bool strm_tx_done()
{
	return (bool)!XAxiDma_Busy(&dma, XAXIDMA_DMA_TO_DEVICE);
}

bool strm_rx_done()
{
	return (bool)!XAxiDma_Busy(&dma, XAXIDMA_DEVICE_TO_DMA);
}

void strm_task(void * params)
{

	uint8_t * x = malloc(5120*5120*2);

	while(x == NULL)
	{
		asm("NOP");
	}

	while(1)
	{
		strm_tx(x, 1024);

		while(!strm_tx_done())
		{
			asm("NOP");
		}
	}
}
