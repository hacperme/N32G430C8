/**  @file
bsp_uart.h

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
21/02/2025			xinqiang		create
=====================================================================================*/


#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MCU_UART_TX_BUFFER_SIZE (256)
#define MCU_UART_RX_BUFFER_SIZE (512)


int mcu_uart4_init(void);

int mcu_uart4_read(unsigned char *buffer, unsigned int len);

int mcu_uart4_write(unsigned char *buffer, unsigned int len);

#ifdef __cplusplus
} /*"C" */
#endif
#endif // __BSP_UART_H__
