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

#include "bsp_iwdg.h"


int bsp_iwdg_config(uint32_t timeout_ms)
{
    int ret = 0;
    uint32_t LsiFreq = 40000; /*40kHz*/
    uint8_t prescaler = 0;
    uint32_t reload_value; 

    if((0xfff*1000/LsiFreq*4) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV4;
        reload_value = LsiFreq*timeout_ms/4/1000;
    }
    else if((0xfff*1000/LsiFreq*8) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV8;
        reload_value = LsiFreq*timeout_ms/8/1000;
    }
    else if((0xfff*1000/LsiFreq*16) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV16;
        reload_value = LsiFreq*timeout_ms/16/1000;
    }
    else if((0xfff*1000/LsiFreq*32) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV32;
        reload_value = LsiFreq*timeout_ms/32/1000;
    }
    else if((0xfff*1000/LsiFreq*64) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV64;
        reload_value = LsiFreq*timeout_ms/64/1000;
    }
    else if((0xfff*1000/LsiFreq*128) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV128;
        reload_value = LsiFreq*timeout_ms/128/1000;
    }
    else if((0xfff*1000/LsiFreq*256) >= timeout_ms)
    {
        prescaler = IWDG_CONFIG_PRESCALER_DIV256;
        reload_value = LsiFreq*timeout_ms/256/1000;
    }
    else
    {
        return -1;
    }

    // printf("prescaler:%x, reload_value:%d\r\n", prescaler, reload_value);
    if((reload_value == 0) || (reload_value > 0xfff))
    {
        return -1;
    }

    IWDG_Write_Protection_Disable();
    IWDG_Prescaler_Division_Set(prescaler);

    IWDG_Counter_Reload(reload_value);
    IWDG_Key_Reload();
    return ret;
}

void bsp_iwdg_feed(void)
{
    IWDG_Key_Reload();
}

void bsp_iwdg_ctl(unsigned char enable)
{
    if(enable)
    {
        IWDG_Enable();
    }
    else
    {
        IWDG_Freeze_Enable();
    }
}
