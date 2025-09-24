/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-21 21:43:24
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-24 21:21:14
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_rtc.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_RTC_H_
#define _SELF_RTC_H_
#include "main.h"
#include <time.h>
extern uint16_t RTC_TimeArr[];

void F_RTCInit(void);
void F_RTC_ReadTime(void);
void F_RTC_ReSetTime(void);

#endif



