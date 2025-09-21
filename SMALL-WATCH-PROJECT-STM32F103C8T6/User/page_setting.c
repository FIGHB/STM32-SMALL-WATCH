#include "page_setting.h"

#include "self_key.h"
enum SETTING_INDEX
{
    SETTING_INDEX_RETURN = 0,
    SETTING_INDEX_DATE
};
#define LIMIT_SETTING_INDEX_MAX SETTING_INDEX_DATE
enum SETTING_INDEX g_settingIndex = SETTING_INDEX_RETURN;

enum DATE_SETTING_INDEX
{
    DATE_SETTING_INDEX_YEAR = 0,
    DATE_SETTING_INDEX_MONTH,
    DATE_SETTING_INDEX_DAY,
};
#define LIMIT_DATE_SETTING_INDEX_MAX DATE_SETTING_INDEX_DAY
enum DATE_SETTING_INDEX g_DateSettingIndex = DATE_SETTING_INDEX_YEAR;

void F_SettingDisplayHandle(void)
{
    F_OLED_Show_Graph(5, 0, 16, 16, IconReturnF16X16);
    f_oledPrintf(5, 16, 8, 16, "日期时间设置");
    switch (g_settingIndex)
    {
    case SETTING_INDEX_RETURN:
        F_OLED_ChooseAreaReverse(5, 0, 16, 16);
        break;
    case SETTING_INDEX_DATE:
        F_OLED_ChooseAreaReverse(5, 16, 96, 16);
        break;
    default:
        break;
    }
}

void F_SettingKeyHandle(uint32_t l_keyVal)
{
    switch (l_keyVal)
    {
    case ENUM_KEY_VALUE_UP_00:
    {
        if(g_settingIndex<LIMIT_SETTING_INDEX_MAX)
        {
            g_settingIndex++;
        }
        break;
    }
    case ENUM_KEY_VALUE_UP_01:
    {
        switch (g_settingIndex)
        {
        case SETTING_INDEX_RETURN:
            S_SYS.renderPageIndex = PAGE_INDEX_HOMEPAGE;
            break;
        case SETTING_INDEX_DATE:
            break;
        default:
            break;
        }
        break;
    }
    case ENUM_KEY_VALUE_UP_02:
    {
        if(g_settingIndex)
        {
            g_settingIndex--;
        }
        break;
    }
    
    default:
        break;
    }
    if(S_SYS.renderPageIndex == PAGE_INDEX_HOMEPAGE)
    {   // 推出时重置当前页面
        g_settingIndex = SETTING_INDEX_RETURN;
    }
}
