/**  @file
control.c

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




#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"
#include "control.h"

void control_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    RCC_AHB_Peripheral_Clock_Enable(BSP_4G_WAKEUP_3V3_CLK|BSP_ACC_OUT_CLK);
    GPIO_Structure_Initialize(&GPIO_InitStructure);

    GPIO_InitStructure.Pin          = BSP_4G_WAKEUP_3V3_PIN;
    /* Set pin mode to general push-pull output */
    GPIO_InitStructure.GPIO_Mode    = GPIO_MODE_OUT_PP;
    /* Set the pin drive current to 4MA*/
    GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    /* Initialize GPIO */
    GPIO_Peripheral_Initialize(BSP_4G_WAKEUP_3V3_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.Pin          = BSP_ACC_OUT_PIN;
    GPIO_Peripheral_Initialize(BSP_ACC_OUT_PORT, &GPIO_InitStructure);
}

void control_4g_wakeup_3v3(unsigned enable)
{
    if(enable)
    {
        GPIO_Pins_Set(BSP_4G_WAKEUP_3V3_PORT, BSP_4G_WAKEUP_3V3_PIN);
    }
    else
    {
        GPIO_Pins_Reset(BSP_4G_WAKEUP_3V3_PORT, BSP_4G_WAKEUP_3V3_PIN);
    }
}

void control_acc_out(unsigned enable)
{
    if(enable)
    {
        GPIO_Pins_Set(BSP_ACC_OUT_PORT, BSP_ACC_OUT_PIN);
    }
    else
    {
        GPIO_Pins_Reset(BSP_ACC_OUT_PORT, BSP_ACC_OUT_PIN);
    }
}

#ifdef __cplusplus
} /*"C" */
#endif
