#ifndef _SELF_SYSTEM_H_
#define _SELF_SYSTEM_H_

#include "main.h"

#define FLAG_MENU_OR_SET_MENU   0
#define FLAG_MENU_OR_SET_SET    1

#define LIMIT_MENU_INDEX_MAX    4

struct self_system
{
    unsigned b_MenuOrSetIndex:1;
    unsigned char menuDepth;    // ��ҳĬ�ϲ˵����Ϊ0
    unsigned char menuChooseIndex;    // ��ǰѡ�еĲ˵�����
};

extern struct self_system S_SYS;

void F_MakeSureHandle(void);
void F_ChooseHandle(void);







#endif

