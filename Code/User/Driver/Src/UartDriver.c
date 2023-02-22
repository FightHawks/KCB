/*
���ļ�Ϊͨ��uart�����˻�ͨѶ����������
LHQ 2022.01.16 
*/
#include "UartDriver.h"
#include "stdio.h"
static uint8_t data[10];//���ݰ��������
static UFD udata;				//���ݽṹ��

/***************************************************
*@brief:  ��ɺ���																	 
*@param: 	��                                    
*@retval: ��			
*@author: lhq 2023.1.16                                        
****************************************************/
void fly()
{
			HAL_Delay(2000);
			udata.roll=0x80;
			udata.pitch=0x80;
			udata.throttle=0x80;
			udata.yaw=0x80;
			udata.mode=0x00;
			data[8] = 1;
			UpdatePackage();
	for(int i = 0;i < 3; i++)
	{
		WriteThrottle_SD(0x80);
		UpdatePackage();
		SendOnePackage();
		HAL_Delay(500);
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
	if(data[8] == 0)
	{	
			while(HAL_UART_Transmit_DMA(&huart2,data,8) == HAL_BUSY)
			{
				huart2.gState = HAL_UART_STATE_READY;
				__HAL_UNLOCK(&huart2);//����
			}
				//HAL_UART_Transmit(&huart1,data,8,0xff);
			data[8] = 1;
			return 1;
	}
	else
		return 0;
}

/***************************************************
*@brief:  �����ݽ��д��																				 
*@param:  buff		������ָ�룬������������
					data		�����ݰ��ṹ��
*@retval: 0 : ���ʧ�ܣ�������δ������       
					1	������ɹ�
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t UpdatePackage()
{
	if(data[8] != 0)
	{
		data[0] = 0x66;		
		data[1] = udata.roll;		
		data[2] = udata.pitch;	
		data[3] = udata.throttle;
		data[4] = udata.yaw;
		data[5] = udata.mode;
		data[6] = data[1] ^ data[2] ^ data[3] ^ data[4] ^ data[5];
		data[7] =	0x99;
		data[8] = 0;//�Ƿ񱻷��ͣ����λ
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
	udata.throttle = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ������Ų���																				 
*@param:  ��
*@retval: ���Ų���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadThrottle_SD()
{	
	return udata.throttle;
}
/***************************************************
*@brief:  �޸����ݽṹ��ĺ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteRoll_SD(uint8_t parm)
{	
	udata.roll = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ��ĺ���ǲ���																				 
*@param:  ��
*@retval: �����
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadRoll_SD()
{	  
	return udata.roll;
}
/***************************************************
*@brief:  �޸����ݽṹ��ĸ����ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WritePitch_SD(uint8_t parm)
{	
	udata.pitch = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ��ĸ����ǲ���																				 
*@param:  ��
*@retval: �����ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadPitch_SD()
{	
	return udata.pitch;
}
/***************************************************
*@brief:  �޸����ݽṹ���ƫ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteYaw_SD(uint8_t parm)
{	
	udata.yaw = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ���ƫ���ǲ���																				 
*@param:  ��
*@retval: ƫ���ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadYaw_SD()
{	
	return udata.yaw;
}	

/***************************************************
*@brief:  �޸����ݽṹ���ƫ���ǲ���																				 
*@param:  parm:Ҫ�ĳɵĲ���
*@retval: ��
*@author: lhq 2023.1.16                                         
****************************************************/
void WriteMode_SD(uint8_t parm)
{	
	udata.mode = parm;
}
/***************************************************
*@brief:  ��ȡ���ݽṹ���ƫ���ǲ���																				 
*@param:  ��
*@retval: ƫ���ǲ���
*@author: lhq 2023.1.16                                         
****************************************************/
uint8_t ReadMode_SD()
{	
	return udata.mode;
}	
