/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-19 20:44:33
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-21 21:58:52
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\main.c
 * @Description: to make a small watch by STM32F103C8T6
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "main.h"
volatile uint8_t g_u8Time4msCount = 0;
volatile uint8_t g_u8Time1sCount = 0;
int main(void)
{
	unsigned int i = 0;
	// unsigned int j = 0;
	F_timer2Init();
	F_KeyInit();
	F_RTCInit();
	F_OLED_Init();
	// F_OLED_Set_Data(0,30,16,16,OLED_CF16x16[2].Data);
	// F_showClockUI();
	// f_OLED_ShowChar(0,0,6,8, '#');
	// f_oledPrintf(16,16,8,16,"Äã");
	// f_oledShowString(16,16,8,16, "ÄãºÃºÃ½ç");

	// F_OLED_Set_Data(0,0,16,16,OLED_CF16x16[4].Data);
	// f_oledPrintf(12,0,6,8,"%d-%d-%d",21,22,23);
	// f_OLED_ShowChar(12, 0, 6, 8, '?');
	F_OLED_Disp_Update();
	while (1)
	{
		if (g_u8Time4msCount > 3)
		{
			g_u8Time4msCount -= 4;
			g_u8Time1sCount++;
			F_KeyValueHandler();
		}

		if (g_u8Time1sCount >= 250)
		{
			g_u8Time1sCount -= 250;
			i++;
			MyRTC_ReadTime();
			f_oledPrintf(0, 0, 6, 8, "%4d-%02d-%02d", MyRTC_Time[0], MyRTC_Time[1], MyRTC_Time[2]);
			f_oledPrintf(20, 20, 12, 24, "%02d:%02d:%02d", MyRTC_Time[3], MyRTC_Time[4], MyRTC_Time[5]);
			F_OLED_Disp_Update();
		}
	}
}
