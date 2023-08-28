#include <math.h>
#include <stdbool.h>
#include "arm_math.h"
#include "signals.h"

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

#include "uart.h"
#include "uartstdio.h"
#include "systick.h"
#include "driverlib/sysctl.h"

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t inputSignal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN];
extern float32_t impulse_response[IMPULSE_RSP_LEN];
extern float32_t outputSignal_f32_1kHz_15kHz[OUTPUT_KHZ1_15_SIG_LEN];
extern float32_t outputSignal_f32_1kHz_15kHz_CMSIS[OUTPUT_KHZ1_15_SIG_LEN];

arm_status status;

static void pseudo_delay(int delay);
static void fpu_enable(void);
static void convolution(float32_t * src, float32_t * dst, float32_t * imp_rsp, uint32_t src_len, uint32_t imp_rsp_len);
static void convolution_CMSIS(float32_t * src, float32_t * dst, float32_t * imp_rsp, uint32_t src_len, uint32_t imp_rsp_len);

uint32_t g_before = 0;
uint32_t g_after  = 0;
float32_t g_duration1 = 0;
float32_t g_duration2 = 0;
uint32_t clock_speed;
float32_t single_circle;

int32_t main(void)
{
    // Configure system clock
    clock_init();
    clock_speed = SysCtlClockGet();
    single_circle = 1/ ((float32_t) clock_speed);

    // Enable FPU
    fpu_enable();

    // Configure UART0
    uart0_tx_init();

    // Configure systick
    systick_counter_init();



    // Convolution
    // Method 1: By definition: took 25.0747502 ms
    g_before = systick_get_current();
    convolution(inputSignal_f32_1kHz_15kHz, outputSignal_f32_1kHz_15kHz, impulse_response, KHZ1_15_SIG_LEN, IMPULSE_RSP_LEN);
    g_after = systick_get_current();
    g_duration1 = (g_before - g_after)*single_circle;

    // Method 2: By CMSIS: took 3.18968738 ms
    g_before = systick_get_current();
    convolution_CMSIS(inputSignal_f32_1kHz_15kHz, outputSignal_f32_1kHz_15kHz_CMSIS, impulse_response, KHZ1_15_SIG_LEN, IMPULSE_RSP_LEN);
    g_after = systick_get_current();
    g_duration2 = (g_before - g_after)*single_circle;




    // Verification
    int i;
    for (i = 0; i < OUTPUT_KHZ1_15_SIG_LEN; i++)
    {
        if (outputSignal_f32_1kHz_15kHz[i] != outputSignal_f32_1kHz_15kHz_CMSIS[i])
        {
            while(1);
        }
    }


    while(1)
    {
        for (i = 0; i < OUTPUT_KHZ1_15_SIG_LEN; i++)
        {
            if (i < KHZ1_15_SIG_LEN)
            {
                UARTprintf("%d,%d,%d\r\n", (int32_t) (inputSignal_f32_1kHz_15kHz[i] * 10000),  (int32_t) (outputSignal_f32_1kHz_15kHz[i] * 10000 - 5000),  (int32_t) (outputSignal_f32_1kHz_15kHz_CMSIS[i] * 10000 - 10000));
            } else {
                UARTprintf("0,%d,%d\r\n", (int32_t) (outputSignal_f32_1kHz_15kHz[i] * 10000  - 5000),  (int32_t) (outputSignal_f32_1kHz_15kHz_CMSIS[i] * 10000  - 10000));
            }
            //UARTprintf("%d\r\n", (int32_t) (outputSignal_f32_1kHz_15kHz[i] * 10000));

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

static void convolution(float32_t * src, float32_t * dst, float32_t * imp_rsp, uint32_t src_len, uint32_t imp_rsp_len)
{
    uint32_t i,j;
    uint32_t dst_len = src_len + imp_rsp_len - 1;

    // Clear buffer
    for ( i = 0; i < dst_len; i++)
    {
        dst[i] = 0;
    }

    // Perform convolution
    for ( i = 0; i < src_len; i++)
    {
        for ( j = 0; j < imp_rsp_len; j++)
        {
            dst[i+j] = dst[i+j] + src[i] * imp_rsp[j];
        }
    }

}

static void convolution_CMSIS(float32_t * src, float32_t * dst, float32_t * imp_rsp, uint32_t src_len, uint32_t imp_rsp_len)
{
    uint32_t i;
    uint32_t dst_len = src_len + imp_rsp_len - 1;

    // Clear buffer
    for ( i = 0; i < dst_len; i++)
    {
        dst[i] = 0;
    }

    // Perform convolution
    arm_conv_f32(src, src_len, imp_rsp, imp_rsp_len, dst);
}
