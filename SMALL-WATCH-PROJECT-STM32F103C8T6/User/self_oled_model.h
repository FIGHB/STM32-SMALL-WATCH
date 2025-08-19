/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-07-30 14:37:46
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-08-15 22:28:29
 * @FilePath: \KEIL-25002-LED-PROJECT\User\self_oled_model.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_OLED_MODEL_H_
#define _SELF_OLED_MODEL_H_
#include <stdint.h>

extern const uint8_t OLED_ASCII_F6x8[][6];
extern const uint8_t OLED_ASCII_F8x16[][16];
extern const uint8_t OLED_ASCII_F12x24[][36];

/*��ģ������Ԫ*/
/*���������궨��ֻ�ɽ������һ����ע��*/
//#define OLED_CHARSET_UTF8			//���������ַ���ΪUTF8
#define OLED_CHARSET_GB2312		//���������ַ���ΪGB2312

typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
	char Index[5];					//�����������ռ�Ϊ5�ֽ�
#endif

#ifdef OLED_CHARSET_GB2312			//�����ַ���ΪGB2312
	char Index[3];					//�����������ռ�Ϊ3�ֽ�
#endif

	uint8_t Data[32];				//��ģ����
} ChineseCell_t;
extern const ChineseCell_t OLED_CF16x16[];  // chinese font

#endif
