/**  @file
bsp_adc.c

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
19/02/2025			修改人名		create
=====================================================================================*/




#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"
#include "bsp_adc.h"

int bsp_adc_init(void)
{
    int ret = 0;
    ADC_InitType ADC_InitStructure;
    GPIO_InitType GPIO_InitStructure;


    RCC_AHB_Peripheral_Clock_Enable(BSP_BAT_NTC_ADC_CLK|BSP_BAT_ADC_CLK|RCC_AHB_PERIPH_ADC);
    /* RCC_ADCHCLK_DIV16*/
    ADC_Clock_Mode_Config(ADC_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ADC_1M_Clock_Config(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source

    GPIO_Structure_Initialize(&GPIO_InitStructure);
    /* Configure adc input as analog input -------------------------*/
    GPIO_InitStructure.Pin       = BSP_BAT_ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_Peripheral_Initialize(BSP_BAT_ADC_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin       = BSP_BAT_NTC_ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_Peripheral_Initialize(BSP_BAT_NTC_ADC_PORT, &GPIO_InitStructure);
    
    ADC_Initializes_Structure(&ADC_InitStructure);
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_1;
    ADC_Initializes(&ADC_InitStructure);
    /* Enable ADC */
    ADC_ON( );
    /* Check ADC Ready */
    while(ADC_Flag_Status_Get(ADC_RD_FLAG ,ADC_FLAG_AWDG ,ADC_FLAG_RDY) == RESET);
    /* Start ADC1 calibration */
    ADC_Calibration_Operation(ADC_CALIBRATION_ENABLE);
    /* Check the end of ADC1 calibration */
    while (ADC_Calibration_Operation(ADC_CALIBRATION_STS) == SET);


    return ret;
}

unsigned int bsp_adc_read(bsp_adc_ch_t ch)
{
    unsigned int adc_value = 0;
    uint8_t ADC_Channel;
    ADC_Channel = (ch == ADC_CH_BAT_NTC) ? (ADC_Channel_06_PA5):(ADC_Channel_07_PA6);
    ADC_Channel_Sample_Time_Config(ADC_Channel ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel, ADC_REGULAR_NUMBER_1);
    /* Start ADC Software Conversion */
    ADC_Regular_Channels_Software_Conversion_Operation(ADC_EXTRTRIG_SWSTRRCH_ENABLE);
    while(ADC_Flag_Status_Get(ADC_RUN_FLAG ,ADC_FLAG_ENDCA ,ADC_FLAG_RDY)==0)
    {
        
    }
    ADC_Flag_Status_Clear(ADC_FLAG_ENDCA);
    ADC_Flag_Status_Clear(ADC_FLAG_STR);
    adc_value = ADC_Regular_Group_Conversion_Data_Get();
    return adc_value;
}

#ifdef __cplusplus
} /*"C" */
#endif
