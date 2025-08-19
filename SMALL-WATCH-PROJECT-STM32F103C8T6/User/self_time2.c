#include "self_time2.h"
/**
 * @description: TO START time 2 clock
 * @return {*}
 */

void F_timer2Init(void)
{
	/*base on APB1 a kind of low speed bus*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//����TIM2��ʱ��
	
	/*setting the default clock source*/
	TIM_InternalClockConfig(TIM2);		//ѡ��TIM2Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
	
	/*init*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//base setting struct
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//clock frequency default division
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//the mode of the clock
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;					//value of ARR the cycle of the clock
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;				//pre frequency division
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);				//setting the configuration of time 2 base on  TIM_TimeBaseInitTypeDef struct
	
	/*�ж��������*/
	//�����ʱ�����±�־λ
	//TIM_TimeBaseInit����ĩβ���ֶ������˸����¼�
	//��������˱�־λ�������жϺ󣬻����̽���һ���ж�
	//�������������⣬������˱�־λҲ��
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);						
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);					//enable the interrupt of time 2
	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����2
																//����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
																//�˷������������������н������һ��
																//���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
																//�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//ѡ������NVIC��TIM2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//ָ��NVIC��·����ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);								//���ṹ���������NVIC_Init������NVIC����
	
	/*TIMʹ��*/
	TIM_Cmd(TIM2, ENABLE);			//ʹ��TIM2����ʱ����ʼ����
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		g_u8Time4msCount++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	// clear the interrupt flag
	}
}




