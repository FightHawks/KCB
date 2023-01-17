/*
���ļ�Ϊͨ��uart�����˻�ͨѶ����������
LHQ 2022.01.16 
*/
#include "UartDriver.h"
uint8_t date[10];
static uint8_t loopstate_send = 1;


void test()
{
			HAL_Delay(8000);
			date[8] = 1;
			GetPackage(date,0x80,0x80,0x80,0x80);
      SendOnePackage(date); //��������2������ģʽ
      HAL_Delay(100);
      GetPackage(date,0x80,0x80,0x80,0xFF);
      SendOnePackage(date); //��������4�������ʼ��ת
      HAL_Delay(1000);
			GetPackage(date,0x80,0x80,0x80,0x80);
      SendOnePackage(date); //��������2������ģʽ
      HAL_Delay(100);
       GetPackage(date,0x80,0x80,0x80,0xFF);
      SendOnePackage(date); //��������4����ɣ�����
      HAL_Delay(1500);  //��������1.5��
      
      //uav_cmd[2][1]=0x78; //������ͣʱ��ֵΪ0x80,���˻������Ҳ�ɣ�����΢������
      //uav_cmd[2][6]=uav_cmd[2][1];
      //for(uint8_t i=2;i<6;i++)  //�������ݺ���Ҫ���¼�������2��У���룬����uav_cmd[2][6]��
      //  uav_cmd[2][6]=uav_cmd[2][6]^uav_cmd[2][i];
      
     /* for(uint8_t i=0;i<100;i++)  //��ͣ10��
      { send_char_array(&huart2,uav_cmd[2],8); //���ֵ�ǰ�߶� ��Ҫ���ϵط����� 
        HAL_Delay(100);  
      }
      
      uav_cmd[3][3]=64;
      uav_cmd[3][6]=uav_cmd[3][1];
      for(uint8_t i=2;i<6;i++)  //�������ݺ���Ҫ���¼�������3��У���룬����uav_cmd[3][6]��
        uav_cmd[3][6]=uav_cmd[3][6]^uav_cmd[3][i];
      
      for(uint8_t i=0;i<50;i++)
      { send_char_array(&huart2,uav_cmd[3],8); //�����½�    //����5��
        HAL_Delay(100);  
      }
  
      send_char_array(&huart2,uav_cmd[11],8); //���ͣת
*/
}

void fly()
{
	HAL_Delay(5000);
	//SendPackageLoop(date,0,0);
	for(int i = 0;i < 4; i++)
	{
		date[8] = 1;
		GetPackage(date,0x80,0x80,0x80,0x80);
		SendOnePackage(date);
		HAL_Delay(1000);
		GetPackage(date,0x80,0x80,0x80,0xFF);
		SendOnePackage(date);
		HAL_Delay(1000);
		
	}
	while(1)
	{
		GetPackage(date,0x79,0x79,0x80,0x83);
		SendOnePackage(date);
		HAL_Delay(500);
	}
	
	date[8] = 1;
		GetPackage(date,0x80,0x80,0x80,0xFF);
		for(int i = 0;i < 20; i++)
		{
			SendOnePackage(date);
			date[8] = 0;
			HAL_Delay(100);
		}
	
	date[8] = 1;
	GetPackage(date,0x80,0x80,0x80,0x80);
	for(int i = 0;i < 10; i++)
	{
		SendOnePackage(date);
		date[8] = 0;
		HAL_Delay(100);
	}
	date[8] = 1;
		GetPackage(date,0x80,0x80,0x80,0xFF);
		for(int i = 0;i < 20; i++)
		{
			SendOnePackage(date);
			date[8] = 0;
			HAL_Delay(100);
		}
	
		date[8] = 1;
		GetPackage(date,0x80,0x80,0x80,0xFF);
		for(int i = 0;i < 2; i++)
		{
			SendOnePackage(date);
			date[8] = 0;
			HAL_Delay(100);
		}
		
	date[8] = 1;
	GetPackage(date,0x80,0x80,0x80,0xFF);
	for(int i = 0;i < 1500; i++)
	{
		SendOnePackage(date);
		date[8] = 0;
		HAL_Delay(100);
	}
}
//ע��
/***************************************************
*@brief:  ����һ�����ݰ�																				 
*@param:  ���ݰ�������ָ��                                     
*@retval: 0	������ʧ��,���ݰ��ѱ�����
					1	�����ͳɹ�
					2	������ʧ�ܣ����ݰ���ʽ����
					
*@author: lhq 2023.1.16                                        
****************************************************/
uint8_t SendOnePackage(uint8_t* pDate)
{
	if(pDate[8] == 0)
	{
		if(pDate[0] == 0x66)//���Ͱ�β
		{
			for(int i = 0;i < 8;i++)
			{
				HAL_UART_Transmit_DMA(&huart2,pDate,8);
				//HAL_UART_Transmit(&huart1,&pDate[i],1,0xff);
			}
			pDate[8] = 1;
			return 1;
		}
		else
			return 2;
	}
	else
		return 0;
}

/***************************************************
*@brief:  ѭ���������ݰ�																				 
*@param:  ���ݰ�������ָ��                                     
*@retval: 1	����ɷ���
*@author: lhq 2023.1.16                                        
****************************************************/
uint8_t SendPackageLoop(uint8_t* pDate,uint32_t frequency,uint32_t times)
{
	HAL_UART_Transmit_DMA(&huart2,pDate,8);
	return 1;
}
/***************************************************
*@brief:  �����ݽ��д��																				 
*@param:  buff		������ָ�룬������������
					roll		�������
					pitch		��������
					yaw			��ƫ����
					throttle������
*@retval: 0 : ���ʧ�ܣ�������δ������       
					1	������ɹ�
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t GetPackage(uint8_t* buff,uint8_t roll,uint8_t pitch,uint8_t yaw,uint8_t throttle)
{
	if(buff[8] != 0)
	{
		buff[0] = 0x66;		
		buff[1] = roll;		
		buff[2] = pitch;	
		buff[3] = throttle;
		buff[4] = yaw;
		buff[5] = 0x00;
		buff[6] = buff[1] ^ buff[2] ^ buff[3] ^ buff[4] ^ buff[5];
		buff[7] =	0x99;
		buff[8] = 0;//�Ƿ񱻷��ͣ����λ
		return 1;
	}
	else
		return 0;
}
