/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_flash
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/

#ifndef _zf_flash_h
#define _zf_flash_h

#include "common.h"

#define FLASH_BASE_ADDR             (0x08000000)                // FALSH�׵�ַ
#define FLASH_PAGE_SIZE             (0x00000400)                // 1K byte
#define FLASH_SECTION_SIZE          (FLASH_PAGE_SIZE*4)         // 4K byte
//һ��16��������һ������4K��

// ö�� Flash ����  ��ö�ٶ��岻�����û��޸�
typedef enum
{
    FLASH_SECTION_00,
    FLASH_SECTION_01,
    FLASH_SECTION_02,
    FLASH_SECTION_03,
    FLASH_SECTION_04,
    FLASH_SECTION_05,
    FLASH_SECTION_06,
    FLASH_SECTION_07,
    FLASH_SECTION_08,
    FLASH_SECTION_09,
    FLASH_SECTION_10,
    FLASH_SECTION_11,
    FLASH_SECTION_12,
    FLASH_SECTION_13,
    FLASH_SECTION_14,
    FLASH_SECTION_15,
}FLASH_SECTION_enum;

// ö�� Flash ҳ���� ��ö�ٶ��岻�����û��޸�
typedef enum
{
    FLASH_PAGE_0,
    FLASH_PAGE_1,
    FLASH_PAGE_2,
    FLASH_PAGE_3,
}FLASH_PAGE_enum;

uint8 flash_check(FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num);
uint8 flash_erase_page(FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num);
void flash_page_read (FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num, uint32 *buf, uint16 len);
uint8 flash_page_program(FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num, const uint32 *buf, uint16 len);

#endif
