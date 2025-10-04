#include "page_mpu_6050.h"
#include "MPU6050.h"
#include "self_key.h"

uint8_t b_mpu_6050_init;
uint8_t g_u8_Id_MPU6050 = 0;
int16_t AX, AY, AZ, GX, GY, GZ; // 定义用于存放各个数据的变量
void F_MPU6050DisplayHandle(void)
{
    if (b_mpu_6050_init == 0)
    {
        b_mpu_6050_init = 1;
        MPU6050_Init();
        g_u8_Id_MPU6050 = MPU6050_GetID();
    }
    f_oledPrintf(0, 0, 8, 16, "ID:0x%x", g_u8_Id_MPU6050);
    MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ); // 获取MPU6050的数据
    f_oledPrintf(0, 20, 6, 8, "AX:%d", AX);
    f_oledPrintf(0, 32, 6, 8, "AY:%d", AY);
    f_oledPrintf(0, 44, 6, 8, "AZ:%d", AZ);
    f_oledPrintf(63, 20, 6, 8, "GX:%d", GX);
    f_oledPrintf(63, 32, 6, 8, "GY:%d", GY);
    f_oledPrintf(63, 44, 6, 8, "GZ:%d", GZ);
}

void F_MPU6050KeyHandle(uint32_t l_keyVal)
{
    switch (l_keyVal)
    {
    case ENUM_KEY_VALUE_UP_00:
    case ENUM_KEY_VALUE_UP_01:
    case ENUM_KEY_VALUE_UP_02:
    {
        S_SYS.renderPageIndex = PAGE_INDEX_MENU;
        break;
    }
    default:
        break;
    }
}
