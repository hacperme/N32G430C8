/**  @file
task.c

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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "bsp.h"

static struct 
{
    unsigned long tick;
    task_item_t *task;
    unsigned int task_size;
    unsigned int task_num;
}g;


static void SysTick_Init(uint32_t NUM)
{
    /* SystemCoreClock / NUM */
    if (SysTick_Config(SystemClockFrequency / NUM))
    {
        while (1);
    }
}


int task_init(void *buffer, unsigned int size)
{
    int ret = 0;
    if(buffer == NULL)
    {
        return -1;
    }
    memset(buffer, 0, size);
    g.task_size = size/sizeof(task_item_t);
    g.task = (task_item_t *)buffer;
    SysTick_Init(TASK_TICK_FREQ);
    return ret;
}

void task_poll(void)
{
    for (size_t i = 0; i < g.task_size; i++)
    {
        if (g.task[i].init)
        {
            if(g.task[i].enable && ((g.tick - g.task[i].last_run_tick) >= g.task[i].period))
            {
                
                g.task[i].func(g.task[i].arg);
                if(g.task[i].repeat == 1)
                {
                    g.task[i].last_run_tick = g.tick;
                }
                else
                {
                    memset(&g.task[i], 0, sizeof(task_item_t));
                    g.task_num--;
                }
            }
        }
    }
}

int task_create(task_func_t func, unsigned char repeat, unsigned long period_ms, unsigned char enable, void *arg)
{
    int ret = 0;
    task_item_t *task = NULL;

    for (size_t i = 0; i < g.task_size; i++)
    {
        if (g.task[i].init == 0)
        {
            task = &g.task[i];
            ret = i;
            break;
        }
        
    }

    if(task == NULL)
    {
        return -1;
    }
    
    task->arg = arg;
    task->func = func;
    task->period = period_ms;
    task->last_run_tick = g.tick;
    task->enable = enable;
    task->repeat = repeat;
    task->init = 1;

    g.task_num++;

    return ret;
}

int task_start(int task_id)
{
    if(task_id < g.task_size)
    {
        if(g.task[task_id].init)
        {
            g.task[task_id].enable = 1;
            return 0;
        }
    }

    return -1;
}

int task_stop(int task_id)
{
    if(task_id < g.task_size)
    {
        if(g.task[task_id].init)
        {
            g.task[task_id].enable = 0;
            return 0;
        }
    }
    return -1;
}

int task_delete(int task_id)
{
    if(task_id < g.task_size)
    {
        if(g.task[task_id].init)
        {
            memset(&g.task[task_id], 0, sizeof(task_item_t));
            g.task_num--;
        }
    }
    return 0;
}

void task_tick(void)
{
    g.tick++;
}

unsigned long task_get_tick(void)
{
    return g.tick;
}

void task_delay_ms(unsigned long ms)
{
    unsigned long tick = g.tick;
    tick += ms;
    while (g.tick < tick)
    {
        /* code */
    }
}

void task_delay_us(unsigned long us)
{
    uint32_t i;
    RCC_ClocksType RCC_Clocks;

    SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
    RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks);
    SysTick_Init(1000000);

    for(i=0;i<us;i++)
    {
        /* When the counter value decreases to 0, bit 16 of the CRTL register will be set to 1 */
        /* When set to 1, reading this bit will clear it to 0 */
        while( !((SysTick->CTRL)&(1<<16)) );
    }
    /* Turn off the SysTick timer */
    SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;

    SysTick_Init(TASK_TICK_FREQ);
}

#ifdef __cplusplus
} /*"C" */
#endif
