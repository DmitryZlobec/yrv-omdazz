#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
/* 
������Ի���:��Ƭ��STC12LE5A60S2,����33M  ��Ƭ��������ѹ3.3V
����Ĭ��IO���ӷ�ʽ��
�����ߣ�RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^2;
������: DB0-DB7��������P0^0-P0^7;  DB8-DB15��������P2^0-P2^7;��8λģʽ��DB0-DB7���Բ����ӣ�
�����������ӷ�ʽ��(��ʹ�ô����ɲ�����)
T_CLK-P1^7;  T_CS-P1^4;  T_DIN-P3^0;  T_OUT-P3^1;  T_IRQ-P3^4;
*/	
main()
{ 
	Lcd_Init();   //tft��ʼ��
	LCD_Clear(WHITE); //����
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 

	while(1)
	{
	     LCD_Clear(RED);
		 delayms(3000);
		 LCD_Clear(GREEN);
		 delayms(3000);
		 LCD_Clear(BLUE);
		 delayms(3000);
    }


}
