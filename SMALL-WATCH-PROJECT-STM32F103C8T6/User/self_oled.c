#include "self_oled.h"

unsigned char g_OLED_Disp_Arr[8][128];

void F_SetPinSDA(uint8_t BitValue)
{
	GPIO_WriteBit(PIN_SDA_GPIOX, PIN_SDA_GPIO_Pin_X, (BitAction)BitValue);
}

void F_SetPinSCL(uint8_t BitValue)
{
	GPIO_WriteBit(PIN_SCL_GPIOX, PIN_SCL_GPIO_Pin_X, (BitAction)BitValue);
}

void F_IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义结构体变量
	uint32_t i, j;

	/*在初始化前，加入适量延时，待OLED供电稳定*/
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1000; j++)
			;
	}

	/*开启时钟*/
	RCC_APB2PeriphClockCmd(PIN_SCL_RCC_APB2Periph_GPIOX, ENABLE); // 开启GPIOC的时钟
	RCC_APB2PeriphClockCmd(PIN_SDA_RCC_APB2Periph_GPIOX, ENABLE); // 开启GPIOC的时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // GPIO模式，赋值为
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度，赋值为50MHz

	GPIO_InitStructure.GPIO_Pin = PIN_SCL_GPIO_Pin_X; // GPIO引脚，赋值为第13号引脚
	GPIO_Init(PIN_SCL_GPIOX, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_SDA_GPIO_Pin_X; // GPIO引脚，赋值为第13号引脚
	GPIO_Init(PIN_SDA_GPIOX, &GPIO_InitStructure);
	F_SetPinSCL(1);
	F_SetPinSDA(1);
}

void F_IIC_Start(void)
{
	F_SetPinSDA(1);
	F_SetPinSCL(1);
	F_SetPinSDA(0);
	F_SetPinSCL(0); // 归0 确保后续修改 SDA 数据
}

void F_IIC_End(void)
{
	F_SetPinSDA(0);
	F_SetPinSCL(1);
	F_SetPinSDA(1);
}

void F_IIC_SendByte(uint8_t u8_data)
{
	uint8_t i = 0;
	for (i = 0; i < 8; i++)
	{
		F_SetPinSDA(!!(u8_data & (0x80 >> i)));
		F_SetPinSCL(1);
		F_SetPinSCL(0);
	}
	// 免ACK，多跑一轮
	F_SetPinSCL(1);
	F_SetPinSCL(0);
}

void F_OLED_WriteCommand(uint8_t u8_command)
{
	F_IIC_Start();
	F_IIC_SendByte(0x78); // 从机地址
	F_IIC_SendByte(0x00); // 写命令
	F_IIC_SendByte(u8_command);
	F_IIC_End();
}

void F_OLED_SendByteArr(uint8_t *dataArr, uint8_t u8_count)
{
	uint8_t i = 0;
	uint8_t j = 0;

	F_IIC_Start();
	F_IIC_SendByte(0x78); // 从机地址
	F_IIC_SendByte(0x40); // 控制字节，给0x40，表示即将写数据
	for (i = 0; i < u8_count; i++)
	{
		j = dataArr[i];
		F_IIC_SendByte(j);
	}
	F_IIC_End();
}

void F_OLED_Clear(void)
{
	uint8_t i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 128; j++)
		{
			g_OLED_Disp_Arr[i][j] = 0x00;
		}
	}
}

void F_OLED_SetCursor(uint8_t u8_pageIndex, uint8_t X)
{
	/*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
	/*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
	/*屏幕的起始列接在了第2列，而不是第0列*/
	/*所以需要将X加2，才能正常显示*/
	X += 2;
	/*通过指令设置页地址和列地址*/
	F_OLED_WriteCommand(0xB0 | u8_pageIndex);	   // 设置页位置
	F_OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
	F_OLED_WriteCommand(0x00 | (X & 0x0F));		   // 设置X位置低4位
}

void F_OLED_Disp_Update(void)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		F_OLED_SetCursor(i, 0);
		F_OLED_SendByteArr(g_OLED_Disp_Arr[i], 128);
	}
}

/**
 * @description:
 * @param {uint8_t} pos_x	显示内容左上角 x 轴坐标
 * @param {uint8_t} pos_y   显示内容左上角 y 轴坐标
 * @param {uint8_t} width   显示内容列长
 * @param {uint8_t} height 显示内容行高
 * @param {uint8_t} *data_arr 显示的数据，按照行列式 排列，第一个字节代表左上角第一列8个点，第二个字节代表第二列前8个点
 * @return {*}
 */
void F_OLED_Set_Data(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height, const uint8_t *data_arr)
{
	unsigned int i;
	uint8_t j, x, y, page, shift;
	// 将对应字模数据设置到相应数据点上
	j = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			x = pos_x + j;
			y = pos_y + i;
			page = y / 8;
			shift = y % 8;
			if (x < 128 && page < 8)
			{ // 越界判定
				if (data_arr[j + i / 8 * width] & (0x01 << (i % 8)))
				{ // 置1
					g_OLED_Disp_Arr[page][x] |= (0x01 << shift);
				}
				else
				{ // 置0
					g_OLED_Disp_Arr[page][x] &= ~(0x01 << (shift));
				}
			}
		}
	}
}

void F_OLED_Init()
{
	/*GPIO初始化*/
	F_IIC_Init();

	F_OLED_WriteCommand(0xAE); // 关闭显示

	F_OLED_WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
	F_OLED_WriteCommand(0x80);

	F_OLED_WriteCommand(0xA8); // 设置多路复用率
	F_OLED_WriteCommand(0x3F);

	F_OLED_WriteCommand(0xD3); // 设置显示偏移
	F_OLED_WriteCommand(0x00);

	F_OLED_WriteCommand(0x40); // 设置显示开始行

	F_OLED_WriteCommand(0xA1); // 设置左右方向，0xA1正常 0xA0左右反置

	F_OLED_WriteCommand(0xC8); // 设置上下方向，0xC8正常 0xC0上下反置

	F_OLED_WriteCommand(0xDA); // 设置COM引脚硬件配置
	F_OLED_WriteCommand(0x12);

	F_OLED_WriteCommand(0x81); // 设置对比度控制
	F_OLED_WriteCommand(0xCF);

	F_OLED_WriteCommand(0xD9); // 设置预充电周期
	F_OLED_WriteCommand(0xF1);

	F_OLED_WriteCommand(0xDB); // 设置VCOMH取消选择级别
	F_OLED_WriteCommand(0x30);

	F_OLED_WriteCommand(0xA4); // 设置整个显示打开/关闭

	F_OLED_WriteCommand(0xA6); // 设置正常/倒转显示

	F_OLED_WriteCommand(0x8D); // 设置充电泵
	F_OLED_WriteCommand(0x14);

	F_OLED_WriteCommand(0xAF); // 开启显示

	F_OLED_Clear(); // OLED清屏
	F_OLED_Disp_Update();
}

void f_OLED_ShowChar(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char u8_char)
{
	if (width == 6)
	{
		F_OLED_Set_Data(x, y, 6, 8, OLED_ASCII_F6x8[u8_char - ' ']);
	}
	else if (width == 8)
	{
		F_OLED_Set_Data(x, y, 8, 16, OLED_ASCII_F8x16[u8_char - ' ']);
	}
	else if (width == 12)
	{
		F_OLED_Set_Data(x, y, 12, 24, OLED_ASCII_F12x24[u8_char - ' ']);
	}
	return;
}

void f_oled_ShowHexString(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *int8_str)
{
	uint8_t len, i, offSet;
	uint8_t j;
	len = strlen(int8_str);
	offSet = x;

	f_OLED_ShowChar(offSet, y, width, height, '0');
	offSet += width;
	f_OLED_ShowChar(offSet, y, width, height, 'x');
	offSet += width;
	for (i = 0; i < len; i++)
	{
		j = (uint8_t)int8_str[i];
		j = j >> 4;
		j = j & 0x0f;
		if (j > 9)
		{
			f_OLED_ShowChar(offSet, y, width, height, 'A' + j - 10);
		}
		else
		{
			f_OLED_ShowChar(offSet, y, width, height, '0' + j);
		}
		offSet += width;
		j = (((uint8_t)int8_str[i]) & 0x0f);
		if (j > 9)
		{
			f_OLED_ShowChar(offSet, y, width, height, 'A' + j - 10);
		}
		else
		{
			f_OLED_ShowChar(offSet, y, width, height, '0' + j);
		}
		offSet += width;
	}
}

void f_oledShowString(unsigned char x, unsigned char y, unsigned char width, unsigned char height, const char *int8_str)
{
	uint8_t i=0, xOffSet=0;
	uint16_t index_CF=0;
	xOffSet = x;
#ifdef OLED_CHARSET_UTF8
	char singleChar[5];
#endif

#ifdef OLED_CHARSET_GB2312
	char singleChar[5];
#endif

		while(int8_str[i])
		{ // to visit the wholl char in the string
#ifdef OLED_CHARSET_UTF8
		if ((int8_str[i] & 0x80) == 0)
		{ // 单字节 ascii 字符
			singleChar[0] = int8_str[i++];
			singleChar[1] = '\0';
		}
		else if ((int8_str[i] & 0xE0) == 0xc0)
		{ // 双字节
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			singleChar[2] = '\0';
		}
		else if ((int8_str[i] & 0xF0) == 0xE0)
		{ // 三字节
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[2] = int8_str[i++];
			singleChar[3] = '\0';
		}
		else if ((int8_str[i] & 0xF8) == 0xF0)
		{ // 三字节
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[2] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[3] = int8_str[i++];
			singleChar[4] = '\0';
		}
		else
		{
			i++; // 意外情况，i指向下一个字节，忽略此字节，继续判断下一个字节
			continue;
		}
#endif

#ifdef OLED_CHARSET_GB2312
		if ((int8_str[i] & 0x80) == 0)
		{ // 单字节 ascii 字符
			singleChar[0] = int8_str[i++];
			singleChar[1] = '\0';
		}
		else
		{ // 双字节
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			singleChar[2] = '\0';
		}
#endif
		if (singleChar[1] == '\0')
		{ // 单字节
			f_OLED_ShowChar(xOffSet, y, width, height, singleChar[0]);
			xOffSet += width;
		}
		else
		{ // chinese word
			for (index_CF = 0; strcmp(OLED_CF16x16[index_CF].Index, "") != 0; index_CF++)
			{
				if (strcmp(OLED_CF16x16[index_CF].Index, singleChar) == 0)
				{
					break;
				}
			}
			if (height == 16)
			{
				F_OLED_Set_Data(xOffSet, y, 16, 16, OLED_CF16x16[index_CF].Data);
				xOffSet += 16;
			}
			else
			{ // error show ?
				f_OLED_ShowChar(xOffSet, y, 6, 8, '?');
				xOffSet += 6;
			}
		}
	} // end while
}

/**
 * @description: 在指定地点打印字符串
 * @param {unsigned char} x start x location
 * @param {unsigned char} y start y location
 * @param {unsigned char} width the width for one char
 * @param {unsigned char} height the height for one char
 * @param {unsigned char} *int8_str the string to printf
 * @return {*}	the parameter for the string which may be a lot
 */
void f_oledPrintf(unsigned char x, unsigned char y, unsigned char width, unsigned char height, char *format, ...)
{
	char int8_string[256];
	va_list vaList;
	va_start(vaList, format);
	vsprintf(int8_string, format, vaList);
	va_end(vaList);
	f_oledShowString(x, y, width, height, int8_string);
}
