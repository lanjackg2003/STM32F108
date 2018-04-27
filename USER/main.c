#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "exti.h"
//ALIENTEK战舰STM32开发板实验12
//OLED显示实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
	
 int main(void)
 {	u8 t;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
	OLED_Init();			//初始化OLED     
	EXTIX_Init();	 
	 OLED_ShowChar1(0 ,0,16,16,1);
	 OLED_ShowChar1(8 ,0,17,16,1);
	 OLED_ShowChar1(16,0,18,16,1);
	 OLED_ShowChar1(24,0,19,16,1);
	 OLED_ShowChar1(32,0,0 ,16,1);
	 OLED_ShowChar1(40,0,1 ,16,1);
	 OLED_ShowChar1(48,0,2 ,16,1);
	 OLED_ShowChar1(56,0,3 ,16,1);
	 OLED_ShowString(64,0,":");  
	 
	 OLED_ShowChar1(72 ,0,6 ,16,1);
	 OLED_ShowChar1(80 ,0,7 ,16,1);
	 OLED_ShowChar1(88 ,0,8 ,16,1);
	 OLED_ShowChar1(96 ,0,9 ,16,1);
	 OLED_ShowChar1(104,0,14,16,1);
	 OLED_ShowChar1(112,0,15,16,1);
	 
	 
	 OLED_ShowString(0,16,"00");
	 OLED_ShowChar1(16 ,16,20 ,16,1);
	 OLED_ShowChar1(24 ,16,21,16,1);
	 OLED_ShowString(48,16,".");
	 OLED_ShowChar1(72,16,4 ,16,1);
	 OLED_ShowChar1(80,16,5 ,16,1);
	 TIM3_Int_Init(99,7199);
	OLED_Refresh_Gram();	 
	t=' ';  
	while(1) 
	{		
		//OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
		OLED_Refresh_Gram();
		//t++;
		//if(t>'~')t=' ';
		//OLED_ShowNum(103,48,t,3,16);//显示ASCII字符的码值 
		delay_ms(5);
		//LED0=!LED0;
	}	  
	
}

