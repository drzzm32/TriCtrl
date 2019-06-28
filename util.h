#include "STC15.h"
#include <intrins.h>

#ifndef __UTIL_H_
#define __UTIL_H_

#define uint8_t unsigned char

#define OUT_A P10
#define OUT_B P12
#define OUT_C P14

#define CTL_V (~(P3 & 0x7) & 0x7)
#define CTL_A !P33
#define CTL_B !P36
#define CTL_C !P37

#define LED P55

#define CNT_MAX 7
static uint8_t cntA, cntB, cntC;
static uint8_t posA, posB, posC;

void portInit() {
	P1M0 = 0x07;	P1M1 = 0x00;
	P3M0 = 0x00;	P3M1 = 0x00;
}

void timerInit() {
	/*24MHz@10us*/
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TL0 = 0x10;	
	TH0 = 0xFF;
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void timerInterrupt() interrupt 1 using 1 {
	OUT_A = (cntA >= posA);
	cntA = (cntA < CNT_MAX ? cntA + 1 : 0);
	OUT_B = (cntB >= posB);
	cntB = (cntB < CNT_MAX ? cntB + 1 : 0);
	OUT_C = (cntC >= posC);
	cntC = (cntC < CNT_MAX ? cntC + 1 : 0);
}

void pwmInit() {
	portInit();
	LED = 1;
	OUT_A = 0; OUT_B = 0; OUT_C = 0;
	cntA = 0; cntB = 0; cntC = 0;
	posA = 0; posB = 0; posC = 0;
	timerInit();
}

void delay(unsigned char t)
{
	unsigned char i, j;
	i = 24; j = 85;
	do {
		do {
			while (--j) _nop_();
		} while (--i);
	} while (--t);
}

#endif