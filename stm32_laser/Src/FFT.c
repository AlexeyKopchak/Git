
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "FFT.h"
#include "arm_math.h"
#include "DDS_conf.h"		//This inclede need to use PS0 define from DDS_conf.h file 

extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;


uint8_t TEST_COEF_1 = 2;
uint8_t TEST_COEF_2 = 10;


/* Quadfunc buffer */
q15_t quadFunc[BUFF_SIZE];

/* Input cycle buffer from ADC */
q15_t inBuffer[BUFF_SIZE]; //q15_t

/* Output from FFT */
q15_t outBuffer[OUT_BUFF_SIZE];
/* Temp buffer for buffered inp data for FFT and output for magnitude */
q15_t tmpBuffer[OUT_BUFF_SIZE];

/* FFT value accumulator */
uint32_t accBuffer[OUT_BUFF_SIZE];


/* Display buffer for accumulator */
uint32_t dispAccBuff[OUT_BUFF_SIZE];

uint8_t readyFlag = 0;
uint8_t PS0_Flag = 0;

arm_status status;
arm_rfft_instance_q15 S;
static uint32_t i, copyCnt = 0;

void FFT_Route()
{
	if (readyFlag == 0)
	{
		if (PS0_Flag == 0)
		{
			PS0_PIN_LOW;
			DDS_IO_Update();
			PS0_PIN_HIGH;
			DDS_IO_Update();
			PS0_Flag = 1;
		}
		waitPuls();
	}
	else if(readyFlag == 1)
	{
		readyFlag = 0;
		PS0_Flag = 0;
		
		// Preamp buffer
		for (i = 0; i < BUFF_SIZE; i++)
		{
			tmpBuffer[i] = (inBuffer[i] * TEST_COEF_1); //IN_DATA_COEF
		}
		
		/* Init FFT then calc it */
		status = arm_rfft_init_q15(&S, BUFF_SIZE, RESET, SET);
		arm_rfft_q15(&S, tmpBuffer, outBuffer);
		
		/* Shift buffer at 8 bits as shown in PDF */
		for (i = 0; i < OUT_BUFF_SIZE; i++) //BUFF_SIZE
		{
			outBuffer[i] = outBuffer[i] << 8;
		}
		arm_cmplx_mag_q15(outBuffer, tmpBuffer, OUT_BUFF_SIZE);
		/* End of FFT */
		
		//Accumulate fft values
		for (i = 0; i < OUT_BUFF_SIZE; i++) //BUFF_SIZE
		{
			accBuffer[i] += tmpBuffer[i];
		}
		
		// Coppy result of accumalating to display buffer
		copyCnt++;
		if (copyCnt > ACC_RATE)
		{
			for (i = 0; i < DISPALY_WIN; i++) //FFT_OFFSET - FFT_WIN; i < BUFFER_SIZE / 2 - FFT_WIN; i++)
			{
				dispAccBuff[i] = (((accBuffer[i] /** quadFunc[i]*/) / (ACC_RATE_DIV)) / TEST_COEF_2);  //80);OUT_DATA_COEF
				if (dispAccBuff[i] > MAX_OUT_VAL)
				{
					dispAccBuff[i] = MAX_OUT_VAL;
				}
			}
			// Clear accumulator buffer
			memset(accBuffer, 0, BUFF_SIZE * 4);
			copyCnt = 0;
		}
		drawFunction();
	}
}

void drawFunction()
{
	/* Start front */
	HAL_GPIO_TogglePin(DAC_Sync_GPIO_Port, DAC_Sync_Pin);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0xFF);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	
	/* Drawing source signal */
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	for (uint32_t i = 0; i < DISPALY_WIN; i++)
	{
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dispAccBuff[i]); //dispAccBuff[i]
	}  
	/* Stop front */
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0xFF);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_GPIO_TogglePin(DAC_Sync_GPIO_Port, DAC_Sync_Pin);
}

void waitPuls()
{
	
	//HAL_Delay(30);
	HAL_TIM_Base_Start_IT(&htim2);
}

uint16_t cnt = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (cnt < BUFF_SIZE)
	{
		HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
    inBuffer[cnt] = HAL_ADC_GetValue(&hadc1);
		cnt++;
		HAL_GPIO_TogglePin(ADC_Scan_Led_GPIO_Port, ADC_Scan_Led_Pin);
		HAL_ADC_Stop(&hadc1);
	}
	else
	{
		HAL_ADC_Stop(&hadc1);
		HAL_TIM_Base_Stop_IT(htim);
		readyFlag = 1;
		cnt = 0;
	}
}
