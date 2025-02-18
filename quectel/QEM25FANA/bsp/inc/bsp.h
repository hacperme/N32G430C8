/**  @file
bsp.h

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


#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

// GPIO 
#define BSP_4G_WAKEUP_3V3_PORT GPIOA
#define BSP_4G_WAKEUP_3V3_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_4G_WAKEUP_3V3_PIN GPIO_PIN_0

#define BSP_4G_SIG_3V3_PORT GPIOA
#define BSP_4G_SIG_3V3_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_4G_SIG_3V3_PIN GPIO_PIN_1

#define BSP_MCU_I2C2_SDA_PORT GPIOA
#define BSP_MCU_I2C2_SDA_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_MCU_I2C2_SDA_PIN GPIO_PIN_2
#define BSP_MCU_I2C2_SCL_PORT GPIOA
#define BSP_MCU_I2C2_SCL_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_MCU_I2C2_SCL_PIN GPIO_PIN_3

#define BSP_BAT_NTC_ADC_PORT GPIOA
#define BSP_BAT_NTC_ADC_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_BAT_NTC_ADC_PIN GPIO_PIN_5

#define BSP_BAT_ADC_PORT GPIOA
#define BSP_BAT_ADC_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_BAT_ADC_PIN GPIO_PIN_6

#define BSP_LED1_PORT GPIOA
#define BSP_LED1_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_LED1_PIN GPIO_PIN_7

#define BSP_LED2_PORT GPIOA
#define BSP_LED2_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_LED2_PIN GPIO_PIN_9

#define BSP_LED3_PORT GPIOA
#define BSP_LED3_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_LED3_PIN GPIO_PIN_10

#define BSP_LED4_PORT GPIOA
#define BSP_LED4_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_LED4_PIN GPIO_PIN_8

#define BSP_ACC_OUT_PORT GPIOA
#define BSP_ACC_OUT_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_ACC_OUT_PIN GPIO_PIN_11


#define BSP_COM_ACC_PORT GPIOA
#define BSP_COM_ACC_CLK RCC_AHB_PERIPH_GPIOA
#define BSP_COM_ACC_PIN GPIO_PIN_12


#define BSP_MCU_UART4_TX_PORT GPIOB
#define BSP_MCU_UART4_TX_CLK RCC_AHB_PERIPH_GPIOB
#define BSP_MCU_UART4_TX_PIN GPIO_PIN_0
#define BSP_MCU_UART4_RX_PORT GPIOB
#define BSP_MCU_UART4_RX_CLK RCC_AHB_PERIPH_GPIOB
#define BSP_MCU_UART4_RX_PIN GPIO_PIN_1

#define BSP_CHG_PSTOP_PORT GPIOB
#define BSP_CHG_PSTOP_CLK RCC_AHB_PERIPH_GPIOB
#define BSP_CHG_PSTOP_PIN GPIO_PIN_5

#define BSP_CHG_INT_PORT GPIOB
#define BSP_CHG_INT_CLK RCC_AHB_PERIPH_GPIOB
#define BSP_CHG_INT_PIN GPIO_PIN_6

#define BSP_CHG_CE_PORT GPIOB
#define BSP_CHG_CE_CLK RCC_AHB_PERIPH_GPIOB
#define BSP_CHG_CE_PIN GPIO_PIN_7

#ifdef __cplusplus
} /*"C" */
#endif

#endif //__BSP_H__
