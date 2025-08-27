/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-07-30 10:40:16
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-27 19:29:36
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_oled.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_OLED_H_
#define _SELF_OLED_H_
/***********************************************************************************************
 * 1.3����ʾ����
 * ����оƬ SH1106
 * 1106оƬ�� 132*64λ���ص㡣�� OLED ��Ļֻ�� 128 *64 λ����������֪�� 0 1 ���п��ţ�����������Ҫƫ����λ
 * ÿ8��Ϊһҳ��128�У���8ҳ��ͨ��������ҳ��ַ���е�ַ��Ȼ��д�����ݣ�������ô��ģʽ���ȷ��ֽڸ�λ���ٷ���λ
 * ������ʾ��������ʽ��������
 */
#include "self_oled_model.h"
#include "stm32f10x.h"
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define PIN_SCL_RCC_APB2Periph_GPIOX    RCC_APB2Periph_GPIOB
#define PIN_SCL_GPIO_Pin_X              GPIO_Pin_8
#define PIN_SCL_GPIOX                   GPIOB

#define PIN_SDA_RCC_APB2Periph_GPIOX    RCC_APB2Periph_GPIOB
#define PIN_SDA_GPIO_Pin_X              GPIO_Pin_9
#define PIN_SDA_GPIOX                   GPIOB

#define OLED_MAX_WIDTH  128
#define OLED_MAX_HEIGHT 64

extern unsigned char g_OLED_Disp_Arr[8][128];
void F_OLED_Init(void);
void F_OLED_Clear(void);
void F_OLED_Disp_Update(void);
void F_OLED_Show_Graph(int16_t pos_x, int16_t pos_y, int16_t width, int16_t height, const uint8_t *data_arr);
void f_oledShowString(unsigned char x, unsigned char y, unsigned char width, unsigned char height, const char *str);
void f_OLED_ShowChar(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char u8_char);
void f_oled_ShowHexString(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *int8_str);
void f_oledPrintf(unsigned char x, unsigned char y, unsigned char width, unsigned char height, char *str, ...);
void F_OLED_ChooseAreaReverse(uint8_t x, uint8_t y, uint8_t width, uint8_t height);  



#endif

