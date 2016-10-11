
#ifndef _FFT_H_
#define _FFT_H_

#include "stm32f4xx_hal.h"

#define ARM_MATH_CM4
//											 2048
#define BUFF_SIZE 			(2048)
#define OUT_BUFF_SIZE 	(BUFF_SIZE)
#define ACC_RATE     		(1) 						//30//900 //1600
#define ACC_RATE_DIV 		(1) 						//4//150 //300
#define MAX_OUT_VAL  		(2047)

#define IN_DATA_COEF		(2)
#define OUT_DATA_COEF		(10)


//#define DRAW_INPUT        0
#define OFFSET_QUAD_FUNC  	4
#define DISPALY_WIN      (BUFF_SIZE/2) 


void drawFunction(void);
void waitPuls(void);
void FFT_Route(void);
void FFT_Init(void);

#endif
