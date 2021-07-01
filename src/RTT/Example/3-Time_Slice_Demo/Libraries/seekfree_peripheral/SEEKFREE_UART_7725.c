/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            С���
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        IAR 8.3 or MDK 5.28
 * @Taobao          https://seekfree.taobao.com/
 * @date            2019-02-18
 * @note
                                        ���߶��壺
                    ------------------------------------
                                                ģ��ܽ�                          ��Ƭ���ܽ�
                        SDA(51��RX)         �鿴SEEKFREE_UART_7725.h�ļ��е�OV7725_UART_COF_UART_TX�궨��
                        SCL(51��TX)         �鿴SEEKFREE_UART_7725.h�ļ��е�OV7725_UART_COF_UART_RX�궨��
                                                ���ж�(VSY)          �鿴SEEKFREE_UART_7725.h�ļ��е�OV7725_UART_VSYNC_PIN�궨��
                                                ���ж�(HREF)         ����
                                                �����ж�(PCLK)       �鿴SEEKFREE_UART_7725.h�ļ��е�OV7725_UART_PCLK�궨��
                                                ���ݿ�(D0-D7)        �鿴SEEKFREE_UART_7725.h�ļ��е�OV7725_UART_DATA_PIN�궨��
                    ------------------------------------

                                                Ĭ�Ϸֱ�����                    160*120
                                                Ĭ��FPS              50֡
 ********************************************************************************************************************/

#include "zf_systick.h"
#include "zf_uart.h"
#include "zf_gpio.h"
#include "zf_nvic.h"
#include "zf_camera.h"

#include "SEEKFREE_UART_7725.h"

uint8 ov7725_uart_image_bin[OV7725_UART_W/8][OV7725_UART_H];
//uint8 ov7725_uart_image_dec[OV7725_UART_H][OV7725_UART_W];


uint16 OV7725_CFG[OV7725_CONFIG_FINISH][2]=
{
    {OV7725_RESERVE,           0},
    {OV7725_CONTRAST,       0x30},
    {OV7725_FPS,              50},
    {OV7725_COL,   OV7725_UART_W},
    {OV7725_ROW,   OV7725_UART_H},

    {OV7725_INIT,              0}
};


uint16 OV7725_GET_CFG[OV7725_CONFIG_FINISH-1][2]=
{
    {OV7725_RESERVE,           0},
    {OV7725_CONTRAST,          0},
    {OV7725_FPS,               0},
    {OV7725_COL,               0},
    {OV7725_ROW,               0}
};

uint8   ov7725_uart_receive[3];
uint8   ov7725_uart_receive_num = 0;
uint8   ov7725_uart_receive_flag = 0;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ�����жϺ���
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �ú�����ISR�ļ� ����3�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------

void ov7725_cof_uart_interrupt(void)
{
    uart_query(OV7725_UART_COF_UART, &ov7725_uart_receive[ov7725_uart_receive_num]);
    ov7725_uart_receive_num++;

    if(1==ov7725_uart_receive_num && 0XA5!=ov7725_uart_receive[0])  ov7725_uart_receive_num = 0;
    if(3 == ov7725_uart_receive_num)
    {
        ov7725_uart_receive_num = 0;
        ov7725_uart_receive_flag = 1;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ���ж�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:                   ��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
//-------------------------------------------------------------------------------------------------------------------

void ov7725_uart_vsync(void)
{
    OV7725_UART_DMA_CH->CNTR = OV7725_UART_SIZE;             //���õ�ǰDMA�����ʣ�����������µݼ����üĴ���ֻ����DMA������ʱ���ġ�
    OV7725_UART_DMA_CH->CFGR |= DMA_CFGR1_EN;                //����DMA1
}

uint8 ov7725_uart_finish_flag = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷDMA����ж�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:                   ��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_dma(void)
{
    ov7725_uart_finish_flag = 1;                             //����ͷ���ݲɼ���1
    OV7725_UART_DMA_CH->CFGR &= (uint16)(~DMA_CFGR1_EN);     //�ر�DMA1
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷDMA��ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_dma_init(void)
{
    uint8 data_pin,num;

    //����ͷ�������ų�ʼ��
    data_pin = (uint8)(((OV7725_UART_DATA_PIN - (GPIOA_BASE+8)) >> 10) << 5) +
                (((OV7725_UART_DATA_PIN - (GPIOA_BASE+8)) & 0x0F) << 3);

    for(num=7; num>0; num--)
    {
        gpio_init((PIN_enum)(num + data_pin), GPI, 0, IN_FLOAT);
    }


 	//DMA����ͷ��ʼ��
 	camera_dma_init(OV7725_UART_DMA_CH,(uint32)OV7725_UART_DATA_PIN, (uint32)camera_buffer_addr, OV7725_UART_SIZE);
    nvic_init(OV7725_UART_DMA_IRQN, 0, 0, ENABLE);          //�ж�����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ��ʱ�����񴥷���ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_tim1_etr_init(void)
{
    camera_tim_etr_init(TIMER_1, OV7725_UART_PCLK);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ���жϳ�ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_vsync_init(void)
{   
    gpio_interrupt_init(OV7725_UART_VSYNC_PIN, FALLING, IN_PULLUP);
    nvic_init(OV7725_UART_VSYNC_IRQN, 1, 0, ENABLE);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      С��������ͷ�ڲ��Ĵ�������д����
//  @param      uartn   ����ͷ�ڲ��Ĵ�����ַ
//  @param      buff    ��Ҫд�������
//  @return     void
//  @since      v1.0
//  Sample usage:       ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void ov7725_set_all_config(UARTN_enum uartn, uint16 buff[OV7725_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];

    ov7725_uart_receive_flag = 0;

    for(i=0; i<OV7725_CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = buff[i][0];
        temp           = buff[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;

        uart_putbuff(uartn, send_buffer, 4);
        systick_delay_ms(10);
    }


    while(!ov7725_uart_receive_flag)    systick_delay_ms(1);
    ov7725_uart_receive_flag = 0;
    while((0xff != ov7725_uart_receive[1]) || (0xff != ov7725_uart_receive[2]))systick_delay_ms(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С����ȡ����ͷ�ڲ�������Ϣ
//  @param      uartn   ����ͷ����
//  @param      buff    ��Ҫ��ȡ������
//  @return     void
//  @since      v1.0
//  Sample usage:       ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void ov7725_get_all_config(UARTN_enum uartn, uint16 buff[OV7725_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];

    for(i=0; i<OV7725_CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = OV7725_GET_STATUS;
        temp           = buff[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;

        uart_putbuff(uartn, send_buffer,4);

        systick_delay_ms(10);

        while(!ov7725_uart_receive_flag)    systick_delay_ms(1);

        ov7725_uart_receive_flag = 0;

        buff[i][1] = ov7725_uart_receive[1]<<8 | ov7725_uart_receive[2];
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�̼��汾
//  @param      uartn               ѡ��ʹ�õĴ���
//  @return     (uint16)camera_id   ��������ͷID
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������ͷ���ô���
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_uart_get_id(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = OV7725_GET_WHO_AM_I;
    temp           = 0;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;

    uart_putbuff(uartn, send_buffer, 4);

    while(!ov7725_uart_receive_flag)    systick_delay_ms(1);
    ov7725_uart_receive_flag = 0;

    return ((uint16)(ov7725_uart_receive[1]<<8) | ov7725_uart_receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�̼��汾
//  @param      uartn       ѡ��ʹ�õĴ���
//  @return     uint16      �汾��
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������ͷ���ô���
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_get_version(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = OV7725_GET_STATUS;
    temp           = OV7725_GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;

    uart_putbuff(uartn, send_buffer, 4);

    while(!ov7725_uart_receive_flag)    systick_delay_ms(1);
    ov7725_uart_receive_flag = 0;

    return ((uint16)(ov7725_uart_receive[1]<<8) | ov7725_uart_receive[2]);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �°�С����ʼ��
//  @return     uint8       ��ʼ�����
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 ov7725_uart_init(void)
{
    camera_type = CAMERA_BIN_UART;//������������ͷ����
    camera_buffer_addr = ov7725_uart_image_bin[0];
    uart_init(OV7725_UART_COF_UART, 9600, OV7725_UART_COF_UART_TX, OV7725_UART_COF_UART_RX);
    uart_rx_irq(OV7725_UART_COF_UART, ENABLE);

    //EnableGlobalIRQ(0);

    //�������в���
    ov7725_uart_receive_flag = 0;
    ov7725_set_all_config(OV7725_UART_COF_UART, OV7725_CFG);
    //��ȡ���в���
    ov7725_uart_receive_flag = 0;
    ov7725_get_all_config(OV7725_UART_COF_UART, OV7725_GET_CFG);

    //DisableGlobalIRQ();

    //DMA��ʼ��
    ov7725_uart_dma_init();
    //GPIO������ʱ����ʼ��,PLCK���ų�ʼ��
    ov7725_uart_tim1_etr_init();
    //VSYNC��ʼ��
    ov7725_uart_vsync_init();

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷδ��ѹͼ��������λ���鿴ͼ��
//  @param      *imgaddr            ѹ��ͼ�����ݵ�ַ
//  @param      *imgsize            ͼ���С(ֱ����дOV7725_UART_SIZE)
//  @return     void
//  @since      v1.0
//  Sample usage:                   ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_7725(UARTN_enum uartn, void *imgaddr, uint32 imgsize)
{
    uint32 i;
    uart_putchar(uartn,0x00);
    uart_putchar(uartn,0xff);
    uart_putchar(uartn,0x01);
    uart_putchar(uartn,0x01);
    for(i=0; i<(imgsize); i++)
    {
        uart_putchar(uartn,((uint8 *)(imgaddr))[i]);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ���ݽ�ѹ����
//  @param      *data1              Դ��ַ
//  @param      *data2              Ŀ�ĵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:                   Image_Decompression(da1,dat2[0]);//��һά����dat1�����ݽ�ѹ����ά����dat2��.
//-------------------------------------------------------------------------------------------------------------------
void Image_Decompression(uint8 *data1,uint8 *data2)
{
    uint8  temp[2] = {0,255};
    uint16 lenth = OV7725_UART_SIZE;
    uint8  i = 8;


    while(lenth--)
    {
        i = 8;
        while(i--)
        {
            *data2++ = temp[(*data1 >> i) & 0x01];
        }
        data1++;
    }
}






