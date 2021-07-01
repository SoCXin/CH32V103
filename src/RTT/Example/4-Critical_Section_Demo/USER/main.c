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


static rt_uint32_t count = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程1入口函数
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_thread_mdelay(10);           //等待FINSH初始化完毕
    while(1)
    {

        rt_enter_critical();        //调度器上锁，上锁后将不再切换到其他线程，仅响应中断
        //以下进入临界区
        count += 10;                //计数值+10
        rt_exit_critical();         //调度器解锁

        rt_kprintf("thread = %d , count = %d\n", 10, count);
        rt_thread_mdelay(1000);
        if(count >= 100)
        {
            break;
        }
    }
    rt_kprintf("\n thread1 exit!\n");
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程2入口函数
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *parameter)
{
    rt_thread_mdelay(10);           //等待FINSH初始化完毕
    while(1)
    {

        rt_enter_critical();        //调度器上锁，上锁后将不再切换到其他线程，仅响应中断
        //以下进入临界区
        count += 20;                //计数值+20
        rt_exit_critical();         //调度器解锁

        rt_kprintf("thread = %d , count = %d\n", 20, count);
        rt_thread_mdelay(2000);
        if(count >= 100)
        {
            break;
        }
    }
    rt_kprintf("\n thread2 exit!\n");
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程创建以及启动
//  @param      void        空
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int critical_section_example(void)
{
    //线程控制块指针
    rt_thread_t tid;
    //创建动态线程
    tid = rt_thread_create("thread_10",     //线程名称
            thread1_entry,                  //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间
            5,                              //线程优先级为5，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            10);                            //时间片
    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_thread_startup(tid);             //运行该线程
    }

    tid = rt_thread_create("thread_20",     //线程名称
            thread2_entry,                  //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间
            3,                              //线程优先级为3，数值越小，优先级越高，0为最高优先级。
                                            //可以通过修改rt_config.h中的RT_THREAD_PRIORITY_MAX宏定义(默认值为8)来修改最大支持的优先级
            10);                            //时间片
    if(tid != RT_NULL)                      //线程创建成功
    {
        rt_thread_startup(tid);             //运行该线程
    }


    return 0;
}

//使用INIT_APP_EXPORT宏自动初始化，也可以通过在其他线程内调用critical_section_example函数进行初始化
INIT_APP_EXPORT(critical_section_example);      //应用初始化

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



