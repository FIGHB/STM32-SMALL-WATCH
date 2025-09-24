/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-09-21 05:42:10
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-23 07:42:44
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\page_home_page.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "main.h"
#include "self_key.h"
unsigned int selfDate[] = {2025, 8, 15, 12, 59, 59};

HOME_PAGE_INDEX g_MenuOrSetIndex = FLAG_MENU_OR_SET_MENU;    // 主页面菜单选择索引
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
void f_OLEDShowDateUp(void)
{
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
    f_OLEDShowMenuAndSetTextDown(g_MenuOrSetIndex);
}

void F_MenuIndexAutoChange()
{
    if(g_MenuOrSetIndex == FLAG_MENU_OR_SET_MENU)
    {
        g_MenuOrSetIndex = FLAG_MENU_OR_SET_SET;
    }
    else
    {
        g_MenuOrSetIndex = FLAG_MENU_OR_SET_MENU;
    }
}

void F_HomePageKeyHandle(uint32_t l_keyVal)
{
    switch (l_keyVal)
    {
    case ENUM_KEY_VALUE_UP_02:
    {
        g_MenuOrSetIndex = FLAG_MENU_OR_SET_MENU;
        break;
    }
    case ENUM_KEY_VALUE_UP_00:
    {
        g_MenuOrSetIndex = FLAG_MENU_OR_SET_SET;
        break;
    }
    case ENUM_KEY_VALUE_UP_01:
    {
        if(g_MenuOrSetIndex)
        {
            S_SYS.renderPageIndex = PAGE_INDEX_SETTING;
        }
        else
        {
            S_SYS.renderPageIndex = PAGE_INDEX_MENU;
        }
        break;
    }
    
    default:
        break;
    }
}

void F_HomePageDisplayHandle(void)
{
    F_RTC_ReadTime();
    f_OLEDShowMainPage();
}

