/**  @file
bsp_iwdg.h

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
20/02/2025			修改人名		create
=====================================================================================*/

#ifndef __BSP_IWDG_H__
#define __BSP_IWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "n32g430.h"

#define BSP_DEFALUT_IWDG_TIMEOUT_MS (10*1000)

int bsp_iwdg_config(uint32_t timeout_ms);

void bsp_iwdg_feed(void);

void bsp_iwdg_ctl(unsigned char enable);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_IWDG_H__ */
