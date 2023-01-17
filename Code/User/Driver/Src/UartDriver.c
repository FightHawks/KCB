/*
���ļ�Ϊͨ��uart�����˻�ͨѶ����������
LHQ 2022.01.16 
*/
#include "UartDriver.h"
static uint8_t date[10];//���ݰ��������
static UFD udate;				//���ݽṹ��

/***************************************************
*@brief:  ��ɺ���																	 
*@param: 	��                                    
*@retval: ��			
*@author: lhq 2023.1.16                                        
****************************************************/
void fly()
{
			HAL_Delay(5000);
			udate.roll=0x80;
			udate.pitch=0x80;
			udate.throttle=0x80;
			udate.yaw=0x80;
			udate.mode=0x00;
			date[8] = 1;
			UpdatePackage();
	for(int i = 0;i < 3; i++)
	{
		WriteThrottle_SD(0x80);
		UpdatePackage();
		SendOnePackage();
		HAL_Delay(1000);
		WriteThrottle_SD(0xFF);
		UpdatePackage();
		SendOnePackage();
		HAL_Delay(1000);
	}

}
//ע��
/***************************************************
*@brief:  ����һ�����ݰ�																				 
*@param:  ���ݰ�������ָ��                                     
*@retval: 0	������ʧ��,���ݰ��ѱ�����
					1	�����ͳɹ�
					
*@author: lhq 2023.1.16                                        
****************************************************/
uint8_t SendOnePackage()
{
	if(date[8] == 0)
	{	
				HAL_UART_Transmit_DMA(&huart2,date,8);
				//HAL_UART_Transmit(&huart1,date,8,0xff);
			
			date[8] = 1;
			return 1;
	}
	else
		return 0;
}

/***************************************************
*@brief:  �����ݽ��д��																				 
*@param:  buff		������ָ�룬������������
					date		�����ݰ��ṹ��
*@retval: 0 : ���ʧ�ܣ�������δ������       
					1	������ɹ�
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t UpdatePackage()
{
	if(date[8] != 0)
	{
		date[0] = 0x66;		
		date[1] = udate.roll;		
		date[2] = udate.pitch;	
		date[3] = udate.throttle;
		date[4] = udate.yaw;
		date[5] = udate.mode;
		date[6] = date[1] ^ date[2] ^ date[3] ^ date[4] ^ date[5];
		date[7] =	0x99;
		date[8] = 0;//�Ƿ񱻷��ͣ����λ
		return 1;
	}
	else
		return 0;
}
/***************************************************
*@brief:  �޸����ݽṹ������Ų���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteThrottle_SD(uint8_t parm)
{	
	udate.throttle = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ������Ų���																				 
*@param:  ��
*@retval: ���Ų���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadThrottle_SD()
{	
	return udate.throttle;
}
/***************************************************
*@brief:  �޸����ݽṹ��ĺ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteRoll_SD(uint8_t parm)
{	
	udate.roll = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ��ĺ���ǲ���																				 
*@param:  ��
*@retval: �����
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadRoll_SD()
{	  
	return udate.roll;
}
/***************************************************
*@brief:  �޸����ݽṹ��ĸ����ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WritePitch_SD(uint8_t parm)
{	
	udate.pitch = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ��ĸ����ǲ���																				 
*@param:  ��
*@retval: �����ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadPitch_SD()
{	
	return udate.pitch;
}
/***************************************************
*@brief:  �޸����ݽṹ���ƫ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteYaw_SD(uint8_t parm)
{	
	udate.yaw = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ���ƫ���ǲ���																				 
*@param:  ��
*@retval: ƫ���ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadYaw_SD()
{	
	return udate.yaw;
}	

/***************************************************
*@brief:  �޸����ݽṹ���ƫ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteMode_SD(uint8_t parm)
{	
	udate.mode = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ���ƫ���ǲ���																				 
*@param:  ��
*@retval: ƫ���ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadMode_SD()
{	
	return udate.mode;
}	
