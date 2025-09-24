/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-09-21 21:22:41
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-09-24 21:29:20
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\page_date_setting.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */
#include "page_date_setting.h"
#include "self_oled.h"
#include "stdint.h"

enum DATE_SETTING_INDEX
{
    DATE_SETTING_INDEX_RETURN,
    DATE_SETTING_INDEX_YEAR_THO,
    DATE_SETTING_INDEX_YEAR_HUN,
    DATE_SETTING_INDEX_YEAR_TEN,
    DATE_SETTING_INDEX_YEAR_UNI,
    DATE_SETTING_INDEX_MONTH_TEN,
    DATE_SETTING_INDEX_MONTH_UNI,
    DATE_SETTING_INDEX_DAY_TEN,
    DATE_SETTING_INDEX_DAY_UNI,
    DATE_SETTING_INDEX_HOUR_TEN,
    DATE_SETTING_INDEX_HOUR_UNI,
    DATE_SETTING_INDEX_MINUTE_TEN,
    DATE_SETTING_INDEX_MINUTE_UNI,
    DATE_SETTING_INDEX_SECOND_TEN,
    DATE_SETTING_INDEX_SECOND_UNI
};
#define DATE_SETTING_INDEX_MAX  DATE_SETTING_INDEX_SECOND_UNI

struct 
{
    unsigned b_ChooseOrSet:1;
    unsigned b_Flicker:1;
    enum DATE_SETTING_INDEX g_DateSettingIndex;
    uint8_t g_FlickerCount;
}PDS_struct;

void F_FlickerReset()
{
    PDS_struct.g_FlickerCount = 0;
    PDS_struct.b_Flicker = 0;
}

/**
 * @description: 显示时钟设置界面
 * @return {*}
 */
void F_dateSettingDisplayHandle(void)
{
    if(++PDS_struct.g_FlickerCount>=5)
    {
        PDS_struct.g_FlickerCount = 0;
        PDS_struct.b_Flicker = ~PDS_struct.b_Flicker;
    }
    F_OLED_Show_Graph(0, 0, 16, 16, IconReturnF16X16);
    f_oledPrintf(0, 16, 12, 24, "%4d-%02d-%02d", RTC_TimeArr[0], RTC_TimeArr[1], RTC_TimeArr[2]);
    f_oledPrintf(0, 40, 12, 24, "%02d:%02d:%02d", RTC_TimeArr[3], RTC_TimeArr[4], RTC_TimeArr[5]);
        switch (PDS_struct.g_DateSettingIndex)
        {
        case DATE_SETTING_INDEX_RETURN:
        {
            F_OLED_ChooseAreaReverse(0, 0, 16, 16);
            break;
        }
        case DATE_SETTING_INDEX_YEAR_THO:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(0, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(0, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_YEAR_HUN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(12, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(12, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_YEAR_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(24, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(24, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_YEAR_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(36, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(36, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_MONTH_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(60, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(60, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_MONTH_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(72, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(72, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_DAY_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(96, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(96, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_DAY_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(108, 16, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(108, 16, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_HOUR_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(0, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(0, 40, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_HOUR_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(12, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(12, 40, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_MINUTE_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(36, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(36, 40, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_MINUTE_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(48, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(48, 40, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_SECOND_TEN:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(72, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(72, 40, 12, 24);
            }
            break;
        }
        case DATE_SETTING_INDEX_SECOND_UNI:
        {
            if(PDS_struct.b_ChooseOrSet)
            {
                if(PDS_struct.b_Flicker)
                {
                    F_OLED_ChooseAreaClean(84, 40, 12, 24);
                }
            }
            else
            {
                F_OLED_ChooseAreaReverse(84, 40, 12, 24);
            }
            break;
        }
        default :
            break;
    }
}

void F_DateSettingHandle(uint8_t u8_data)
{
    switch (PDS_struct.g_DateSettingIndex)
    {
    case DATE_SETTING_INDEX_YEAR_THO:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[0] < 9000)
            {
                RTC_TimeArr[0] += 1000;
            }
        }
        else
        {
            if(RTC_TimeArr[0] > 1000)
            {
                RTC_TimeArr[0] -= 1000;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_YEAR_HUN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[0] < 9900)
            {
                RTC_TimeArr[0] += 100;
            }
        }
        else
        {
            if(RTC_TimeArr[0] > 100)
            {
                RTC_TimeArr[0] -= 100;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_YEAR_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[0] < 9990)
            {
                RTC_TimeArr[0] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[0] > 10)
            {
                RTC_TimeArr[0] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_YEAR_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[0] < 9999)
            {
                RTC_TimeArr[0] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[0] > 1)
            {
                RTC_TimeArr[0] -= 1;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_MONTH_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[1] < 3)
            {
                RTC_TimeArr[1] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[1] > 9)
            {
                RTC_TimeArr[1] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_MONTH_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[1] < 12)
            {
                RTC_TimeArr[1] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[1] > 1)
            {
                RTC_TimeArr[1] -= 1;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_DAY_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[2] < 22)
            {
                RTC_TimeArr[2] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[2] > 10)
            {
                RTC_TimeArr[2] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_DAY_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[2] < 31)
            {
                RTC_TimeArr[2] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[2] > 1)
            {
                RTC_TimeArr[2] -= 1;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_HOUR_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[3] < 14)
            {
                RTC_TimeArr[3] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[3] > 9)
            {
                RTC_TimeArr[3] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_HOUR_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[3] < 23)
            {
                RTC_TimeArr[3] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[3] > 0)
            {
                RTC_TimeArr[3] -= 1;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_MINUTE_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[4] < 50)
            {
                RTC_TimeArr[4] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[4] > 9)
            {
                RTC_TimeArr[4] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_MINUTE_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[4] < 59)
            {
                RTC_TimeArr[4] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[4] > 0)
            {
                RTC_TimeArr[4] -= 1;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_SECOND_TEN:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[5] < 50)
            {
                RTC_TimeArr[5] += 10;
            }
        }
        else
        {
            if(RTC_TimeArr[5] > 9)
            {
                RTC_TimeArr[5] -= 10;
            }
        }
        break;
    }
    case DATE_SETTING_INDEX_SECOND_UNI:
    {
        if(u8_data)
        {
            if(RTC_TimeArr[5] < 59)
            {
                RTC_TimeArr[5] += 1;
            }
        }
        else
        {
            if(RTC_TimeArr[5] > 0)
            {
                RTC_TimeArr[5] -= 1;
            }
        }
        break;
    }
    default:
        break;
    }
}

extern void F_dateSettingKeyHandle(uint32_t l_keyVal)
{
    switch (l_keyVal)
    {
    case ENUM_KEY_VALUE_1S_00:
    case ENUM_KEY_VALUE_UP_00:
    {
        F_FlickerReset();
        if(PDS_struct.b_ChooseOrSet==0)
        {
            if(PDS_struct.g_DateSettingIndex<DATE_SETTING_INDEX_MAX)
            {
                PDS_struct.g_DateSettingIndex++;
            }
        }
        else
        {
            F_DateSettingHandle(1);
        }
        break;
    }
    case ENUM_KEY_VALUE_UP_01:
    {
        F_FlickerReset();
        if(PDS_struct.g_DateSettingIndex == DATE_SETTING_INDEX_RETURN)
        {
            S_SYS.renderPageIndex = PAGE_INDEX_SETTING;
            F_RTC_ReSetTime();
        }
        else
        {
            PDS_struct.b_ChooseOrSet = ~PDS_struct.b_ChooseOrSet;
        }
        break;
    }
    case ENUM_KEY_VALUE_1S_02:
    case ENUM_KEY_VALUE_UP_02:
    {
        F_FlickerReset();
        if(PDS_struct.b_ChooseOrSet==0)
        {
            if(PDS_struct.g_DateSettingIndex)
            {
                PDS_struct.g_DateSettingIndex--;
            }
        }
        else
        {
            F_DateSettingHandle(0);
        }
        break;
    }
    default:
        break;
    }
}
