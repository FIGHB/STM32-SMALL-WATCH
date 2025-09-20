/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-22 07:23:05
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-21 05:10:51
 * @FilePath: \PROJECT-SMALL-WATCH\SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_system.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "self_system.h"
struct self_system S_SYS = {0};

void F_ChooseHandleL(void)
{
    switch (S_SYS.menuDepth)
    {
    case 0:
        S_SYS.b_MenuOrSetIndex = ~S_SYS.b_MenuOrSetIndex;
        break;
    case 1:
    {
        if (g_IndexPre == DEFAULT_MENU_INDEX_X)
        {
            if (S_SYS.menuChooseIndex < LIMIT_MENU_INDEX_MAX)
            {
                S_SYS.menuChooseIndex++;
            }
            else
            {
                S_SYS.menuChooseIndex = 0;
            }
            g_IndexPre += DEFAULT_MENU_INTERVAL_X;
        }
        break;
    }

    default:
        break;
    }
}

void F_ChooseHandleR(void)
{
    switch (S_SYS.menuDepth)
    {
    case 0:
        S_SYS.b_MenuOrSetIndex = ~S_SYS.b_MenuOrSetIndex;
        break;
    case 1:
    {
        if (g_IndexPre == DEFAULT_MENU_INDEX_X)
        {
            if (S_SYS.menuChooseIndex)
            {
                S_SYS.menuChooseIndex--;
            }
            else
            {
                S_SYS.menuChooseIndex = LIMIT_MENU_INDEX_MAX;
            }
            g_IndexPre -= DEFAULT_MENU_INTERVAL_X;
        }
        break;
    }

    default:
        break;
    }
}

void F_MakeSureHandle(void)
{
    switch (S_SYS.menuDepth)
    {
    case 0:
        S_SYS.menuDepth = 1; // goto first menu such as the menu choose
        break;
    case 1:
    {
        switch (S_SYS.menuChooseIndex)
        {
        case 0:
        {   // 退回建
            S_SYS.menuDepth = 0;
            S_SYS.menuChooseIndex = 0;
            break;
        }
        case 1:
        {   // 秒表
            S_SYS.menuDepth = 2;
            S_SYS.menuFunctionIndex = 1;
            break;
        }

        default:
            break;
        }
        break;
    }
    case 2:
    {
        switch (S_SYS.menuFunctionIndex)
        {
        case 1:
        {   // 秒表
            
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
}
