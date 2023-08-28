/*
 * systick.c
 *
 *  Created on: Aug 28, 2023
 *      Author: luong
 */

#include "systick.h"
#include "inc/hw_types.h"

#define SYSTICK_CTRL      0xE000E010
#define SYSTICK_RELOAD    0xE000E014
#define SYSTICK_CURRENT   0xE000E018
#define SYSTICK_CLOCK_SRC (1U << 2)
#define SYSTICK_ENABLE    (1U << 0)


void systick_counter_init(void)
{
    // Disable and reset systick control register before config
    HWREG(SYSTICK_CTRL) = 0;

    // Load systick reload register value with the maximum value
    HWREG(SYSTICK_RELOAD) = 0x00FFFFFF;

    // Clear systick current value
    HWREG(SYSTICK_CURRENT) = 0;

    // Select internal clock source
    HWREG(SYSTICK_CTRL) |= SYSTICK_CLOCK_SRC;

    // Enable systick
    HWREG(SYSTICK_CTRL) |= SYSTICK_ENABLE;
}

uint32_t systick_get_current(void)
{
    return (HWREG(SYSTICK_CURRENT));
}
