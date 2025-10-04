/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-09-21 05:42:15
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-10-04 10:45:54
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\page_home_page.h
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _PAGE_HOME_PAGE_H_
#define _PAGE_HOME_PAGE_H_

typedef enum
{
    FLAG_MENU_OR_SET_MENU = 0,
    FLAG_MENU_OR_SET_SET = 1
}HOME_PAGE_INDEX;

void F_HomePageDisplayHandle(void);
extern void F_HomePageKeyHandle(uint32_t l_keyVal);
void f_OLEDShowMenuAndSetTextDown(unsigned char u8_chooseIndex);
void f_OLEDShowDateUp(void);
#endif
