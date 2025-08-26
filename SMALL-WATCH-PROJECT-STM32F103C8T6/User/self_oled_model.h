/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-07-30 14:37:46
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-26 23:01:31
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_oled_model.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_OLED_MODEL_H_
#define _SELF_OLED_MODEL_H_
#include "main.h"
#include <stdint.h>

extern const uint8_t OLED_ASCII_F6x8[][6];
extern const uint8_t OLED_ASCII_F8x16[][16];
extern const uint8_t OLED_ASCII_F12x24[][36];

/*字模基本单元*/
/*以下两个宏定义只可解除其中一个的注释*/
//#define OLED_CHARSET_UTF8			//定义中文字符集为UTF8
#define OLED_CHARSET_GB2312		//定义中文字符集为GB2312

typedef struct 
{
	uint8_t Data[32];				//字模数据
	
#ifdef OLED_CHARSET_UTF8			//定义字符集为UTF8
	char Index[5];					//汉字索引，空间为5字节
#endif

#ifdef OLED_CHARSET_GB2312			//定义字符集为GB2312
	char Index[3];					//汉字索引，空间为3字节
#endif

} ChineseCell_t;
extern const ChineseCell_t OLED_CF16x16[];  // chinese font
extern const uint8_t Frame44X44[];

#endif
