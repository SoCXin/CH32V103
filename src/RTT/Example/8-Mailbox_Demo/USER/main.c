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

//创建一个字符串
static char mb_str1[] = "i am a mail!";

//邮箱控制块的指针
static rt_mailbox_t mb;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      线程入口
//  @param      parameter   参数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    char* str;
    rt_thread_mdelay(10);                                                       //等待FINSH初始化完毕
    rt_kprintf("thread1:try to recv a mail.\n");

    if(rt_mb_recv(mb,                                                           //邮箱控制块
            (rt_uint32_t *)&str,                                                //接收邮箱的字符串
            RT_WAITING_FOREVER)                                                 //一直等待
            == RT_EOK)
    {
        rt_kprintf("thread1:get a mail from mailbox.the content :%s\n", str);   //输出接收信息
    }
    rt_mb_delete(mb);                                                           //删除邮箱
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
    rt_thread_mdelay(10);                                                       //等待FINSH初始化完毕
    rt_kprintf("thread2:try to send a mail.\n");
    rt_mb_send(mb, (rt_uint32_t)&mb_str1);                                      //发送邮箱
    rt_kprintf("\n thread2 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      邮箱创建以及启动
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int mailbox_example(void)
{
    //线程控制块指针
    rt_thread_t t1,t2;

    //创建邮箱
    mb = rt_mb_create("mb",
            4,                              //4x32个字节的变量
            RT_IPC_FLAG_FIFO                //先进先出
            );

    //创建动态线程
    t1 = rt_thread_create(
          "thread1",                        //线程名称
          thread1_entry,                    //线程入口函数
          RT_NULL,                          //线程参数
          512,                              //栈空间大小
          4,                                //设置线程优先级
          5);                               //时间片

    if(t1 != RT_NULL)                       //线程创建成功
    {
        rt_thread_startup(t1);              //运行该线程
    }

    //创建动态线程
    t2 = rt_thread_create(
            "thread2",                      //线程名称
            thread2_entry,                  //线程入口函数
            RT_NULL,                        //线程参数
            512,                            //栈空间大小
            3,                              //设置线程优先级
            5);                             //时间片

    if(t2 != RT_NULL)                       //线程创建成功
    {
        rt_thread_startup(t2);              //运行该线程
    }

    return 0;
}

//使用INIT_APP_EXPORT宏自动初始化，也可以通过在其他线程内调用mailbox_example函数进行初始化
INIT_APP_EXPORT(mailbox_example);           //应用初始化

int main(void)
{
    //使用前需要在Libraries\rtthread_libraries\bsp\rtconfig.h中打开RT_USING_MUTEX宏定义

    //此处编写用户代码(例如：外设初始化代码等)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}

