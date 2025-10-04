/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-09-21 05:47:24
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-10-04 11:08:43
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_display.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "self_display.h"

void F_displayHandle()
{
    F_OLED_Clear();
    switch (S_SYS.renderPageIndex)
    {
    case PAGE_INDEX_HOMEPAGE:
    {
        F_HomePageDisplayHandle();
        break;
    }
    case PAGE_INDEX_MENU:
    {
        F_MenuDisplayHandle();
        break;
    }
    case PAGE_INDEX_SETTING:
    {
        F_SettingDisplayHandle();
        break;
    }
    case PAGE_INDEX_TIME_COUNTER:
    {
        F_TimeCounterDisplayHandle();
        break;
    }
    case PAGE_INDEX_DATE_SETTING:
    {
        F_dateSettingDisplayHandle();
        break;
    }
    case PAGE_INDEX_MPU_6050:
    {
        F_MPU6050DisplayHandle();
        break;
    }
    default:
        break;
    }
    F_OLED_Disp_Update();
}
