/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-21 02:41:22
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-21 19:34:53
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_key.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef  _SELF_SELF_KEY_H_
#define  _SELF_SELF_KEY_H_
#include "main.h"
typedef enum e_ENUM_KEY_VALUE
{
    ENUM_KEY_VALUE_NONE,
    ENUM_KEY_VALUE_UP_00,
    ENUM_KEY_VALUE_UP_01,
    ENUM_KEY_VALUE_UP_02,
    ENUM_KEY_VALUE_1S_00,
    ENUM_KEY_VALUE_1S_01,
    ENUM_KEY_VALUE_1S_02,
    ENUM_KEY_VALUE_3S_00,
    ENUM_KEY_VALUE_3S_01,
    ENUM_KEY_VALUE_3S_02
}ENUM_KEY_VALUE;

extern uint8_t g_ShowNum;

void F_KeyInit(void);
void F_KeyValueHandler(void);

#endif


