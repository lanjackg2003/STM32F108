#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
static u16 mode = 0;
static u16 ms = 0,s = 0,min = 0;
static u16 start = 0;
static u16 line = 16;

void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); 

 	//EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	//EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	//NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	//NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==1)	 	 //WK_UP按键
	{				
		setMs(0);
		setS(0);
		setMin(0);
		start = 0;
		mode = !mode;	
		Reset();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 
//外部中断2服务程序
void EXTI1_IRQHandler(void)
{
	//OLED_ShowNum(72,0,  9,1,16);
	delay_ms(10);//消抖
	if(KEY1==0)	  //按键KEY2
	{
		if(mode == 0){
			line = 16;
			start = !start;
		}
		else if(mode == 1){
			if(start == 0){
				start = 1;
			}
			else if(start == 1 && line < 48){
				line += 16;
			}
			else if(start == 1 && line == 48){
				line = 16;
			}
		}
		//OLED_Refresh_Gram();	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	 //按键KEY1
	{		
		if(start){
			start = 0;
			//setMs(0);
			//setS(0);
			//setMin(0);
		}
		else{
			Reset();
		}
		//OLED_Refresh_Gram();	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE3上的中断标志位  
}
u16 getMode(){
	return mode;
}
void setMode(u16 x){
	mode = x;
}
u16 getMs(){
	return ms;
}
u16 getS(){
	return s;
}
u16 getMin(){
	return min;
}
u16 getStart(){
	return start;
}
u16 getLine(){
	return line;
}
void setMs(u16 x){
	ms = x;
}
void setS(u16 x){
	s = x;
}
void setMin(u16 x){
	min = x;
}
void setStart(u16 x){
	start = x;
}
void setLine(u16 x){
	line = x;
}
void Reset(){
	setMs(0);
	setS(0);
	setMin(0);
	if(mode == 0){	
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
			
			
			OLED_ShowString(0,32,"           ");
			OLED_ShowString(0,48,"           ");
		}		
		else if(mode == 1){
			line = 16;
			OLED_ShowChar1(0 ,0,16,16,1);
			OLED_ShowChar1(8 ,0,17,16,1);
			OLED_ShowChar1(16,0,18,16,1);
			OLED_ShowChar1(24,0,19,16,1);
			OLED_ShowChar1(32,0,0    ,16,1);
			OLED_ShowChar1(40,0,1 ,16,1);
			OLED_ShowChar1(48,0,2 ,16,1);
			OLED_ShowChar1(56,0,3 ,16,1);
			OLED_ShowString(64,0,":");  
			
			OLED_ShowChar1(72 ,0,4 ,16,1);
			OLED_ShowChar1(80,0,5 ,16,1);
			OLED_ShowChar1(88,0,22,16,1);
			OLED_ShowChar1(96,0,23,16,1);
			OLED_ShowString(104,0,"  ");
			
			OLED_ShowString(0,32,"           ");
			OLED_ShowString(0,48,"           ");
		}		
}

