#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include "UartDriver.h"
#include "mpu6050.h"
#include "opticalflow.h"
#include <stdio.h>

#define TASK_1_TIME 10
#define TASK_2_TIME 10
#define TASK_3_TIME 10
#define TASK_4_TIME 10

#define DELAY_NUM   						20				//������ʱ������
#define FIRST_TASK  						TASK_1 		//��һ������
#define LAST_TASK	 						TASK_6   	//���һ������
#define PACKET_UPDATE_INTERVAL 	200   		//���ݰ����¼����ms��
#define PACKET_SEND_INTERVAL		500				//���ݰ����ͼ����ms��
//�����ӳٺ꣬һ���������ӵ��һ���������ʼ����Ϊ������У��ȴ�ʱ����л����������
#define TaskDelay_ms(x) if(DelayMs(x,taskid)) return;	
//״̬ö��
enum state
{
	TASK_1,
	TASK_2,
	TASK_3,
	TASK_4,
	TASK_5,
	TASK_6,
};
//״̬��ѭ����
void loop(void);
//���� ����ID��Ϊ�˼�¼������ʱ��
void task1(uint16_t taskid);
void task2(uint16_t taskid);
void task3(uint16_t taskid);
void task4(uint16_t taskid);
void task5(uint16_t taskid);
void task6(uint16_t taskid);
//������ʱ����
uint8_t DelayMs(uint32_t ms , uint16_t taskid);
#endif  
