/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//�Ҽ��������̣�ѡ��ˢ��

#include "headfile.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳���ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_uint32_t i = 0;
    rt_uint8_t *p = RT_NULL;        //�ڴ���ָ��

    while(1)
    {
        p = rt_malloc(1<<i++);      //�ڶ��������ڴ�
        if(p != RT_NULL)
        {
            rt_kprintf("get  memory : %dByte\n", 1<<i);
            rt_free(p);             //�ͷ��ڴ�
            rt_kprintf("free  memory : %dByte\n", 1<<i);
            p = RT_NULL;            //ָ�����
        }
        else
        {
            rt_kprintf("get memory : %dByte failed!!!\n",1<<i);
            return;
        }
        rt_thread_mdelay(1000);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void        ��
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int dynmem_example(void)
{
    //�����߳̿��ƿ�
    rt_thread_t tid;

    //������̬�߳�
    tid = rt_thread_create("thread1",       //�߳�����
            thread1_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            1024,                           //1024���ֽڵ�ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            5);                             //ʱ��ƬΪ5


    if(tid != RT_NULL)                      //�̴߳�����Ϊ��
    {
        rt_kprintf("create thread OK\n");
        rt_thread_startup(tid);             //���и��߳�
    }
    else                                    //�̴߳���ʧ��
    {
        rt_kprintf("create thread failed\n");
        return 0;
    }

    return 1;
}

//����FINSH������
//��������������dynmem_example ��������С�
//MSH_CMD_EXPORT(dynmem_example, dynmem example);

INIT_APP_EXPORT(dynmem_example);      //Ӧ�ó�ʼ��

int main(void)
{
    //dynmem_example();

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}



