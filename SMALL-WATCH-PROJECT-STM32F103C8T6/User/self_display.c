#include "self_display.h"

void F_displayHandle()
{
    F_RTC_ReadTime();
    F_OLED_Clear();
    switch (S_SYS.renderPageIndex)
    {
    case PAGE_INDEX_HOMEPAGE:
    {
        F_HomePageDisplayHandle();
        break;
    }
    case PAGE_INDEX_MENU:
    {
        F_MenuDisplayHandle();
        break;
    }
    case PAGE_INDEX_SETTING:
    {
        F_SettingDisplayHandle();
        break;
    }
    case PAGE_INDEX_TIME_COUNTER:
    {
        F_TimeCounterDisplayHandle();
        break;
    }
    default:
        break;
    }
    F_OLED_Disp_Update();
}
