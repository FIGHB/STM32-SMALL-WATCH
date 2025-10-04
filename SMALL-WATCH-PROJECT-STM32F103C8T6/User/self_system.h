/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-22 07:23:15
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-28 06:01:25
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_system.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _SELF_SYSTEM_H_
#define _SELF_SYSTEM_H_

#include "main.h"

#define LIMIT_MENU_INDEX_MAX    6

enum PAGE_INDEX
{
    PAGE_INDEX_HOMEPAGE,
    PAGE_INDEX_MENU,
    PAGE_INDEX_SETTING,
    PAGE_INDEX_TIME_COUNTER,
    PAGE_INDEX_DATE_SETTING,
    PAGE_INDEX_MPU_6050,
};

struct self_system
{
    unsigned b_Flag1:1;
    enum PAGE_INDEX renderPageIndex;     // 当前渲染页面索引
};

extern struct self_system S_SYS;

#endif

