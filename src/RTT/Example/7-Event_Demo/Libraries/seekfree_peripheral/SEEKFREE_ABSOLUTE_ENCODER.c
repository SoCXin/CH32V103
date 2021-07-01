/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            ����ʽ������
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴LPC546XX_config.h�ļ��ڰ汾�궨��
 * @Software        IAR 8.3 or MDK 5.24a
 * @Target core     LPC54606J512BD100
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-01-13
 * @note
                    ���߶��壺
                    ------------------------------------
                    ģ��ܽ�                                    ��Ƭ���ܽ�
                    SCK                          �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_SCK_PIN �궨��
                    MISO                         �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_MISO_PIN�궨��
                    MOSI                 �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_MOSI_PIN�궨��
                    CS                   �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_PCS_PIN  �궨��
                    ------------------------------------
 ********************************************************************************************************************/

#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "zf_systick.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͨ��SPIдһ��byte,ͬʱ��ȡһ��byte
//  @param      byte        ���͵�����    
//  @return     uint8       return ����status״̬
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_wr_byte(uint8 byte)
{
    spi_mosi(ABS_ENCODER_SPI_NUM, &byte, &byte, 1);
    return(byte);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��valд��cmd��Ӧ�ļĴ�����ַ,ͬʱ����status�ֽ�
//  @param      cmd         ������
//  @param      val         ��д��Ĵ�������ֵ
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void spi_w_reg_byte(uint8 cmd, uint8 val, PIN_enum cs_pin)
{
    GPIO_PIN_RESET(cs_pin);
    cmd |= ABS_ENCODER_SPI_W;
    spi_wr_byte(cmd);
    spi_wr_byte(val);
    GPIO_PIN_SET(cs_pin);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡcmd����Ӧ�ļĴ�����ַ
//  @param      cmd         ������
//  @param      *val        �洢��ȡ�����ݵ�ַ
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void spi_r_reg_byte(uint8 cmd, uint8 *val, PIN_enum cs_pin)
{
    GPIO_PIN_RESET(cs_pin);
    cmd |= ABS_ENCODER_SPI_R;
    spi_wr_byte(cmd);
    *val = spi_wr_byte(0);
    GPIO_PIN_SET(cs_pin);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      д��һ�����ݵ��������ļĴ���
//  @param      cmd         �Ĵ�����ַ
//  @param      *val        д�����ݵĵ�ַ
//  @return     uint8       0������  1��ʧ��
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 encoder_spi_w_reg_byte(uint8 cmd, uint8 val, PIN_enum cs_pin)
{
    uint8 dat;
    GPIO_PIN_RESET(cs_pin);
    cmd |= ABS_ENCODER_SPI_W;
    spi_wr_byte(cmd);
    spi_wr_byte(val);
    GPIO_PIN_SET(cs_pin);
    systick_delay_us(1);
    GPIO_PIN_RESET(cs_pin);
    dat = spi_wr_byte(0x00);
    spi_wr_byte(0x00);
    GPIO_PIN_SET(cs_pin);
    
    if(val != dat)  return 1;   //д��ʧ��
    return 0;                   //д��ɹ�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ�Ĵ���
//  @param      cmd         �Ĵ�����ַ
//  @param      *val        �洢��ȡ�����ݵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void encoder_spi_r_reg_byte(uint8 cmd, uint8 *val, PIN_enum cs_pin)
{
    GPIO_PIN_RESET(cs_pin);
    cmd |= ABS_ENCODER_SPI_R;
    spi_wr_byte(cmd);
    spi_wr_byte(0x00);

    GPIO_PIN_SET(cs_pin);
    systick_delay_us(1);
    GPIO_PIN_RESET(cs_pin);
    *val = spi_wr_byte(0x00);
    spi_wr_byte(0x00);
    GPIO_PIN_SET(cs_pin);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ƫ
//  @param      zero_position  ��Ҫ���õ���ƫ
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void set_zero_position_spi(uint16 zero_position, PIN_enum cs_pin)
{    
    zero_position = (uint16)(4096 - zero_position);
    zero_position = zero_position << 4;
    encoder_spi_w_reg_byte(ZERO_L_REG,(uint8)zero_position, cs_pin);//������λ
    encoder_spi_w_reg_byte(ZERO_H_REG,zero_position>>8, cs_pin);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ��ǰ�Ƕ�
//  @param      void
//  @return     uint16       ���ؽǶ�ֵ0-4095 ��Ӧ0-360��
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint16 encoder_angle_spi(PIN_enum cs_pin)
{
    uint16 angle;
    angle = 0;
    GPIO_PIN_RESET(cs_pin);
    angle = (uint16)spi_wr_byte(0x00);
    angle <<= 8;                                //�洢�߰�λ
    angle |= (uint16)spi_wr_byte(0x00);  //�洢�Ͱ�λ
    GPIO_PIN_SET(cs_pin);
    
    return angle>>4;                               //12λ���ȣ����������λ
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������1�ٶȻ�ȡ
//  @param      cs_pin		 ������1��CS����
//  @return     uint16       ���ؽǶ�ֵ-511-511
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int16 encoder1_speed_spi(PIN_enum cs_pin)
{
    static uint16 old_angle ,new_angle;
    uint16 angle_diff;

    //��ȡ���νǶ�����
    GPIO_PIN_RESET(cs_pin);
    new_angle = (uint16)spi_wr_byte(0x00);
    new_angle <<= 8;                           //�洢�߰�λ
    new_angle |= (uint16)spi_wr_byte(0x00);    //�洢�Ͱ�λ
    GPIO_PIN_SET(cs_pin);
    new_angle >>= 6;

    angle_diff = (old_angle - new_angle)&0x3ff;
    old_angle = new_angle;                      //�������


    return ((int16)angle_diff - ((angle_diff & 0x200)<<1));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������2�ٶȻ�ȡ
///  @param      cs_pin		 ������2��CS����
//  @return     uint16       ���ؽǶ�ֵ-511-511
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int16 encoder2_speed_spi(PIN_enum cs_pin)
{
    static uint16 old_angle ,new_angle;
    uint16 angle_diff;

    //��ȡ���νǶ�����
    GPIO_PIN_RESET(cs_pin);
    new_angle = (uint16)spi_wr_byte(0x00);
    new_angle <<= 8;                           //�洢�߰�λ
    new_angle |= (uint16)spi_wr_byte(0x00);    //�洢�Ͱ�λ
    GPIO_PIN_SET(cs_pin);
    new_angle >>= 6;

    angle_diff = (old_angle - new_angle)&0x3ff;
    old_angle = new_angle;                      //�������


    return ((int16)angle_diff - ((angle_diff & 0x200)<<1));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������3�ٶȻ�ȡ
//  @param      cs_pin		 ������3��CS����
//  @return     uint16       ���ؽǶ�ֵ-511-511
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int16 encoder3_speed_spi(PIN_enum cs_pin)
{
    static uint16 old_angle ,new_angle;
    uint16 angle_diff;

    //��ȡ���νǶ�����
    GPIO_PIN_RESET(cs_pin);
    new_angle = (uint16)spi_wr_byte(0x00);
    new_angle <<= 8;                           //�洢�߰�λ
    new_angle |= (uint16)spi_wr_byte(0x00);    //�洢�Ͱ�λ
    GPIO_PIN_SET(cs_pin);
    new_angle >>= 6;

    angle_diff = (old_angle - new_angle)&0x3ff;
    old_angle = new_angle;                      //�������


    return ((int16)angle_diff - ((angle_diff & 0x200)<<1));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������4�ٶȻ�ȡ
//  @param      cs_pin		 ������4��CS����
//  @return     uint16       ���ؽǶ�ֵ-511-511
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int16 encoder4_speed_spi(PIN_enum cs_pin)
{
    static uint16 old_angle ,new_angle;
    uint16 angle_diff;

    //��ȡ���νǶ�����
    GPIO_PIN_RESET(cs_pin);
    new_angle = (uint16)spi_wr_byte(0x00);
    new_angle <<= 8;                           //�洢�߰�λ
    new_angle |= (uint16)spi_wr_byte(0x00);    //�洢�Ͱ�λ
    GPIO_PIN_SET(cs_pin);
    new_angle >>= 6;

    angle_diff = (old_angle - new_angle)&0x3ff;
    old_angle = new_angle;                      //�������


    return ((int16)angle_diff - ((angle_diff & 0x200)<<1));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������Լ캯��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void encoder_self5_check(PIN_enum cs_pin)
{
    uint8 val;
    do
    {
        encoder_spi_r_reg_byte(6, &val, cs_pin);
        //��������ԭ�������¼���
        //1 ���������ˣ�������µ������ĸ��ʼ���
        //2 ���ߴ������û�нӺ�
    }while(0x1C != val);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������ʼ������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void encoder_init_spi(PIN_enum cs_pin)
{
    //��ʼ��SPI��ʹ���������CS����
    spi_init(ABS_ENCODER_SPI_NUM, ABS_ENCODER_SPI_SCK_PIN, ABS_ENCODER_SPI_MOSI_PIN, ABS_ENCODER_SPI_MISO_PIN, cs_pin, 0, FPCLK_DIV_16);
    encoder_self5_check(cs_pin);
    encoder_spi_w_reg_byte(DIR_REG, 0x00, cs_pin);       //������ת���� ��ת��ֵ��С��0x00   ��ת��ֵ���0x80
    set_zero_position_spi(0, cs_pin);                   //������ƫ
}

