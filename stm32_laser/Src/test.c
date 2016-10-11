
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "test.h"

extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

uint8_t buff[256];
uint8_t flag;

void test ()
{
	
	if (flag == 0)
	{
		HAL_TIM_Base_Start_IT(&htim2);
	}
	else if(flag == 1)
	{
//		for (uint8_t i = 0; i < 255; i++)
//		{
//			HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, buff[i]); //dispAccBuff[i]
//			HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
//		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (flag == 0)
	{
		for(uint8_t cnt = 0; cnt < 255; cnt++)
		{
			HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			buff[cnt] = HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop_DMA(&hadc1);
		}
		//HAL_TIM_Base_Stop_IT(htim);
		flag = 1;
	}
	else if(flag == 1)
	{
		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		for (uint8_t i = 0; i < 255; i++)
		{
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, buff[i]); //dispAccBuff[i]
			//HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
		}
		flag = 0;
	}
}





