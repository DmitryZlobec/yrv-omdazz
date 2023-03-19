#include <STDIO.H>                    // printf() 
#include <UNISTD.H>                   // usleep() 
#include "my_types.h"                 // �������� 
#include "debug.h"                    // debug 
#include "sd_card.h"                  // sd�� 
#include "ili932x.h"                  // ili9325 
       
       
//#define ENABLE_APP_DEBUG // turn on debug message 
#ifdef ENABLE_APP_DEBUG 
#define APP_DEBUG(x)    DEBUG(x) 
#else 
#define APP_DEBUG(x) 
#endif 
       
       
int main(void) 
{ 
   ili_Initial();            // ��ʼ��ILI9325 
   ili_DispColorBar();       // �������� 
   while(1); 
   return 0; 
}
