/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-08-15 20:40:53
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-26 23:56:03
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_menu.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "self_menu.h"
unsigned int selfDate[] = {2025, 8, 15, 12, 59, 59};

/**
 * @description: 底部展示菜单和设置文本内容
 * @return {*}
 */
void f_OLEDShowMenuAndSetTextDown(unsigned char u8_chooseIndex)
{
    f_oledPrintf(0, 48, 8, 16, "菜单");
    f_oledPrintf(96, 48, 8, 16, "设置");
    switch (u8_chooseIndex)
    {
    case FLAG_MENU_OR_SET_MENU:
        F_OLED_ChooseAreaReverse(0, 48, 32, 16);
        break;
    case FLAG_MENU_OR_SET_SET:
        F_OLED_ChooseAreaReverse(96, 48, 32, 16);
        break;
    default:
        break;
    }
}

/**
 * @description: show the date on the top area
 * @return {*}
 */
void f_OLEDShowDateUp()
{
    F_RTC_ReadTime();
    f_oledPrintf(0, 0, 6, 8, "%4d-%02d-%02d", RTC_TimeArr[0], RTC_TimeArr[1], RTC_TimeArr[2]);
}

/**
 * @description: show the Time in the midden area
 * @return {*}
 */
void f_OLEDShowTimeMid()
{
    f_oledPrintf(16, 16, 12, 24, "%02d:%02d:%02d", RTC_TimeArr[3], RTC_TimeArr[4], RTC_TimeArr[5]);
}

/**
 * @description: 主页显示内容
 * @return {*}
 */
void f_OLEDShowMainPage()
{
    f_OLEDShowDateUp();
    f_OLEDShowTimeMid();
    f_OLEDShowMenuAndSetTextDown(S_SYS.b_MenuOrSetIndex);
}

void f_OLED_ShowMenuFrame()
{
    F_OLED_Set_Data(42,10,44,44,Frame44X44);
}

/**
 * @description: show the menu cho ose logo
 * @return {*}
 */
void f_OLED_ShowMenuContant()
{
    f_OLED_ShowMenuFrame();
}

void f_OLEDShowMenu()
{
    f_OLEDShowDateUp();
    f_OLED_ShowMenuContant();
    f_OLEDShowMenuAndSetTextDown(FLAG_MENU_OR_SET_MENU);
}

void f_OLEDShowSet()
{
    f_OLEDShowDateUp();
    f_OLEDShowMenuAndSetTextDown(FLAG_MENU_OR_SET_MENU);
}

void F_showClockUI()
{
    F_RTC_ReadTime();
    F_OLED_Clear();
    switch (S_SYS.menuDepth)
    {
    case 0:
    {
        f_OLEDShowMainPage();
        break;
    }
    case 1:
    {
        switch (S_SYS.b_MenuOrSetIndex)
        {
        case FLAG_MENU_OR_SET_MENU:
        {
            f_OLEDShowMenu();
            break;
        }
        case FLAG_MENU_OR_SET_SET:
        {
            f_OLEDShowSet();
            break;
        }
        default:
            break;
        }
        
        break;
    }
    default:
        break;
    }
    F_OLED_Disp_Update();
}
