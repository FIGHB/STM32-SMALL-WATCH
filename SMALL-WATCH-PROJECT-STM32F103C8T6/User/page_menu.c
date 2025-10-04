/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-08-15 20:40:53
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-28 06:06:38
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\page_menu.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "main.h"
#include "page_menu.h"

uint8_t page1ChooseIndex;    // 菜单功能页面选择索引
void f_OLED_ShowMenuFrame()
{
    F_OLED_Show_Graph(42, 5, 44, 44, Frame44X44);
}

/**
 * @description: show the menu cho ose logo
 * @return {*}
 */
int g_IndexPre = DEFAULT_MENU_INDEX_X;
#define MENU_REMOVE_SPEED 10 // the larger, the faster
void f_OLED_ShowMenuContant()
{
    int l_Index = 0, l_ChooseIndex = 0;
    if (g_IndexPre < DEFAULT_MENU_INDEX_X)
    {
        if (g_IndexPre < DEFAULT_MENU_INDEX_X - MENU_REMOVE_SPEED)
        {
            g_IndexPre += MENU_REMOVE_SPEED;
        }
        else
        {
            g_IndexPre = DEFAULT_MENU_INDEX_X;
        }
    }
    if (g_IndexPre > DEFAULT_MENU_INDEX_X)
    {
        if (g_IndexPre > DEFAULT_MENU_INDEX_X + MENU_REMOVE_SPEED)
        {
            g_IndexPre -= MENU_REMOVE_SPEED;
        }
        else
        {
            g_IndexPre = DEFAULT_MENU_INDEX_X;
        }
    }
    f_OLED_ShowMenuFrame();

    if (g_IndexPre >= 0)
    {
        l_Index = g_IndexPre % DEFAULT_MENU_INTERVAL_X - DEFAULT_MENU_INTERVAL_X; // x轴0点负半轴第一个图标的起始坐标
        l_ChooseIndex = ((int)(page1ChooseIndex) - g_IndexPre / DEFAULT_MENU_INTERVAL_X - 1) % (LIMIT_MENU_INDEX_MAX + 1);
    }
    else
    {
        l_Index = g_IndexPre % DEFAULT_MENU_INTERVAL_X;
        l_ChooseIndex = ((int)(page1ChooseIndex) - g_IndexPre / DEFAULT_MENU_INTERVAL_X) % (LIMIT_MENU_INDEX_MAX + 1);
    }

    if (l_ChooseIndex < 0)
    {
        l_ChooseIndex += LIMIT_MENU_INDEX_MAX + 1;
    }

    while (l_Index < 128) // x坐标最大坐标为127
    {
        F_OLED_Show_Graph(l_Index, 11, 32, 32, OLED_GRAPH_F32X32[l_ChooseIndex]);
        l_Index += DEFAULT_MENU_INTERVAL_X;
        l_ChooseIndex = (++l_ChooseIndex) % (LIMIT_MENU_INDEX_MAX + 1);
    }
    /******************************************************************************************************* */
    // if(page1ChooseIndex>=2)
    // {
    //     F_OLED_Show_Graph(g_IndexPre-80,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex-2)]);
    // }
    // else
    // {
    //     F_OLED_Show_Graph(g_IndexPre-80,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex+(LIMIT_MENU_INDEX_MAX+1)-2)]);
    // }
    // if(page1ChooseIndex>=1)
    // {
    //     F_OLED_Show_Graph(g_IndexPre-40,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex-1)]);
    // }
    // else
    // {
    //     F_OLED_Show_Graph(g_IndexPre-40,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex+LIMIT_MENU_INDEX_MAX)]);
    // }
    // F_OLED_Show_Graph(g_IndexPre,11,32,32,OLED_GRAPH_F32X32[page1ChooseIndex%(LIMIT_MENU_INDEX_MAX+1)]);
    // F_OLED_Show_Graph(g_IndexPre+40,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex+1)%(LIMIT_MENU_INDEX_MAX+1)]);
    // F_OLED_Show_Graph(g_IndexPre+80,11,32,32,OLED_GRAPH_F32X32[(page1ChooseIndex+2)%(LIMIT_MENU_INDEX_MAX+1)]);
}

void f_OLEDShowMenu()
{
    f_OLED_ShowMenuContant();
    f_OLEDShowMenuAndSetTextDown(FLAG_MENU_OR_SET_MENU);
}

void F_MenuDisplayHandle(void)
{
    f_OLEDShowMenu();
}

void F_MenuKeyHandle(uint32_t l_keyVal)
{
    switch (l_keyVal)
    {
    case ENUM_KEY_VALUE_1S_02:
    case ENUM_KEY_VALUE_UP_02:
    {
        if (g_IndexPre == DEFAULT_MENU_INDEX_X)
        {
            if (page1ChooseIndex)
            {
                page1ChooseIndex--;
            }
            else
            {
                page1ChooseIndex = LIMIT_MENU_INDEX_MAX;
            }
            g_IndexPre -= DEFAULT_MENU_INTERVAL_X;
        }
        break;
    }
    case ENUM_KEY_VALUE_UP_01:
    {
        switch (page1ChooseIndex)
        {
        case 0:
        { // 退回建
            S_SYS.renderPageIndex = PAGE_INDEX_HOMEPAGE;
            break;
        }
        case 1:
        { // 秒表
            S_SYS.renderPageIndex = PAGE_INDEX_TIME_COUNTER;
            break;
        }
        case 3:
        {
            S_SYS.renderPageIndex = PAGE_INDEX_MPU_6050;
            break;
        }
        default:
            break;
        }
        break;
    }
    case ENUM_KEY_VALUE_1S_00:
    case ENUM_KEY_VALUE_UP_00:
    {
        if (g_IndexPre == DEFAULT_MENU_INDEX_X)
        {
            if (page1ChooseIndex < LIMIT_MENU_INDEX_MAX)
            {
                page1ChooseIndex++;
            }
            else
            {
                page1ChooseIndex = 0;
            }
            g_IndexPre += DEFAULT_MENU_INTERVAL_X;
        }
        break;
    }

    default:
        break;
    }
}
