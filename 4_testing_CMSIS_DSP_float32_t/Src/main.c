#include <math.h>
#include "arm_math.h"
#include "signals.h"

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

#include "uart.h"
#include "uartstdio.h"

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t inputSignal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN];

arm_status status;

static void pseudo_delay(int delay);
static void fpu_enable(void);


int32_t main(void)
{
    // Configure system clock
    clock_init();

    // Enable FPU
    fpu_enable();

    // Configure UART0
    uart0_tx_init();

    int i;

    while(1)
    {
        for (i = 0; i < KHZ1_15_SIG_LEN; i++)
        {
            UARTprintf("%d\r\n", (int32_t) (inputSignal_f32_1kHz_15kHz[i] * 10000));
            pseudo_delay(100000);
        }
    }
}

static void pseudo_delay(int delay)
{
    int i;
    for (i = 0; i < delay; i++){}
}

static void fpu_enable(void)
{
    // Enable FPU: Enable CP10 and CP11 full access
    // Reference from function FPUEnable() of  "driverlib/fpu.h"

    //HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) &
    //                     ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
    //                    NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);
    HWREG(NVIC_CPAC) |= ((3UL << 10*2) | (3UL << 11*2));

}
