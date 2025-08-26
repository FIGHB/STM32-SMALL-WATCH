/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-22 07:23:05
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-23 04:01:04
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_system.c
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "self_system.h"
struct self_system S_SYS = {0};

void F_ChooseHandle(void)
{
    switch (S_SYS.menuDepth)
    {
    case 0:
        S_SYS.b_MenuOrSetIndex = ~S_SYS.b_MenuOrSetIndex;
        break;
    case 1:
    {
        if(S_SYS.menuChooseIndex<LIMIT_MENU_INDEX_MAX)
        {
            S_SYS.menuChooseIndex++;
        }
        else
        {
            S_SYS.menuChooseIndex = 0;
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
        S_SYS.menuDepth = 1;    // goto first menu such as the menu choose
        break;
    
    default:
        break;
    }
}

