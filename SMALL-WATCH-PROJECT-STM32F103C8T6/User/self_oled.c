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
	GPIO_InitTypeDef GPIO_InitStructure; // ����ṹ�����
	uint32_t i, j;

	/*�ڳ�ʼ��ǰ������������ʱ����OLED�����ȶ�*/
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1000; j++)
			;
	}

	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(PIN_SCL_RCC_APB2Periph_GPIOX, ENABLE); // ����GPIOC��ʱ��
	RCC_APB2PeriphClockCmd(PIN_SDA_RCC_APB2Periph_GPIOX, ENABLE); // ����GPIOC��ʱ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // GPIOģʽ����ֵΪ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO�ٶȣ���ֵΪ50MHz

	GPIO_InitStructure.GPIO_Pin = PIN_SCL_GPIO_Pin_X; // GPIO���ţ���ֵΪ��13������
	GPIO_Init(PIN_SCL_GPIOX, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_SDA_GPIO_Pin_X; // GPIO���ţ���ֵΪ��13������
	GPIO_Init(PIN_SDA_GPIOX, &GPIO_InitStructure);
	F_SetPinSCL(1);
	F_SetPinSDA(1);
}

void F_IIC_Start(void)
{
	F_SetPinSDA(1);
	F_SetPinSCL(1);
	F_SetPinSDA(0);
	F_SetPinSCL(0); // ��0 ȷ�������޸� SDA ����
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
	// ��ACK������һ��
	F_SetPinSCL(1);
	F_SetPinSCL(0);
}

void F_OLED_WriteCommand(uint8_t u8_command)
{
	F_IIC_Start();
	F_IIC_SendByte(0x78); // �ӻ���ַ
	F_IIC_SendByte(0x00); // д����
	F_IIC_SendByte(u8_command);
	F_IIC_End();
}

void F_OLED_SendByteArr(uint8_t *dataArr, uint8_t u8_count)
{
	uint8_t i = 0;
	uint8_t j = 0;

	F_IIC_Start();
	F_IIC_SendByte(0x78); // �ӻ���ַ
	F_IIC_SendByte(0x40); // �����ֽڣ���0x40����ʾ����д����
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
	/*���ʹ�ô˳�������1.3���OLED��ʾ��������Ҫ�����ע��*/
	/*��Ϊ1.3���OLED����оƬ��SH1106����132��*/
	/*��Ļ����ʼ�н����˵�2�У������ǵ�0��*/
	/*������Ҫ��X��2������������ʾ*/
	X += 2;
	/*ͨ��ָ������ҳ��ַ���е�ַ*/
	F_OLED_WriteCommand(0xB0 | u8_pageIndex);	   // ����ҳλ��
	F_OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4)); // ����Xλ�ø�4λ
	F_OLED_WriteCommand(0x00 | (X & 0x0F));		   // ����Xλ�õ�4λ
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
 * @param {uint8_t} pos_x	��ʾ�������Ͻ� x ������
 * @param {uint8_t} pos_y   ��ʾ�������Ͻ� y ������
 * @param {uint8_t} width   ��ʾ�����г�
 * @param {uint8_t} height ��ʾ�����и�
 * @param {uint8_t} *data_arr ��ʾ�����ݣ���������ʽ ���У���һ���ֽڴ������Ͻǵ�һ��8���㣬�ڶ����ֽڴ���ڶ���ǰ8����
 * @return {*}
 */
void F_OLED_Set_Data(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height, const uint8_t *data_arr)
{
	unsigned int i;
	uint8_t j, x, y, page, shift;
	// ����Ӧ��ģ�������õ���Ӧ���ݵ���
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
			{ // Խ���ж�
				if (data_arr[j + i / 8 * width] & (0x01 << (i % 8)))
				{ // ��1
					g_OLED_Disp_Arr[page][x] |= (0x01 << shift);
				}
				else
				{ // ��0
					g_OLED_Disp_Arr[page][x] &= ~(0x01 << (shift));
				}
			}
		}
	}
}

void F_OLED_Init()
{
	/*GPIO��ʼ��*/
	F_IIC_Init();

	F_OLED_WriteCommand(0xAE); // �ر���ʾ

	F_OLED_WriteCommand(0xD5); // ������ʾʱ�ӷ�Ƶ��/����Ƶ��
	F_OLED_WriteCommand(0x80);

	F_OLED_WriteCommand(0xA8); // ���ö�·������
	F_OLED_WriteCommand(0x3F);

	F_OLED_WriteCommand(0xD3); // ������ʾƫ��
	F_OLED_WriteCommand(0x00);

	F_OLED_WriteCommand(0x40); // ������ʾ��ʼ��

	F_OLED_WriteCommand(0xA1); // �������ҷ���0xA1���� 0xA0���ҷ���

	F_OLED_WriteCommand(0xC8); // �������·���0xC8���� 0xC0���·���

	F_OLED_WriteCommand(0xDA); // ����COM����Ӳ������
	F_OLED_WriteCommand(0x12);

	F_OLED_WriteCommand(0x81); // ���öԱȶȿ���
	F_OLED_WriteCommand(0xCF);

	F_OLED_WriteCommand(0xD9); // ����Ԥ�������
	F_OLED_WriteCommand(0xF1);

	F_OLED_WriteCommand(0xDB); // ����VCOMHȡ��ѡ�񼶱�
	F_OLED_WriteCommand(0x30);

	F_OLED_WriteCommand(0xA4); // ����������ʾ��/�ر�

	F_OLED_WriteCommand(0xA6); // ��������/��ת��ʾ

	F_OLED_WriteCommand(0x8D); // ���ó���
	F_OLED_WriteCommand(0x14);

	F_OLED_WriteCommand(0xAF); // ������ʾ

	F_OLED_Clear(); // OLED����
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
		{ // ���ֽ� ascii �ַ�
			singleChar[0] = int8_str[i++];
			singleChar[1] = '\0';
		}
		else if ((int8_str[i] & 0xE0) == 0xc0)
		{ // ˫�ֽ�
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			singleChar[2] = '\0';
		}
		else if ((int8_str[i] & 0xF0) == 0xE0)
		{ // ���ֽ�
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
		{ // ���ֽ�
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
			i++; // ���������iָ����һ���ֽڣ����Դ��ֽڣ������ж���һ���ֽ�
			continue;
		}
#endif

#ifdef OLED_CHARSET_GB2312
		if ((int8_str[i] & 0x80) == 0)
		{ // ���ֽ� ascii �ַ�
			singleChar[0] = int8_str[i++];
			singleChar[1] = '\0';
		}
		else
		{ // ˫�ֽ�
			singleChar[0] = int8_str[i++];
			if (int8_str[i] == '\0')
				break; // if error break out
			singleChar[1] = int8_str[i++];
			singleChar[2] = '\0';
		}
#endif
		if (singleChar[1] == '\0')
		{ // ���ֽ�
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
 * @description: ��ָ���ص��ӡ�ַ���
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
