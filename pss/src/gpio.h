#ifndef __GPIO__
#define __GPIO__

#include <stdint.h>
#include <stdbool.h>

#define GPIO_DIR_INPUT (0x00)
#define GPIO_DIR_OUTPUT (0x01)
#define GPIO_OUTPUT_EN (0x01)

typedef enum
{
    BTN_TOPLEFT_PIN = 1,
    BTN_BTMRIGHT_PIN = 9,
    SEN_SYS_NRESET_PIN = 28,
    DSP_NRESET_PIN = 29,
    PWR_SEN_3V6_EN_PIN = 30,
    PWR_EVF_AVDD_EN_PIN = 31,
    TMP_ALERT_PIN = 32,
    BTN_BTMLEFT_PIN = 33,
    PWR_SEN_1V3_EN_PIN = 35,
    PWR_SEN_0V7_EN_PIN = 36,
    TMP_THERM_PIN = 38,
    SEN_TEXP0_PIN = 39,
    PWR_SEN_3V3A_EN_PIN = 40,
    BTN_THUMB_PIN = 41,
    DSP_D_NC_PIN = 42,
    SEN_TDIG1_PIN = 43,
    EVF_NRESET_PIN = 44,
    PWR_EVF_AVEE_EN_PIN = 45,
    PWR_SEN_4V1_EN_PIN = 46,
    PWR_SEN_N1V3A_EN_PIN = 47,
    SEN_TDIG0_PIN = 48,
    PWR_VDISP_EN_PIN = 49,
    BTN_TOPRIGHT_PIN = 50,
    PSS_PMC_FLAG_PIN = 51,
    PMC_PSS_FLAG_PIN = 52,
    SEN_TEXP1_PIN = 53
} gpio_pins_t;

#define FPGA_DEBUG_0 (0x0001)
#define FPGA_DEBUG_1 (0x0002)
#define FPGA_DEBUG_2 (0x0004)
#define FPGA_DEBUG_3 (0x0008)
#define FPGA_DEBUG_4 (0x0010)
#define FPGA_DEBUG_5 (0x0020)
#define FPGA_DEBUG_6 (0x0040)
#define FPGA_DEBUG_7 (0x0080)
#define FPGA_DEBUG_CLK (0x0100)
#define FPGA_DEBUG_EN (0x0200)
#define FPGA_STATUS_D0 (0x0400)
#define FPGA_STATUS_D1 (0x0800)
#define FPGA_STATUS_D2 (0x1000)
#define FPGA_LED_D0 (0x2000)
#define FPGA_LED_D1 (0x4000)
#define FPGA_LED_D2 (0x8000)

void gpio_init();
bool gpio_get(gpio_pins_t pin);
void gpio_set(gpio_pins_t pin, bool state);
bool gpio_pl_get(uint32_t pin_mask);
void gpio_pl_set(uint32_t pin_mask, bool state);
void gpio_task(void *params);

#endif
