/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-22 07:23:15
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-27 20:02:57
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_system.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_SYSTEM_H_
#define _SELF_SYSTEM_H_

#include "main.h"

#define FLAG_MENU_OR_SET_MENU   0
#define FLAG_MENU_OR_SET_SET    1

#define LIMIT_MENU_INDEX_MAX    6

struct self_system
{
    unsigned b_MenuOrSetIndex:1;
    unsigned char menuDepth;    // 首页默认菜单深度为0
    unsigned char menuChooseIndex;    // 当前选中的菜单索引
};

extern struct self_system S_SYS;

void F_MakeSureHandle(void);
void F_ChooseHandleL(void);
void F_ChooseHandleR(void);







#endif

