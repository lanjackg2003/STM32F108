#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
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
void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��	
void setMs(u16 x);
void setS(u16 x);
void setMin(u16 x);
void setMode(u16 x);
void setStart(u16 x);
void setLine(u16 x);
u16 getMs();
u16 getS();
u16 getMin();
u16 getMode();
u16 getStart();
u16 getLine();
void Reset();

#endif

