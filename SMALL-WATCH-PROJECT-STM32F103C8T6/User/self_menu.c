/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-08-15 20:40:53
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-08-16 03:08:21
 * @FilePath: \KEIL-25002-LED-PROJECT\User\self_menu.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "self_menu.h"
#include "self_oled.h"
unsigned int selfDate[] = {2025,8,15,12,59,59};

void f_OLEDShowDate()
{
    f_oledPrintf(0,0,6,8,"%d-%d-%d", selfDate[0], selfDate[1], selfDate[2]);
    f_oledPrintf(16,16,12,24,"%02d-%02d-%02d", selfDate[3], selfDate[4], selfDate[5]);
}

// œ‘ æ÷˜“≥ ±÷”UI
void F_showClockUI()
{
    f_OLEDShowDate();
}





