/**  @file
led.h

 @brief
 文件功能模块描述。
*/

/*=====================================================================================
Copyright (c) 2025 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
=====================================================================================*/

/*=====================================================================================

                        EDIT HISTORY FOR MODULE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.
WHEN				WHO			WHAT, WHERE, WHY
------------		-------		-------------------------------------------------------
18/02/2025			xinqiang		create
=====================================================================================*/


#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "bsp.h"

typedef enum
{
    LED_ID_1 = 0x01,
    LED_ID_2 = 0x01 << 1,
    LED_ID_3 = 0x01 << 2,
    LED_ID_4 = 0x01 << 3,
    LED_ID_MAX
}led_id_t;

typedef enum
{
    LED_MODE_OFF,
    LED_MODE_ON,
    LED_MODE_TOGGLE
}led_mode_t;


void led_init(void);

int led_set(led_id_t led, led_mode_t mode, uint32_t on_time_ms, uint32_t off_time_ms);


#ifdef __cplusplus
} /*"C" */
#endif

#endif // __LED_H__
