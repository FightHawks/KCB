#ifndef __KAERMAN_H
#define __KAERMAN_H

/*
        Q:����������Q���󣬶�̬��Ӧ��죬�����ȶ��Ա仵
        R:����������R���󣬶�̬��Ӧ�����������ȶ��Ա��
 
R���������˲����������ʵ�����ߵ�����̶ȣ�rԽСԽ�ӽ���
 
Q�������˲��������ƽ���̶ȣ�qԽСԽƽ����
 
*/

typedef struct
{
	float Q;//��������
	float R;//��������
	float x_last;
	float p_last;
}KalmanFilterData;
	
	

float KalmanFilter(float ResrcData,KalmanFilterData* KFD);


#endif  
