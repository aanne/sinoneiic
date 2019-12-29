#include "Function_Init.h"

bit TWIFlag = 0;          //中断标志位

void beep(void){
    P1&=0xEF;
}

void beepStop(void){
    P1|=0x10;
}

void LED1_ON(){
    P0&=0xEF;
}

void LED1_OFF(){
    P0|=0x10;
}

void LED2_ON(){
    P5&=0xFD;
}

void LED2_OFF(){
    P5|=0x02;
}

void LED3_ON(){
    P1&=0x7F;
}

void LED3_OFF(){
    P1|=0x80;
}

void sysInit(){
    P0CON = 0xFF;
    P0PH  = 0xFF;	
    P1CON = 0xFF;
    P1PH  = 0xFF;
    P2CON = 0xFF;
    P2PH  = 0xFF;
    P5CON = 0xFF;
    P5PH  = 0xFF;

    P0 = 0xFF;
    P1 = 0xFF;
    P5 = 0xFF; 	
	P2 = 0xFF;
    EA = 1;
    WDTCON |= 0x10;		    //清看门狗
	OPERCON = 0X01;         //CHKSUM运算
	_nop_();
}

/*****************************************************
*函数名称：void TWI_Init(void)
*函数功能：TWI初始化
*入口参数：void
*出口参数：void
*****************************************************/
void TWI_Init(void)
{
	OTCON |= 0x80;  //选择TWI模式
	SSCON0 = 0x88;  // ---- x---  0为不允许接收，1为允许接收
	SSCON1 = 0x03;  //xxxx xxxy  x为地址寄存器，y为0禁止/1允许通用地址响应
    IE1 |= 0x01;
    SSDAT=0x22;
}

void TWI_Int() interrupt 7{
	if(SSCON0&0x40){
		SSCON0 &= 0xbf;  //中断清零
//        if(SSDAT==0x22)
//           LED2_ON();
		TWIFlag = 1;
	}	
}

void main(void){
    sysInit();
    TWI_Init();
    while(1){

        }
}









