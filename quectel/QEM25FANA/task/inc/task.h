/**  @file
task.h

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


#ifndef __TASK_H__
#define __TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_TICK_FREQ (1000)   // tick 的周期 1 ms 


typedef void (*task_func_t)(void *arg);

typedef struct 
{
    task_func_t func;
    void *arg;
    unsigned long last_run_tick;
    unsigned long period;
    unsigned char repeat;
    unsigned char enable;
    unsigned char init;
}task_item_t;

int task_init(void *buffer, unsigned int size);

void task_poll(void);

int task_create(task_func_t func, unsigned char repeat, unsigned long period_ms, 
        unsigned char enable, void *arg);

int task_start(int task_id);

int task_stop(int task_id);

int task_delete(int task_id);

void task_tick(void);

unsigned long task_get_tick(void);

void task_delay_ms(unsigned long ms);

void task_delay_us(unsigned long ms);


#ifdef __cplusplus
} /*"C" */
#endif

#endif //__TASK_H__
