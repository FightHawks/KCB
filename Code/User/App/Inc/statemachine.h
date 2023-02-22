#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include "UartDriver.h"
#include "mpu6050.h"
#include "opticalflow.h"
#include "SPL06_001.h"
#include <stdio.h>
//#include "ultrasonic.h"
#include "altimeter.h"
#include "pid.h"



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
enum callstate
{
	NO_RESPNOD,
	RESPNODED,
	ACCOMPLISHED,
};
typedef struct
{
	uint8_t taskid;
	uint32_t ms;
	uint32_t lstime;
}_TaskDelay;
typedef struct
{
	enum state state;
	enum state lstate;
	enum state cstate;
	enum callstate cdstate;
	uint8_t called_flag;
}_StatemachineData;

typedef struct
{
	float target_height;
	float target_yaw;
	uint8_t hover;
}Target_Val;

//״̬��ѭ����
void loop(void);

//״̬����غ���
uint8_t CallTask(enum state state);
void UpdateTime(void);
void print_data(void);
void UpdateState(void);
void DelayListInit(void);
//���� ����ID��Ϊ�˼�¼������ʱ��
void task1(uint16_t taskid);
void task2(uint16_t taskid);
void task3(uint16_t taskid);
void task4(uint16_t taskid);
void task5(uint16_t taskid);
void task6(uint16_t taskid);
void PID_calculate(Target_Val val);
void task_main(Target_Val tval);
//������ʱ����
uint8_t DelayMs(uint32_t ms , uint16_t taskid);
#endif  
