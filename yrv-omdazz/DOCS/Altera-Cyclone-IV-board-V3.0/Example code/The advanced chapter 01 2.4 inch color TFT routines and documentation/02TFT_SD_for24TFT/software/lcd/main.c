#include <stdio.h>                    // printf()
#include <unistd.h>                   // usleep()
#include "my_types.h"                 // ��������
#include "debug.h"                    // debug
#include "sd_card.h"                  // sd_card
#include "ili932x.h"                  // ili9325


#define ENABLE_APP_DEBUG // turn on debug message
#ifdef ENABLE_APP_DEBUG
    #define APP_DEBUG(x)    DEBUG(x)
#else
    #define APP_DEBUG(x)
#endif


#define PIC_NUM      2    // ͼƬ����
#define START_SECTOR 8337 // ���ݴ洢����ʼ������ע��û�����ļ�ϵͳ�����Գ�ʼ��ַ���������������߼���������winhex�鿴ʱ��������ֻ������һ����
void DispPic_Demo(void)
{
  u16 i, j;
  u8 pic_num=0;         // ��Ƭ����
  u8 sector_buf[512];
  u32 sector_addr;

  sector_addr=START_SECTOR;
  do
  {
    ili_nCS=0;
    DB_o_EN;

    ili_SetDispArea(0, 0, 240, 320, 0, 0);
    for(j=0;j<300;j++)   //300��ʾһ��ͼƬ����300x512�ֽڵ���Ϣ
    {
      SD_CARD_Read_Data_LBA(sector_addr+j, 512, sector_buf);//ÿ�ζ���512�ֽڷŵ�������
      for(i=0;i<256;i++) //Ȼ��д��Һ������������ʾ256�����أ�ÿ������16λ��2���ֽ�
        ili_WrData(sector_buf[2*i+1],sector_buf[2*i]);
    }


    ili_nCS=1;

    sector_addr += 304;//304����ʵ��winhex�鿴���ֵ
    pic_num++;
    usleep(2*1000*1000); // ��ʱ2s
  }while(pic_num < PIC_NUM);
}


int main()
{
  ili_Initial();            // ��ʼ��ILI9325
  while(SD_CARD_Init() != 0x55);// ��ʼ��SD��
  while(1)
  {
    DispPic_Demo();
  }
  return 0;
}
