/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
 * @version         查看doc内version文件 版本说明
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//整套推荐IO查看Projecct文件夹下的TXT文本

//打开新的工程或者工程移动了位置务必执行以下操作
//右键单击工程，选择刷新

#include "headfile.h"

#define EVENT_FLAG3 (1<<3)
#define EVENT_FLAG5 (1<<5)

//事件控制块指针
rt_event_t event;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程入口
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_uint32_t e;
    rt_thread_mdelay(10);           //等待FINSH初始化完毕
    if(rt_event_recv
            (event,                                     //事件控制块
            (EVENT_FLAG3 | EVENT_FLAG5),                //事件标志3和事件标志5
            (RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR),  //事件与触发，接收完成后清除事件标志位
            RT_WAITING_FOREVER,                         //一直等待
            &e) == RT_EOK)
    {
        rt_kprintf("thread1: AND recv event 0x%x\n", e);
    }
    rt_kprintf("\n thread1 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程入口
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *parameter)
{
    rt_thread_mdelay(10);           //等待FINSH初始化完毕

    rt_kprintf("thread2: send event3\n");
    rt_event_send(event, EVENT_FLAG3);
    rt_thread_mdelay(200);

    rt_kprintf("thread2: send event5\n");
    rt_event_send(event, EVENT_FLAG5);
    rt_thread_mdelay(200);

    rt_kprintf("\n thread2 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程创建以及启动
//  @param      void        空
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int event_example(void)
{
    //线程控制块指针
    rt_thread_t tid;

    //创建事件
    event = rt_event_create("event", RT_IPC_FLAG_FIFO);

    //创建动态线程
    tid = rt_thread_create("thread1",       //线程名称
            thread1_entry,                  //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间
            5,                              //线程优先级为5，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            5);                             //时间片为5

    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_kprintf("create thread1 OK\n");
        //运行该线程
        rt_thread_startup(tid);
    }

    //创建动态线程
    tid = rt_thread_create("thread2",       //线程名称
            thread2_entry,                  //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间
            5,                              //线程优先级为5，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            5);                             //时间片为5

    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_kprintf("create thread2 OK\n");
        //运行该线程
        rt_thread_startup(tid);
    }

    return 1;
}

//使用INIT_APP_EXPORT宏自动初始化，也可以通过在其他线程内调用event_example函数进行初始化
INIT_APP_EXPORT(event_example);      //应用初始化

int main(void)
{
    //使用前需要在Libraries\rtthread_libraries\bsp\rtconfig.h中打开 RT_USING_EVENT宏定义

    //此处编写用户代码(例如：外设初始化代码等)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}



