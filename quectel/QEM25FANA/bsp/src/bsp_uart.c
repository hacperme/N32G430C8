/**  @file
bsp_uart.c

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
21/02/2025			修改人名		create
=====================================================================================*/


#include "bsp.h"
#include "bsp_uart.h"
#include "ring_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

static unsigned char mcu_tx_buffer[MCU_UART_TX_BUFFER_SIZE] = {0};
static unsigned char mcu_rx_buffer[MCU_UART_RX_BUFFER_SIZE] = {0};

static RB_ST mcu_tx_rb = {0};
static RB_ST mcu_rx_rb = {0};

void UART4_IRQHandler(void)
{
    unsigned char ch;
    if (USART_Interrupt_Status_Get(UART4, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        if(rb_get_free_size(&mcu_rx_rb) == 0)
        {
            /* Disable the USARTz Receive interrupt */
            USART_Interrput_Disable(UART4, USART_INT_RXDNE);
        }
        else
        {
            ch = USART_Data_Receive(UART4);
            rb_write(&mcu_rx_rb, (uint8_t *)&ch, 1, 1);
        }
    }

    if (USART_Interrupt_Status_Get(UART4, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
        if(rb_get_fill_size(&mcu_tx_rb) == 0)
        {
            /* Disable the USARTz Transmit interrupt */
            USART_Interrput_Disable(UART4, USART_INT_TXDE);
        }
        else
        {
            rb_read(&mcu_tx_rb, (uint8_t *)&ch, 1, 1);
            USART_Data_Send(UART4, ch);
        }
    }
		
    /* Determine if an error flag still exists and clear the error flag */
    if ((USART_Flag_Status_Get(UART4, USART_FLAG_OREF) != RESET)  || \
        (USART_Flag_Status_Get(UART4, USART_FLAG_NEF) != RESET)  || \
        (USART_Flag_Status_Get(UART4, USART_FLAG_PEF) != RESET)  || \
        (USART_Flag_Status_Get(UART4, USART_FLAG_FEF) != RESET))
    {
        /*Read the sts register first,and the read the DAT register to clear the all error flag*/
        (void)UART4->STS;
        (void)UART4->DAT;
        /* Under normal circumstances, all error flags will be cleared when the upper data is read and will not be executed here; 
           users can add their own processing according to the actual scenario. */
    }
}

int mcu_uart4_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    rb_init(&mcu_tx_rb, (uint8_t *)mcu_tx_buffer, sizeof(mcu_tx_buffer));
    rb_init(&mcu_rx_rb, (uint8_t *)mcu_rx_buffer, sizeof(mcu_rx_buffer));

    RCC_AHB_Peripheral_Clock_Enable(BSP_MCU_UART4_TX_CLK|BSP_MCU_UART4_RX_CLK);
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_UART4);


    NVIC_InitStructure.NVIC_IRQChannel                   = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY_1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);


    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = BSP_MCU_UART4_TX_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_UART4;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_Peripheral_Initialize(BSP_MCU_UART4_TX_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin             = BSP_MCU_UART4_RX_PIN;
    GPIO_InitStructure.GPIO_Alternate  = GPIO_AF7_UART4;
    GPIO_Peripheral_Initialize(BSP_MCU_UART4_RX_PORT, &GPIO_InitStructure);

    USART_InitStructure.BaudRate            = 921600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* init uart */
    USART_Initializes(UART4, &USART_InitStructure);

    /* Enable USARTz Receive and Transmit interrupts */
    USART_Interrput_Enable(UART4, USART_INT_RXDNE);
    USART_Interrput_Enable(UART4, USART_INT_TXDE);

    /* enable uart */
    USART_Enable(UART4);
    return 0;
}

int mcu_uart4_read(unsigned char *buffer, unsigned int len)
{
    int ret = 0;

    ret = rb_read(&mcu_rx_rb, (uint8_t *)buffer, 1, len);

    if (USART_Interrupt_Status_Get(UART4, USART_INT_RXDNE) == RESET)
    {
        USART_Interrput_Enable(UART4, USART_INT_RXDNE);
    }
    
    return ret;
}

int mcu_uart4_write(unsigned char *buffer, unsigned int len)
{
    int ret = 0;

    ret = rb_write(&mcu_tx_rb, (uint8_t *)buffer, 1, len);
    
    if (USART_Interrupt_Status_Get(UART4, USART_INT_TXDE) == RESET)
    {
        USART_Interrput_Enable(UART4, USART_INT_TXDE);
    }
    
    return ret;
}

int _write(int fd, char *ptr, int len)  
{  
    return mcu_uart4_write((unsigned char *)ptr, len);
}

#ifdef __cplusplus
} /*"C" */
#endif
