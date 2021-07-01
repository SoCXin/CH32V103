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

#include "ch32v10x_misc.h"
#include "ch32v10x_flash.h"
#include "zf_flash.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      У��FLASH�Ƿ�������
//  @param      sector_num      ��Ҫд����������   ������Χ FLASH_SECTION_00-FLASH_SECTION_15
//  @param      page_num        ��ǰ����ҳ�ı��        ������Χ FLASH_PAGE_0-FLASH_PAGE_3
//  @return                     ����1�����ݣ�����0û�����ݣ������Ҫ�������ݵ�����д���µ�������Ӧ�ö������������в�������
//  @since      v1.0
//  Sample usage:               flash_check(FLASH_SECTION_00,FLASH_PAGE_0);
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check (FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num)
{
    uint16 temp_loop;
    uint32 flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));     // ��ȡ��ǰ Flash ��ַ

    for(temp_loop = 0; temp_loop < FLASH_PAGE_SIZE; temp_loop+=4)                                       // ѭ����ȡ Flash ��ֵ
    {
        if( (*(__IO u32*) (flash_addr+temp_loop)) != 0xffffffff )                                       // ������� 0xffffffff �Ǿ�����ֵ
            return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������
//  @param      sector_num      ��Ҫд����������   ������Χ FLASH_SECTION_00-FLASH_SECTION_15
//  @param      page_num        ��ǰ����ҳ�ı��     ������Χ FLASH_PAGE_0-FLASH_PAGE_3
//  @return                     ����1�б�ʾʧ��  ����0��ʾ�ɹ�
//  @since      v1.0
//  Sample usage:               flash_erase_page(FLASH_SECTION_00,FLASH_PAGE_0);
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_erase_page (FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num)
{
    static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
    uint32 flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));     // ��ȡ��ǰ Flash ��ַ

    FLASH_Unlock();                                                                                     // ���� Flash
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);                           // ���������־
    gFlashStatus = FLASH_ErasePage(flash_addr);                                                         // ����
    FLASH_ClearFlag(FLASH_FLAG_EOP );                                                                   // ���������־
    FLASH_Lock();                                                                                       // ���� Flash
    if(gFlashStatus != FLASH_COMPLETE)                                                                  // �жϲ����Ƿ�ɹ�
        return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡһҳ
//  @param      sector_num      ��Ҫ��ȡ���������   ������Χ FLASH_SECTION_00-FLASH_SECTION_15
//  @param      page_num        ��Ҫ��ȡ��ҳ���        ������Χ FLASH_PAGE_0-FLASH_PAGE_3
//  @param      buf             ��Ҫ��ȡ�����ݵ�ַ   ������������ͱ���Ϊuint32
//  @param      len             ��Ҫ��ȡ�����ݳ���   ������Χ 1-256
//  @return                     ����1�б�ʾʧ��  ����0��ʾ�ɹ�
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flash_page_read (FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num, uint32 *buf, uint16 len)
{
    uint16 temp_loop = 0;
    uint32 flash_addr = 0;
    flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));            // ��ȡ��ǰ Flash ��ַ
    flash_addr = ((uint32_t)0x0800F000);

    for(temp_loop = 0; temp_loop < len; temp_loop++)                                                    // ����ָ�����ȶ�ȡ
    {
        *buf++ = *(__IO uint32_t*)(flash_addr+temp_loop*4);                                             // ѭ����ȡ Flash ��ֵ
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���һҳ
//  @param      sector_num      ��Ҫд����������   ������Χ FLASH_SECTION_00-FLASH_SECTION_15
//  @param      page_num        ��Ҫд���ҳ���        ������Χ FLASH_PAGE_0-FLASH_PAGE_3
//  @param      buf             ��Ҫд������ݵ�ַ   ������������ͱ���Ϊuint32
//  @param      len             ��Ҫд������ݳ���   ������Χ 1-256
//  @return                     ����1�б�ʾʧ��  ����0��ʾ�ɹ�
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_page_program (FLASH_SECTION_enum sector_num, FLASH_PAGE_enum page_num, const uint32 *buf, uint16 len)
{
    static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
    uint32 flash_addr = 0;
    flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));            // ��ȡ��ǰ Flash ��ַ

    if(flash_check(sector_num, page_num))                                                               // �ж��Ƿ������� ����������ı��� ��ֹ����û������д��
        flash_erase_page(sector_num, page_num);                                                         // ������һҳ

    FLASH_Unlock();                                                                                     // ���� Flash
    while(len--)                                                                                        // ���ݳ���
    {
        gFlashStatus = FLASH_ProgramWord(flash_addr, *buf++);                                           // ���� 32bit д������
        if(gFlashStatus != FLASH_COMPLETE)                                                              // ����ȷ�ϲ����Ƿ�ɹ�
            return 1;
        flash_addr += 4;                                                                                // ��ַ����
    }
    FLASH_Lock();                                                                                       // ���� Flash
    return 0;
}




























