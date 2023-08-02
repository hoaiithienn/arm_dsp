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
static float32_t signal_mean(float32_t * sig_src_arr, uint32_t sig_length);
static float32_t signal_variance(float32_t * sig_src_arr, float32_t sig_mean, uint32_t sig_length);
static float32_t signal_std(float32_t variance);
float32_t g_mean_value;
float32_t g_variance_value;
float32_t g_std_value;
float32_t g_std_cmsis_value;

int32_t main(void)
{
    // Configure system clock
    clock_init();

    // Enable FPU
    fpu_enable();

    // Configure UART0
    uart0_tx_init();

    // Calculate mean
    g_mean_value = signal_mean((float32_t *) inputSignal_f32_1kHz_15kHz, (uint32_t) KHZ1_15_SIG_LEN);
    g_variance_value = signal_variance(inputSignal_f32_1kHz_15kHz, g_mean_value, KHZ1_15_SIG_LEN);
    g_std_value = signal_std(g_variance_value);
    arm_std_f32((float32_t *) &inputSignal_f32_1kHz_15kHz[0], KHZ1_15_SIG_LEN, (float32_t *) &g_std_cmsis_value);

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

static float32_t signal_mean(float32_t * sig_src_arr, uint32_t sig_length)
{
    float32_t _mean = 0.0f;
    uint32_t i;

    for (i = 0; i < sig_length; i++)
    {
        _mean += sig_src_arr[i];
    }

    _mean = _mean / (float32_t) sig_length;

    return _mean;
}

static float32_t signal_variance(float32_t * sig_src_arr, float32_t sig_mean, uint32_t sig_length)
{
    float32_t _variance = 0.0f;
    uint32_t i;

    for (i = 0; i < sig_length; i++)
    {
        _variance += powf(sig_src_arr[i] - sig_mean, 2);
    }
    _variance = _variance / ((float32_t) sig_length - 1.0f);

    return _variance;
}

static float32_t signal_std(float32_t variance)
{
    float32_t _std = sqrt(variance);
    return _std;
}
