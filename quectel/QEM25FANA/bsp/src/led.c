/**  @file
led.c

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



#ifdef __cplusplus
extern "C" {
#endif

#include "led.h"

void led_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    RCC_AHB_Peripheral_Clock_Enable(BSP_LED1_CLK|BSP_LED2_CLK|BSP_LED3_CLK|BSP_LED4_CLK);
    GPIO_Structure_Initialize(&GPIO_InitStructure);

    GPIO_InitStructure.Pin          = BSP_LED1_PIN;
    /* Set pin mode to general push-pull output */
    GPIO_InitStructure.GPIO_Mode    = GPIO_MODE_OUT_PP;
    /* Set the pin drive current to 4MA*/
    GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    /* Initialize GPIO */
    GPIO_Peripheral_Initialize(BSP_LED1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = BSP_LED2_PIN;
    GPIO_Peripheral_Initialize(BSP_LED2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = BSP_LED3_PIN;
    GPIO_Peripheral_Initialize(BSP_LED3_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = BSP_LED4_PIN;
    GPIO_Peripheral_Initialize(BSP_LED4_PORT, &GPIO_InitStructure);
}

int led_set(led_id_t led, led_mode_t mode, uint32_t on_time_ms, uint32_t off_time_ms)
{
    int ret = 0;
    GPIO_Module *port;
    unsigned int pin;

    switch (led)
    {
    case LED_ID_1:
        port = BSP_LED1_PORT;
        pin = BSP_LED1_PIN;
        break;
    case LED_ID_2:
        port = BSP_LED2_PORT;
        pin = BSP_LED2_PIN;
        break;
    case LED_ID_3:
        port = BSP_LED3_PORT;
        pin = BSP_LED3_PIN;
        break;
    case LED_ID_4:
        port = BSP_LED4_PORT;
        pin = BSP_LED4_PIN;
        break;
    default:
        ret = -1;
        goto exit;
    }

    switch (mode)
    {
    case LED_MODE_OFF:
        GPIO_Pins_Reset(port, pin);
        break;
    case LED_MODE_ON:
        GPIO_Pins_Set(port, pin);
        break;
    case LED_MODE_TOGGLE:
        GPIO_Pin_Toggle(port, pin);
        break;
    default:
        ret = -1;
        break;
    }

exit:

    return ret;
}

#ifdef __cplusplus
} /*"C" */
#endif
