#ifndef _SELF_RTC_H_
#define _SELF_RTC_H_
#include "main.h"
#include <time.h>
extern uint16_t MyRTC_Time[];

void F_RTCInit(void);
void MyRTC_ReadTime(void);

#endif



