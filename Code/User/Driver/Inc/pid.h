#ifndef __PID_H
#define __PID_H


typedef struct
{
    float target_val;           //Ŀ��ֵ
    float actual_val;        		//ʵ��ֵ
    float err;             			//����ƫ��ֵ
    float err_last;          		//����������ƫ��ֵ
		float err_next;          		//������һ��ƫ��ֵ
    float Kp,Ki,Kd;          		//������������֡�΢��ϵ��
    float integral;          		//�������ֵ
		float integral_min;					//�����޷�
		float integral_max;					//�����޷�
		float output_val_max;				//����޷�
		float output_val_min;				//����޷�
}pid_t;
void PID_Init(pid_t* pid,float Kp,float Ki,float Kd,float integral_max,float integral_min,float output_val_max,float output_val_min);
float PID_pos_realize(pid_t* pid,float temp_val,float sensor_val);
float PID_inc_realize(pid_t* pid,float temp_val,float sensor_val);

#endif  
