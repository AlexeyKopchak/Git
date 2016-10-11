/***************************************************************************
 * @file    DDS_conf.c
 * @author  Kopchak Alexey
 * @version v1.0
 * @date    October-2016
 * @brief   DDS Configure File
 ***************************************************************************
 *
 * ===========How to calculate Linear Sweep No-Dwell mode ==================
 *
 * Example: FTW0 = 5MHz (the start frequency); 
 *          FTW1 = 10 MHz (the stop frequency);
 *          NLSCW = 1000 ms
 * 					PLSCW = 1000 ms
 * 					SYSCLK = 384 MHz (24 MHz quartz * 16 (PLL)) -> Max 400 MHz
 * 					SYNC_CLK = SYSCLK/4 = 96 (see BLOCK DIAGRAM on page 3/40)
 *
 * FTW0 is (5/SYSCLK) * 2^32 or 0x0353F7CE in hex
 * FTW1 is (10/SYSCLK)* 2^32 or 0x06A7EF9D in hex
 * NLSCW is 
 *
 * (FTW1 - FTW0) * 4 * N	   (10 MHz - 5MHz)* 4 * 200
 * --------------------- * 2^32 -> ------------------------ * 2^32 = 0x3A
 * NLSCW * (SYSCLK^2)		   1000 ms * (384 MHz)^2
 *
 * Where N = 200 ramp rate (0x64 on hex)
 * Combining the rising ramp rate, first byte, and the
 * rising delta frequency 
 * NLSCW = 0x640000003A
 * NLSCW = PLSCW
 *
 * For more detail u can read DETAILED PROGRAMMING EXAMPLES 
 * on page 33/40 of datasheet AD9954
 ***************************************************************************
 */
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "DDS_conf.h"

extern SPI_HandleTypeDef hspi3;

uint8_t arr_DDS_CFR1[DDS_CFR1_LEN];
uint8_t arr_DDS_CFR2[DDS_CFR2_LEN];
uint8_t arr_DDS_FTW0[DDS_FTW0_LEN];
uint8_t arr_DDS_FTW1[DDS_FTW1_LEN];
uint8_t arr_DDS_NLSCW[DDS_NLSCW_LEN];
uint8_t arr_DDS_PLSCW[DDS_PLSCW_LEN];


uint8_t test_arr1[DDS_FTW0_LEN];
uint8_t test_arr1[DDS_FTW0_LEN];

//Read function

/*==================================== 
 * Reading CFR1 register function.
 *====================================*/
void getReg_DDS_CFR1(void)
{
	uint8_t data[DDS_CFR1_LEN];
	data[0] = DDS_CFR1 | DDS_READ_REG;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = 0x00;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_CFR1, DDS_CFR1_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}


/*==================================== 
 * Reading CFR2 register function.
 *====================================*/
void getReg_DDS_CFR2(void)
{
	uint8_t data[DDS_CFR1_LEN];
	data[0] = DDS_CFR2 | DDS_READ_REG;
	data[1] = NOTHING;
	data[2] = NOTHING;
	data[3] = NOTHING;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_CFR2, DDS_CFR2_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}


/*==================================== 
 * Reading FTW0 register function.
 *====================================*/
void getReg_DDS_FTW0(void)
{
	uint8_t data[DDS_FTW0_LEN];
	data[0] = DDS_FTW0 | DDS_READ_REG;
	data[1] = NOTHING;
	data[2] = NOTHING;
	data[3] = NOTHING;
	data[4] = NOTHING;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_FTW0, DDS_FTW0_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}

/*==================================== 
 * Reading FTW1 register function.
 *====================================*/
void getReg_DDS_FTW1(void)
{
	uint8_t data[DDS_FTW1_LEN];
	data[0] = DDS_FTW1 | DDS_READ_REG;
	data[1] = NOTHING;
	data[2] = NOTHING;
	data[3] = NOTHING;
	data[4] = NOTHING;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_FTW1, DDS_FTW1_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}

/*==================================== 
 * Reading NLSCW register function.
 *====================================*/
void getReg_DDS_NLSCW(void)
{
	uint8_t data[DDS_NLSCW_LEN];
	data[0] = DDS_NLSCW | DDS_READ_REG;
	data[1] = NOTHING;
	data[2] = NOTHING;
	data[3] = NOTHING;
	data[4] = NOTHING;
	data[5] = NOTHING;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_NLSCW, DDS_NLSCW_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}

/*==================================== 
 * Reading PLSCW register function.
 *====================================*/
void getReg_DDS_PLSCW(void)
{
	uint8_t data[DDS_PLSCW_LEN];
	data[0] = DDS_PLSCW | DDS_READ_REG;
	data[1] = NOTHING;
	data[2] = NOTHING;
	data[3] = NOTHING;
	data[4] = NOTHING;
	data[5] = NOTHING;
	
	DDS_SPI_CS_LOW;
	HAL_SPI_TransmitReceive(&hspi3, data, arr_DDS_PLSCW, DDS_PLSCW_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	//DDS_IO_Update();
}

/*================================================ 
 * CFR1 register setting function
 * Parameters: uint8_t data0_7   - 0-7   data byte
 *						 uint8_t data8_15  - 8-15  data byte 
 *					 	 uint8_t data16_23 - 16-23 data byte
 *						 uint8_t data24_31 - 24-31 data byte 
 *================================================*/
void setReg_DDS_CFR1(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31)
{
	uint8_t data[DDS_CFR1_LEN];
	data[0] = DDS_CFR1;
	data[1] = data24_31;
	data[2] = data16_23;
	data[3] = data8_15;
	data[4] = data0_7;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_CFR1_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}


/*================================================ 
 * CFR2 register setting function
 * Parametrs: uint8_t data0_7   - 0-7   data byte
 *						uint8_t data8_15  - 8-15  data byte 
 *					 	uint8_t data16_23 - 16-23 data byte
 *================================================
 */
void setReg_DDS_CFR2(uint8_t data0_7,
										 uint8_t data8_15,
									 	 uint8_t data16_23)
{
	uint8_t data[DDS_CFR2_LEN];
	data[0] = DDS_CFR2;
	data[1] = data0_7;
	data[2] = data8_15;
	data[3] = data16_23;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_CFR2_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}

/*================================================ 
 * FTW0 register setting function
 * Parameters: uint8_t data0_7   - 0-7   data byte
 *						 uint8_t data8_15  - 8-15  data byte 
 *					 	 uint8_t data16_23 - 16-23 data byte
 *						 uint8_t data24_31 - 24-31 data byte 
 *================================================
 */

void setReg_DDS_FTW0(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31)
{
	uint8_t data[DDS_FTW0_LEN];
	data[0] = DDS_FTW0;
	data[1] = data0_7;
	data[2] = data8_15;
	data[3] = data16_23;
	data[4] = data24_31;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_FTW0_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}

/*================================================ 
 * FTW1 register setting function
 * Parameters: uint8_t data0_7   - 0-7   data byte
 *						 uint8_t data8_15  - 8-15  data byte 
 *					 	 uint8_t data16_23 - 16-23 data byte
 *						 uint8_t data24_31 - 24-31 data byte 
 *================================================
 */
void setReg_DDS_FTW1(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31)
{
	uint8_t data[DDS_FTW1_LEN];
	data[0] = DDS_FTW1;
	data[1] = data0_7;
	data[2] = data8_15;
	data[3] = data16_23;
	data[4] = data24_31;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_FTW1_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}

/*================================================ 
 * NLSCW register setting function
 * Parameters: uint8_t data0_7   - 0-7   data byte
 *						 uint8_t data8_15  - 8-15  data byte 
 *					 	 uint8_t data16_23 - 16-23 data byte
 *						 uint8_t data24_31 - 24-31 data byte 
 * 						 uint8_t data32_39 - 32-39 data byte
 *================================================
 */
void setReg_DDS_NLSCW(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31,
										 uint8_t data32_39)
{
	uint8_t data[DDS_NLSCW_LEN];
	data[0] = DDS_NLSCW;
	data[1] = data0_7;
	data[2] = data8_15;
	data[3] = data16_23;
	data[4] = data24_31;
	data[5] = data32_39;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_NLSCW_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}

/*================================================ 
 * PLSCW register setting function
 * Parameters: uint8_t data0_7   - 0-7   data byte
 *						 uint8_t data8_15  - 8-15  data byte 
 *					 	 uint8_t data16_23 - 16-23 data byte
 *						 uint8_t data24_31 - 24-31 data byte 
 * 						 uint8_t data32_39 - 32-39 data byte
 *================================================
 */
void setReg_DDS_PLSCW(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31,
										 uint8_t data32_39)
{
	uint8_t data[DDS_PLSCW_LEN];
	data[0] = DDS_PLSCW;
	data[1] = data0_7;
	data[2] = data8_15;
	data[3] = data16_23;
	data[4] = data24_31;
	data[5] = data32_39;
	DDS_SPI_CS_LOW;
	HAL_SPI_Transmit(&hspi3, data, DDS_PLSCW_LEN, SPI_TIMEOUT);
	DDS_SPI_CS_HIGH;
	DDS_IO_Update();
}

/*==================================== 
 * Update I/O function 
 * (need to apply changes)
 *====================================*/
void DDS_IO_Update(void)
{
	DDS_SPI_CS_HIGH;
	DDS_IO_HIGH;
	DDS_IO_LOW;
	HAL_Delay(10);
	DDS_IO_HIGH;
	HAL_Delay(10);
}

/*====================================  
 * DDS Init function
 *====================================*/
void DDS_Init(void)
{
	PS1_PIN_LOW;
	DDS_SPI_CS_HIGH;
	DDS_IO_LOW;
	/************************************
	 * Register map on page 26/40
	 * Register masks on DDS_conf.h
	 ************************************
	 */
	setReg_DDS_CFR1(LIN_SWEEP_NO_DWELL, SDIO_INPUT_ONLY, LIN_SWEEP_EN, 0x00);
	setReg_DDS_CFR2(NOTHING, NOTHING, CLK_PLL | VCO_RANGE);
	/****************************************
	 * How to calculate FTW0, FTW1, NLSCW, PLSCW 
	 * look at the beginning of the file.
	 *****************************************
	 */
	setReg_DDS_FTW0(0x03, 0x53, 0xF7, 0xCE);
	setReg_DDS_FTW1(0x06, 0xA7, 0xEF, 0x9D);
	setReg_DDS_NLSCW(0x64, 0x00, 0x00, 0x00, 0x3A);
	setReg_DDS_PLSCW(0x64, 0x00, 0x00, 0x00, 0x3A);
	
	DDS_SPI_CS_HIGH;
}

/*==================================== 
 * Loop
 *====================================*/
void DDS_loop()
{
	
}

/*==================================== 
 * Read all the registers function
 * (To check the settings)
 *====================================*/
void DDS_CheckReg()
{
	getReg_DDS_CFR1();
	HAL_Delay(10);
	getReg_DDS_CFR2();
	HAL_Delay(10);
	getReg_DDS_FTW0();
	HAL_Delay(10);
	getReg_DDS_FTW1();
	HAL_Delay(10);
	getReg_DDS_NLSCW();
	HAL_Delay(10);
	getReg_DDS_PLSCW();
	HAL_Delay(10);
}
