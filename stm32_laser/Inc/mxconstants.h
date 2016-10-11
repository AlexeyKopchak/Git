/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define DAC_Out_Pin GPIO_PIN_4
#define DAC_Out_GPIO_Port GPIOA
#define DAC_Sync_Pin GPIO_PIN_5
#define DAC_Sync_GPIO_Port GPIOA
#define ADC_In_Pin GPIO_PIN_6
#define ADC_In_GPIO_Port GPIOA
#define Laser_Pin GPIO_PIN_7
#define Laser_GPIO_Port GPIOA
#define DIR_Pin GPIO_PIN_0
#define DIR_GPIO_Port GPIOB
#define Err_Led_Pin GPIO_PIN_14
#define Err_Led_GPIO_Port GPIOB
#define Init_Led_Pin GPIO_PIN_6
#define Init_Led_GPIO_Port GPIOC
#define ADC_Scan_Led_Pin GPIO_PIN_8
#define ADC_Scan_Led_GPIO_Port GPIOC
#define DDS_RST_Pin GPIO_PIN_11
#define DDS_RST_GPIO_Port GPIOA
#define nCS_Pin GPIO_PIN_15
#define nCS_GPIO_Port GPIOA
#define PS0_Pin GPIO_PIN_3
#define PS0_GPIO_Port GPIOB
#define PS1_Pin GPIO_PIN_4
#define PS1_GPIO_Port GPIOB
#define IO_Upd_Pin GPIO_PIN_5
#define IO_Upd_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define LASER_ON 							(HAL_GPIO_WritePin(GPIOA, GPIO_Laser_Pin, GPIO_PIN_SET))
#define LASER_OFF							(HAL_GPIO_WritePin(GPIOA, GPIO_Laser_Pin, GPIO_PIN_RESET))
#define ARRAY_LEN							1024
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
