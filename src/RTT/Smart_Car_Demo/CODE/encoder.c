#include "encoder.h"

#define ENCODER1_TIM		TIM_1
#define ENCODER1_A			TIM_1_ENC1_A08
#define ENCODER1_B			TIM_1_ENC2_A01

#define ENCODER2_TIM		TIM_8
#define ENCODER2_A			TIM_8_ENC1_C00
#define ENCODER2_B			TIM_8_ENC2_C01

uint16 encoder_data[4];

void encoder_init(void)
{
    encoder_init_spi(ABS_ENCODER_SPI_PC1_PIN);      //编码器1初始化。
    //encoder_init_spi(ABS_ENCODER_SPI_PC2_PIN);      //编码器2初始化。
    //encoder_init_spi(ABS_ENCODER_SPI_PC3_PIN);      //编码器3初始化。
    //encoder_init_spi(ABS_ENCODER_SPI_PC4_PIN);      //编码器4初始化。
}


void encoder_get(void)
{
    encoder_data[0] = encoder1_speed_spi(ABS_ENCODER_SPI_PC1_PIN);          //获取编码器1的数据
    //encoder_data[1] = encoder2_speed_spi(ABS_ENCODER_SPI_PC2_PIN);          //获取编码器2的数据
    //encoder_data[2] = encoder3_speed_spi(ABS_ENCODER_SPI_PC3_PIN);          //获取编码器3的数据
    //encoder_data[3] = encoder4_speed_spi(ABS_ENCODER_SPI_PC4_PIN);          //获取编码器4的数据
}
