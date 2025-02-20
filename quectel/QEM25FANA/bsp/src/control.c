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


void EXTI1_IRQHandler(void)
{
    if (RESET != EXTI_Interrupt_Status_Get(EXTI_LINE1))
    {
        EXTI_Interrupt_Status_Clear(EXTI_LINE1);
        // printf("EXTI1 init, state:%d\r\n", GPIO_Input_Pin_Data_Get(BSP_4G_SIG_3V3_PORT, BSP_4G_SIG_3V3_PIN));
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (RESET != EXTI_Interrupt_Status_Get(EXTI_LINE12))
    {
        EXTI_Interrupt_Status_Clear(EXTI_LINE12);
        // printf("EXTI12 init, state:%d\r\n", GPIO_Input_Pin_Data_Get(BSP_COM_ACC_PORT, BSP_COM_ACC_PIN));
    }
}

void control_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    RCC_AHB_Peripheral_Clock_Enable(BSP_4G_WAKEUP_3V3_CLK|BSP_ACC_OUT_CLK);
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO);

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

    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = BSP_4G_SIG_3V3_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_PULL_UP;
    GPIO_Peripheral_Initialize(BSP_4G_SIG_3V3_PORT, &GPIO_InitStructure);

    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = BSP_COM_ACC_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_PULL_UP;
    GPIO_Peripheral_Initialize(BSP_COM_ACC_PORT, &GPIO_InitStructure);

    GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE1, AFIO_EXTI_PA1);
    GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE12, AFIO_EXTI_PA12);

    EXTI_Structure_Initializes(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE_1;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line    = EXTI_LINE_12;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);

    /* Set key input interrupt priority */
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY_1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY_1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);
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
