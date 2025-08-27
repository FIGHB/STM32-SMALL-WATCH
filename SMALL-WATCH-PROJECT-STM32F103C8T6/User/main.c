/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-19 20:44:33
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-27 22:50:13
 * @FilePath: \PROJECT-SMALL-WATCH\SMALL-WATCH-PROJECT-STM32F103C8T6\User\main.c
 * @Description: to make a small watch by STM32F103C8T6
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "main.h"
volatile uint8_t g_u8Time4msCount = 0;
volatile uint8_t g_u8Time100msCount = 0;
volatile uint8_t g_u8Time1sCount = 0;
int main(void)
{
	// unsigned int j = 0;
	F_timer2Init();
	F_KeyInit();
	// F_RTCInit();
	F_OLED_Init();
	// F_OLED_Show_Graph(0,30,16,16,OLED_CF16x16[2].Data);
	// F_showClockUI();
	// f_OLED_ShowChar(0,0,6,8, '#');
	// f_oledPrintf(16,16,8,16,"Äã");
	// f_oledShowString(16,16,8,16, "ÄãºÃºÃ½ç");

	// F_OLED_Show_Graph(0,0,16,16,OLED_CF16x16[4].Data);
	// f_oledPrintf(12,0,6,8,"%d:%d:%d",-11%8,-2%10,03%10);
	// f_OLED_ShowChar(12, 0, 6, 8, '?');
	F_OLED_Disp_Update();
	while (1)
	{
		if (g_u8Time4msCount > 3)
		{
			g_u8Time4msCount -= 4;
			g_u8Time1sCount++;
			g_u8Time100msCount++;
			F_KeyValueHandler();
			// f_oledPrintf(0,0,12,14,"%02d",g_ShowNum);
		}

		if (g_u8Time100msCount >= 25)
		{
			g_u8Time100msCount -= 25;
			F_showClockUI();
		}

		if (g_u8Time1sCount >= 250)
		{
			g_u8Time1sCount -= 250;
			
		}
	}
}
