#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
static u16 mode = 0;
static u16 ms = 0,s = 0,min = 0;
static u16 start = 0;
static u16 line = 16;

void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

  //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); 

 	//EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	//EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	//NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	//NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==1)	 	 //WK_UP����
	{				
		setMs(0);
		setS(0);
		setMin(0);
		start = 0;
		mode = !mode;	
		Reset();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 
//�ⲿ�ж�2�������
void EXTI1_IRQHandler(void)
{
	//OLED_ShowNum(72,0,  9,1,16);
	delay_ms(10);//����
	if(KEY1==0)	  //����KEY2
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
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 //����KEY1
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
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE3�ϵ��жϱ�־λ  
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

