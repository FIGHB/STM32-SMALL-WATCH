#ifndef _MAIN_H_
#define _MAIN_H_

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
#include "self_oled_model.h"
#include "self_oled.h"
#include "self_menu.h"
#include "self_time2.h"
#include "self_delay.h"
#include "self_key.h"
#include "self_rtc.h"

extern volatile uint8_t g_u8Time4msCount;

#endif





