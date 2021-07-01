#include "buzzer.h"
#include "button.h"

//���尴������
#define KEY1    B2
#define KEY2    B4
#define KEY3    B5

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;

//�����ź���
rt_sem_t key1_sem;
rt_sem_t key2_sem;
rt_sem_t key3_sem;

void button_entry(void *parameter)
{

    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    
    //��ȡ��ǰ����״̬
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);
    
    //��⵽��������֮�󲢷ſ� �ͷ�һ���ź���
    if(key1_status && !key1_last_status)    
    {
        rt_sem_release(key1_sem);
        rt_mb_send(buzzer_mailbox, 100);
    }
    if(key2_status && !key2_last_status)    
    {
        rt_sem_release(key2_sem);
        rt_mb_send(buzzer_mailbox, 300);
    }
    if(key3_status && !key3_last_status)    
    {
        rt_sem_release(key3_sem);
        rt_mb_send(buzzer_mailbox, 600);
    }
    
    
}

void button_init(void)
{
    rt_timer_t timer1;
    
    gpio_init(KEY1, GPI, 0, GPIO_INT_CONFIG);
    gpio_init(KEY2, GPI, 0, GPIO_INT_CONFIG);
    gpio_init(KEY3, GPI, 0, GPIO_INT_CONFIG);
    
    
    key1_sem = rt_sem_create("key1", 0, RT_IPC_FLAG_FIFO);  //�����������ź��������������¾��ͷ��ź���������Ҫʹ�ð����ĵط���ȡ�ź�������
    key2_sem = rt_sem_create("key2", 0, RT_IPC_FLAG_FIFO);  
    key3_sem = rt_sem_create("key3", 0, RT_IPC_FLAG_FIFO);  
    
    timer1 = rt_timer_create("button", button_entry, RT_NULL, 20, RT_TIMER_FLAG_PERIODIC);

    if(RT_NULL != timer1) 
    {
        rt_timer_start(timer1);
    }
}
