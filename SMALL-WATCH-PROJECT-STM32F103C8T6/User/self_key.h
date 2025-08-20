/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-21 02:41:22
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-21 03:14:20
 * @FilePath: \PROJECT-SMALL-WATCH\SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_key.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef  _SELF_KEY_H_
#define  _SELF_KEY_H_
#include "main.h"

extern uint8_t g_ShowNum;

void F_KeyInit(void);
void F_KeyValueHandler(void);

#endif


