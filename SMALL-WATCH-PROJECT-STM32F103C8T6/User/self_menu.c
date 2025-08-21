/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-08-15 20:40:53
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-22 07:34:30
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_menu.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "self_menu.h"
unsigned int selfDate[] = {2025, 8, 15, 12, 59, 59};

/**
 * @description: 主页显示内容
 * @return {*}
 */
void f_OLEDShowMainPage()
{
    F_RTC_ReadTime();
    f_oledPrintf(0, 0, 6, 8, "%4d-%02d-%02d", RTC_TimeArr[0], RTC_TimeArr[1], RTC_TimeArr[2]);
    f_oledPrintf(16, 16, 12, 24, "%02d:%02d:%02d", RTC_TimeArr[3], RTC_TimeArr[4], RTC_TimeArr[5]);
    f_oledPrintf(0, 48, 8, 16, "菜单");
    f_oledPrintf(96, 48, 8, 16, "设置");
    switch (S_SYS.b_MenuOrSetIndex)
    {
    case 0:
        F_OLED_ChooseAreaReverse(0, 48, 32, 16);
        break;
    case 1:
        F_OLED_ChooseAreaReverse(96, 48, 32, 16);
        break;
    default:
        break;
    }
}
    void F_showClockUI()
    {
        f_OLEDShowMainPage();
        
        F_OLED_Disp_Update();
    }
