/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-07-30 20:42:59
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-08-19 06:48:59
 * @FilePath: \KEIL-25002-LED-PROJECT\User\main.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "stm32f10x.h"     
#include <stdint.h> 
#include "self_oled.h"
#include "self_menu.h"
#include "self_oled_model.h"
#include <stm32f10x_gpio.h>     

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

int main(void)
{
	unsigned int i;
	unsigned int j;
	F_OLED_Init();
	// F_OLED_Set_Data(0,30,16,16,OLED_CF16x16[2].Data);
	// F_showClockUI();
	// f_OLED_ShowChar(0,0,6,8, '#');
	// f_oledPrintf(16,16,8,16,"你");
	f_oledShowString(16,16,8,16, "你好好界");
	
	
	// F_OLED_Set_Data(0,0,16,16,OLED_CF16x16[4].Data);
	// f_oledPrintf(12,0,6,8,"%d-%d-%d",21,22,23);
	// f_OLED_ShowChar(12, 0, 6, 8, '?');
	F_OLED_Disp_Update();
	while (1)
	{
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 128; j++)
			 {
				Delay_ms(100);
			 }
		}
	}
}
