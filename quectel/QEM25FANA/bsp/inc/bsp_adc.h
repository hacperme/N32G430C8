/**  @file
bsp_adc.h

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


#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    ADC_CH_BAT_NTC, /* 电池 NTC */
    ADC_CH_BAT      /* 电池电压 */
}bsp_adc_ch_t;


int bsp_adc_init(void);

unsigned int bsp_adc_read(bsp_adc_ch_t ch);

#ifdef __cplusplus
} /*"C" */
#endif

#endif // __ADC_H__
