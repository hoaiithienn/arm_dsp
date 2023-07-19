#include <math.h>
#include "arm_math.h"
#include "signals.h"

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

extern float _5hz_signal[HZ_5_SIG_LEN];

arm_status status;

float g_in_sig_sample;
int g_idx;
static void plot_input_signal(void);
static void pseudo_delay(int delay);


int32_t main(void)
{
    // Enable FPU: Enable CP10 and CP11 full access
    // Reference from function FPUEnable() of  "driverlib/fpu.h"

    //HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) &
    //                     ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
    //                    NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);
    HWREG(NVIC_CPAC) |= ((3UL << 10*2) | (3UL << 11*2));


    while(1)
    {
        plot_input_signal();
    }
}


static void plot_input_signal(void)
{
    int i;
    for (i = 0; i < HZ_5_SIG_LEN; i++)
    {
        g_idx = i;
        g_in_sig_sample = _5hz_signal[i];
        pseudo_delay(100000);

    }
}

static void pseudo_delay(int delay)
{
    int i;
    for (i = 0; i < delay; i++){}
}
