/**  @file
control.h

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
19/02/2025			xinqiang		create
=====================================================================================*/

#ifndef __CONTROL_H__
#define __CONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif

void control_gpio_init(void);

void control_4g_wakeup_3v3(unsigned enable);

void control_acc_out(unsigned enable);

#ifdef __cplusplus
} /*"C" */
#endif

#endif // __CONTROL_H__
