#include "ads7843.h"
#include <unistd.h>


// ȫ�ֱ��������Դ���������Ϣ
u16 X=0, Y=0;


// SPI��ʼ״̬
void ads_SPIStart(void)
{
  ads_CLK=0;
  ads_nCS=1;
  ads_DIN=1;
  ads_CLK=1;
  ads_nCS=0;
}


// SPIдһ��byte
void ads_SPIWrite(u8 cmd)
{
  u8 i;
  ads_CLK=0;
  for(i=0; i<8; i++) // ��������Ч
  {
    ads_DIN = (cmd >> (7-i)) & 0x1; // MSB��ǰ��LSB�ں�
    ads_CLK=0; usleep(1);
    ads_CLK=1; usleep(1);
  }
}


// SPI��12��bit
u16 ads_SPIRead(void)
{
  u8 i;
  u16 temp=0;
  for(i=0; i<12; i++) // �½�����Ч
  {
    temp<<=1;
    ads_CLK=1; usleep(1);
    ads_CLK=0; usleep(1);
    if(ads_DOUT) temp++;
  }
  return temp;
}


// ��ȡADS7843�ɼ���X��Yֵ
// ���أ�������Ļ��Χ���򷵻�0
bool ads_ReadXY(void)
{
  ads_SPIStart();
  ads_SPIWrite(CHX);
  ads_CLK=1; usleep(1);
  ads_CLK=0; usleep(1);
  X = ads_SPIRead();
  ads_SPIWrite(CHY);
  ads_CLK=1; usleep(1);
  ads_CLK=0; usleep(1);
  Y = ads_SPIRead();
  ads_nCS=1;
  if((X>350 && X<3800) && (Y>300 && Y<3800)) // �����Լ��������н���
    return 1; // �����ɹ�(��Χ����)
  else
    return 0; // ����ʧ��
}


// �����ADS7843��ȡ��X��Yֵ��Ȼ�󻥻�
#define SAMP_CNT      4
#define SAMP_CNT_DIV2 2
bool ads_GetXY(void)
{
  u8 i, j, k, min;
  u16 temp;
  u16 tempXY[2][SAMP_CNT], XY[2];
  // ����
  for(i=0; i<SAMP_CNT; i++)
  {
    if(ads_ReadXY())
    {
      tempXY[0][i] = X;
      tempXY[1][i] = Y;
    }
  }
  // �˲�
  for(k=0; k<2; k++)
  { // ��������
    for(i=0; i<SAMP_CNT-1; i++)
    {
      min=i;
      for (j=i+1; j<SAMP_CNT; j++)
      {
        if (tempXY[k][min] > tempXY[k][j]) min=j;
      }
      temp = tempXY[k][i];
      tempXY[k][i] = tempXY[k][min];
      tempXY[k][min] = temp;
    }
    // �趨��ֵ
    if((tempXY[k][SAMP_CNT_DIV2]-tempXY[k][SAMP_CNT_DIV2-1]) > 5)
      return 0;
    // ���м�ֵ�ľ�ֵ
    XY[k] = (tempXY[k][SAMP_CNT_DIV2]+tempXY[k][SAMP_CNT_DIV2-1]) / 2;
  }
  // ��������
  Y = ((XY[0]-350)/11);
  X = ((XY[1]-400)/14);
  return 1;
}


// ����ת�ַ�������ʾX��Y���꣬3��ASCII�룩
u8 *intostr(u16 n)
{
  u8 *p;
  static u8 buf[3];
  p = &buf[3];
  *p     = (n/100) - ((n/1000)*10)+48;
  *(p+1) = (n/10) - ((n/100)*10) +48;
  *(p+2) = n- ((n/10) *10) +48;
  *(p+3) = 0;
  return  p;
}
