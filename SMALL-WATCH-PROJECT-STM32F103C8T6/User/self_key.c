/*
 * @Author: FIGHB li839521927@gmail.com
 * @Date: 2025-08-21 02:41:29
 * @LastEditors: FIGHB li839521927@gmail.com
 * @LastEditTime: 2025-08-21 03:49:02
 * @FilePath: \SMALL-WATCH-PROJECT-STM32F103C8T6\User\self_key.c
 * @Description:
 *
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved.
 */

#include "self_key.h"

void F_KeyInit(void)
{ // A1 A8 A11
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t F_KeyValueScan(void)
{
    uint8_t l_u8KeyValue = 0;
    static uint8_t s_u8KeyValueLast = 0, s_u8KeyValueRet = 0, s_u8SameCount = 0;
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
    {
        l_u8KeyValue |= BIT0;
    }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)
    {
        l_u8KeyValue |= BIT1;
    }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)
    {
        l_u8KeyValue |= BIT2;
    }

    if (s_u8KeyValueLast == l_u8KeyValue)
    {
        if (++s_u8SameCount > 3)
        {
            s_u8SameCount = 0;
            s_u8KeyValueRet = s_u8KeyValueLast;
        }
    }
    else
    {
        s_u8KeyValueLast = l_u8KeyValue;
        s_u8KeyValueRet = 0;
    }
    return s_u8KeyValueRet;
}

uint8_t g_ShowNum = 12;
#define C_KEY_DOWN_TIME_20MS    5
#define C_KEY_DOWN_TIME_1000MS  250
#define C_KEY_DOWN_TIME_3000MS  750
void F_KeyValueHandler(void)
{
    unsigned int l_u32KeyValuePre = 0;
    static unsigned int s_u32KeyValueLast = 0, s_u32KeyUpValue = 0, s_u32SameCount = 0;
    l_u32KeyValuePre = F_KeyValueScan();

    if (s_u32KeyValueLast == l_u32KeyValuePre)
    {
        if(s_u32SameCount<65536)
        {
            s_u32SameCount++;
        }
    }
    else
    {
        s_u32KeyValueLast = l_u32KeyValuePre;
        s_u32SameCount = 0;
    }

    if (s_u32KeyValueLast)
    {
        if (s_u32SameCount == 1)
        {
            s_u32KeyUpValue = s_u32KeyValueLast;
        }

        if(C_KEY_DOWN_TIME_20MS == s_u32SameCount)
        {
            switch (s_u32KeyValueLast)
            {
                // code
            
            default:
                break;
            }
        }

        if (C_KEY_DOWN_TIME_1000MS == s_u32SameCount)
        {
            switch (s_u32KeyValueLast)
            {
            case BIT0:
                /* code */
                g_ShowNum = 11;
                s_u32KeyUpValue = 0;
                break;
            case BIT1:
                /* code */
                g_ShowNum = 12;
                s_u32KeyUpValue = 0;
                break;
            case BIT2:
                /* code */
                g_ShowNum = 13;
                s_u32KeyUpValue = 0;
                break;

            default:
                break;
            }
        }

        if (C_KEY_DOWN_TIME_3000MS == s_u32SameCount)
        {
            switch (s_u32KeyValueLast)
            {
            case BIT0:
                /* code */
                g_ShowNum = 31;
                s_u32KeyUpValue = 0;
                break;
            case BIT1:
                /* code */
                g_ShowNum = 32;
                s_u32KeyUpValue = 0;
                break;
            case BIT2:
                /* code */
                g_ShowNum = 33;
                s_u32KeyUpValue = 0;
                break;

            default:
                break;
            }
        }
    }
    else
    {
        switch (s_u32KeyUpValue)
        {
        case BIT0:
            g_ShowNum = 1;
            break;
        case BIT1:
            g_ShowNum = 2;
            break;
        case BIT2:
            g_ShowNum = 3;
            break;

        default:
            break;
        }
        s_u32KeyUpValue = 0;
    }
}
