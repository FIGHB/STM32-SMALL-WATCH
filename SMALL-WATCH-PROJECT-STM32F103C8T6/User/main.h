/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-19 22:05:46
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-10-04 10:45:41
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\main.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef _MAIN_MAIN_H_
#define _MAIN_MAIN_H_

#define BIT0 0X01
#define BIT1 0X02
#define BIT2 0X04
#define BIT3 0X08
#define BIT4 0X10
#define BIT5 0X20
#define BIT6 0X40
#define BIT7 0X80

#include "stm32f10x.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stdint.h>
#include "self_system.h"
#include "self_display.h"
#include "self_oled_model.h"
#include "self_oled.h"
#include "self_time2.h"
#include "self_delay.h"
#include "self_rtc.h"
#include "page_time_counter.h"
#include "page_home_page.h"
#include "page_menu.h"
#include "page_setting.h"
#include "page_date_setting.h"
#include "page_mpu_6050.h"

extern volatile uint8_t g_u8Time4msCount;

#endif





