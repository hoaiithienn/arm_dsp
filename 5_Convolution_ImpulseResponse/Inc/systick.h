/*
 * systick.h
 *
 *  Created on: Aug 28, 2023
 *      Author: luong
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "arm_math.h"

void systick_counter_init(void);
uint32_t systick_get_current(void);

#endif /* INC_SYSTICK_H_ */
