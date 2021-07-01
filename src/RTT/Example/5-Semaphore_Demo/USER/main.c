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

//信号量控制块指针
static rt_sem_t dynamic_sem = RT_NULL;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      释放信号量线程入口函数
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void release_semaphore_thread_entry(void *parameter)
{
    static rt_uint16_t num = 0;
    //线程控制块指针
    rt_thread_t tid = rt_thread_find("get_semaphore");
    rt_thread_mdelay(10);           //等待FINSH初始化完毕
    while(1)
    {
        if(num++ < 10)
        {
            rt_kprintf("\n release_semaphore_thread_entry release a semaphore. \n");
            rt_sem_release(dynamic_sem);            //释放信号量
            rt_thread_mdelay(1000);                 //延时1000ms，并让出CPU使用权
        }
        else
        {
            rt_sem_delete(dynamic_sem);             //删除信号量
            rt_kprintf("\n delete dynamic_sem!\n");

            rt_thread_delete(tid);                  //删除线程1
            rt_kprintf("\n delete get_semaphore_thread\n");

            break;
        }
    }
    rt_kprintf("\n release_semaphore exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取信号量线程入口函数
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void get_semaphore_thread_entry(void *parameter)
{
    static rt_err_t result;
    static rt_uint8_t sum = 0;
    rt_thread_mdelay(10);           //等待FINSH初始化完毕
    while(1)
    {
        /* 通过永久等待的方式获取信号量，获取到了则执行sum++的操作*/
        result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);

        if(result == RT_EOK)    //获取信号量成功
        {
            sum++;
            rt_kprintf("\n get_semaphore_thread_entry take a semaphore. sum semaphore = %d \n", sum);
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      程创建以及启动
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int semaphore_example(void)
{
    //创建信号量
    dynamic_sem = rt_sem_create("dynamic_semaphore", 0 ,RT_IPC_FLAG_FIFO);

    //线程控制块指针
    rt_thread_t tid;
    //创建动态线程
    tid = rt_thread_create(
            "release_semaphore",            //线程名称
            release_semaphore_thread_entry, //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间大小
            4,                              //设置线程优先级，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            10);                            //时间片

    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_thread_startup(tid);             //运行该线程
    }

    tid = rt_thread_create(
            "get_semaphore",                //线程名称
            get_semaphore_thread_entry,     //线程入口函数
            RT_NULL,                        //线程参数
            512,                           //栈空间大小
            3,                              //设置线程优先级，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            10);                            //时间片

    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_thread_startup(tid);             //运行该线程
    }


    return 0;
}


//使用INIT_APP_EXPORT宏自动初始化，也可以通过在其他线程内调用semaphore_example函数进行初始化
INIT_APP_EXPORT(semaphore_example);      //应用初始化

int main(void)
{
    //此处编写用户代码(例如：外设初始化代码等)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);

    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}



