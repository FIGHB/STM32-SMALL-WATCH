#include "self_rtc.h"
uint16_t RTC_TimeArr[] = {2025, 1, 1, 23, 59, 55}; // ����ȫ�ֵ�ʱ�����飬�������ݷֱ�Ϊ�ꡢ�¡��ա�ʱ���֡���
void F_RTC_ReSetTime(void);
/**
 * @description: 32.768kHz ���þ���
 * @return {*}
 */
void F_RTCInit(void)
{
    /*����ʱ��*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // ����PWR��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE); // ����BKP��ʱ��

    /*���ݼĴ�������ʹ��*/
    PWR_BackupAccessCmd(ENABLE); // ʹ��PWR�����Ա��ݼĴ����ķ���

    // ͨ��д�뱸�ݼĴ����ı�־λ���ж�RTC�Ƿ��ǵ�һ������
    // if������ִ�е�һ�ε�RTC����
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        RCC_LSEConfig(RCC_LSE_ON); // ����LSEʱ��
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
            ; // �ȴ�LSE׼������

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // ѡ��RTCCLK��ԴΪLSE
        RCC_RTCCLKCmd(ENABLE);                  // RTCCLKʹ��

        RTC_WaitForSynchro();  // �ȴ�ͬ��
        RTC_WaitForLastTask(); // �ȴ���һ�β������

        RTC_SetPrescaler(32768 - 1); // ����RTCԤ��Ƶ����Ԥ��Ƶ��ļ���Ƶ��Ϊ1Hz
        RTC_WaitForLastTask();       // �ȴ���һ�β������

        F_RTC_ReSetTime(); // ����ʱ�䣬���ô˺�����ȫ��������ʱ��ֵˢ�µ�RTCӲ����·

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5); // �ڱ��ݼĴ���д���Լ��涨�ı�־λ�������ж�RTC�ǲ��ǵ�һ��ִ������
    }
    else // RTC���ǵ�һ������
    {
        RTC_WaitForSynchro();  // �ȴ�ͬ��
        RTC_WaitForLastTask(); // �ȴ���һ�β������
    }
}

void F_RTC_ReSetTime(void)
{
    time_t time_cnt;     // �������������������
    struct tm time_date; // ��������ʱ����������

    time_date.tm_year = RTC_TimeArr[0] - 1900; // �������ʱ�丳ֵ������ʱ��ṹ��
    time_date.tm_mon = RTC_TimeArr[1] - 1;
    time_date.tm_mday = RTC_TimeArr[2];
    time_date.tm_hour = RTC_TimeArr[3];
    time_date.tm_min = RTC_TimeArr[4];
    time_date.tm_sec = RTC_TimeArr[5];

    time_cnt = mktime(&time_date) - 8 * 60 * 60; // ����mktime������������ʱ��ת��Ϊ���������ʽ
                                                 //- 8 * 60 * 60Ϊ��������ʱ������

    RTC_SetCounter(time_cnt); // ���������д�뵽RTC��CNT��
    RTC_WaitForLastTask();    // �ȴ���һ�β������
}

/**
 * @description: to get the most recent time into the RTC_TimeArr arr
 * @return {*}
 */
void F_RTC_ReadTime(void)
{
    time_t time_cnt;     // �������������������
    struct tm time_date; // ��������ʱ����������

    time_cnt = RTC_GetCounter() + 8 * 60 * 60; // ��ȡRTC��CNT����ȡ��ǰ���������
                                               //+ 8 * 60 * 60Ϊ��������ʱ������

    time_date = *localtime(&time_cnt); // ʹ��localtime���������������ת��Ϊ����ʱ���ʽ

    RTC_TimeArr[0] = time_date.tm_year + 1900; // ������ʱ��ṹ�帳ֵ�������ʱ��
    RTC_TimeArr[1] = time_date.tm_mon + 1;
    RTC_TimeArr[2] = time_date.tm_mday;
    RTC_TimeArr[3] = time_date.tm_hour;
    RTC_TimeArr[4] = time_date.tm_min;
    RTC_TimeArr[5] = time_date.tm_sec;
}
