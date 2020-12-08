/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/
#include "debug.h"
#include "string.h"
#include "CHRV3UFI.h"
/* Global define */


/* Global Variable */
__attribute__ ((aligned(4))) UINT8  RxBuffer[MAX_PACKET_SIZE] ;      // IN, must even address
__attribute__ ((aligned(4))) UINT8  TxBuffer[MAX_PACKET_SIZE] ;      // OUT, must even address
__attribute__ ((aligned(4))) UINT8  Com_Buffer[128];

UINT8  buf[100];                                  //���ȿ��Ը���Ӧ���Լ�ָ��

/* ������״̬,�����������ʾ������벢ͣ�� */
void mStopIfError( UINT8 iError )
{
    if ( iError == ERR_SUCCESS )
    {
      return;    /* �����ɹ� */
    }
    printf( "Error: %02X\r\n", (UINT16)iError );  /* ��ʾ���� */
    /* ���������,Ӧ�÷����������Լ�CHRV3DiskStatus״̬,�������CHRV3DiskReady��ѯ��ǰU���Ƿ�����,���U���ѶϿ���ô�����µȴ�U�̲����ٲ���,
       ��������Ĵ�����:
       1������һ��CHRV3DiskReady,�ɹ����������,����Open,Read/Write��
       2�����CHRV3DiskReady���ɹ�,��ôǿ�н���ͷ��ʼ����(�ȴ�U�����ӣ�CHRV3DiskReady��) */
    while ( 1 )
    {  }
}
/*******************************************************************************
* Function Name  : Set_USBConfig
* Description    : Set USB clock.
* Input          : None
* Return         : None
*******************************************************************************/
void USBHD_ClockCmd(UINT32 RCC_USBCLKSource,FunctionalState NewState)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, NewState);
	EXTEN->EXTEN_CTR |= EXTEN_USBHD_IO_EN;
	RCC_USBCLKConfig(RCC_USBCLKSource);             //USBclk=PLLclk/1.5=48Mhz
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHD,NewState);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main()
{
	UINT8   s, i;
	PUINT8  pCodeStr;
	UINT16  j;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

	printf("USBHD HOST Test\r\n");
	USBHD_ClockCmd(RCC_USBCLKSource_PLLCLK_1Div5,ENABLE);
	pHOST_RX_RAM_Addr = RxBuffer;
	pHOST_TX_RAM_Addr = TxBuffer;
	USB_HostInit();
	CHRV3LibInit();
	printf( "Wait Device In\r\n" );

	while(1)
	{
		s = ERR_SUCCESS;

		if ( R8_USB_INT_FG & RB_UIF_DETECT )
		{
			R8_USB_INT_FG = RB_UIF_DETECT ;

			s = AnalyzeRootHub( );
			if ( s == ERR_USB_CONNECT )
			{
				printf( "New Device In\r\n" );
				FoundNewDev = 1;
			}
			if( s == ERR_USB_DISCON )
			{
				printf( "Device Out\r\n" );
			}
		}

		if ( FoundNewDev || s == ERR_USB_CONNECT )
		{
			FoundNewDev = 0;
			Delay_Ms( 200 );
			s = InitRootDevice( Com_Buffer );
			if ( s == ERR_SUCCESS )
			{
				// U�̲������̣�USB���߸�λ��U�����ӡ���ȡ�豸������������USB��ַ����ѡ�Ļ�ȡ������������֮�󵽴�˴�����CH103�ӳ���������ɺ�������
				CHRV3DiskStatus = DISK_USB_ADDR;
				for ( i = 0; i != 10; i ++ )
				{
					printf( "Wait DiskReady\r\n" );
					s = CHRV3DiskReady( );                                 //�ȴ�U��׼����
					if ( s == ERR_SUCCESS )
					{
						break;
					}
					else
					{
						printf("%02x\r\n",(UINT16)s);
					}
					Delay_Ms( 50 );
				}
				if ( CHRV3DiskStatus >= DISK_MOUNTED )
				{
					/* ���ļ� */
					printf( "Open\r\n" );
					strcpy( (PCHAR)mCmdParam.Open.mPathName, "/C51/CH103HFT.C" );         //����Ҫ�������ļ�����·��
					s = CHRV3FileOpen( );                                          //���ļ�
					if ( s == ERR_MISS_DIR )
					{
						printf("�����ڸ��ļ������г���Ŀ¼�����ļ�\r\n");
						pCodeStr = (PUINT8)"/*";
					}
					else
					{
						pCodeStr = (PUINT8)"/C51/*";    //�г�\C51��Ŀ¼�µĵ��ļ�
					}

					printf( "List file %s\r\n", pCodeStr );
					for ( j = 0; j < 10000; j ++ )                                 //�޶�10000���ļ�,ʵ����û������
					{
							strcpy( (PCHAR)mCmdParam.Open.mPathName, (PCCHAR)pCodeStr );              //�����ļ���,*Ϊͨ���,�����������ļ�������Ŀ¼
							i = strlen( (PCHAR)mCmdParam.Open.mPathName );
							mCmdParam.Open.mPathName[ i ] = 0xFF;                      //�����ַ������Ƚ��������滻Ϊ���������,��0��254,�����0xFF��255��˵�����������CHRV3vFileSize������
							CHRV3vFileSize = j;                                        //ָ������/ö�ٵ����
							i = CHRV3FileOpen( );                                      //���ļ�,����ļ����к���ͨ���*,��Ϊ�����ļ�������
							/* CHRV3FileEnum �� CHRV3FileOpen ��Ψһ�����ǵ����߷���ERR_FOUND_NAMEʱ��ô��Ӧ��ǰ�߷���ERR_SUCCESS */
							if ( i == ERR_MISS_FILE )
							{
								break;    //��Ҳ��������ƥ����ļ�,�Ѿ�û��ƥ����ļ���
							}
							if ( i == ERR_FOUND_NAME )                                 //��������ͨ�����ƥ����ļ���,�ļ�����������·�������������
							{
								printf( "  match file %04d#: %s\r\n", (unsigned int)j, mCmdParam.Open.mPathName );  /* ��ʾ��ź���������ƥ���ļ���������Ŀ¼�� */
								continue;                                                /* ����������һ��ƥ����ļ���,�´�����ʱ��Ż��1 */
							}
							else                                                       //����
							{
								mStopIfError( i );
								break;
							}
					}
					i = CHRV3FileClose( );                                          //�ر��ļ�
					printf( "U����ʾ���\r\n" );
				}
				else
				{
					printf( "U��û��׼���� ERR =%02X\r\n", (UINT16)s );
				}
			}
		}
		Delay_Ms( 100 );  // ģ�ⵥƬ����������
		SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��
	}
}



