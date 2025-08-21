#ifndef _SELF_RTC_H_
#define _SELF_RTC_H_
#include "main.h"
#include <time.h>
extern uint16_t RTC_TimeArr[];

void F_RTCInit(void);
void F_RTC_ReadTime(void);

#endif



