#ifndef DDS_CONF_H_
#define DDS_CONF_H_

#include "stm32f4xx_hal.h"

/*=================== User Config ===============================*/
/*========== Exemple on datasheet AD9954 on 33/40 page ========= */
/*===================== Not Using ===============================*/

#define XTAL_FREQ 						(24)		//MHz
#define DDS_FTW0_FREQ					(5)
#define DDS_FTW1_FREQ					(10)

#define DDS_CHIRP_UP					(1000)	//ms -> miliseconds
#define DDS_CHIRP_DOWN				(1000)	//ms -> miliseconds
#define DDS_CHIRP_DIV					(100)		//ramp rate
/*==============================================================*/


/*======================Private Defines=========================*/
#define DDS_CFR1							(0x00)
#define DDS_CFR1_LEN					(SPI_WORD_LEN*4 + DDS_ADR_LEN)
#define DDS_CFR2							(0x01)
#define DDS_CFR2_LEN					(SPI_WORD_LEN*3 + DDS_ADR_LEN)
#define DDS_FTW0							(0x04)
#define DDS_FTW0_LEN					(SPI_WORD_LEN*4 + DDS_ADR_LEN)
#define DDS_FTW1							(0x06)
#define DDS_FTW1_LEN					(SPI_WORD_LEN*4 + DDS_ADR_LEN)
#define DDS_NLSCW							(0x07)
#define DDS_NLSCW_LEN					(SPI_WORD_LEN*5 + DDS_ADR_LEN)
#define DDS_PLSCW							(0x08)
#define DDS_PLSCW_LEN					(SPI_WORD_LEN*5 + DDS_ADR_LEN)

#define DDS_READ_REG					(0x80)
#define DDS_ADR_LEN						(1)

#define SYNC_CLK_DISABLE			(0x02)
#define LIN_SWEEP_NO_DWELL		(0x04)
#define EXT_POWER_DOWN_MODE		(0x08)
#define CLK_INPUT_PWR_DOWN		(0x10)
#define DAC_PWR_DOWN					(0x20)
#define COMP_PWR_DOWN					(0x40)
#define DIGITAL_PWR_DOWN			(0x80)

#define LSB_FIRST							(0x01)
#define SDIO_INPUT_ONLY       (0x02)
#define CLEAR_PHACE_ACUM      (0x04)
#define CLEAR_FREQ_ACUM       (0x08)
#define SIN_COS_SELECT        (0x10)
#define AUTO_CLEAR_PHACE      (0x20)
#define AUTO_CLEAR_FREQ       (0x40)
#define SRR_LOAD_EN           (0x80)

#define LIN_SWEEP_EN					(0x20)
#define SOFT_MANUAL_SYNC      (0x40)
#define AUTO_SYNC_EN          (0x80)

#define AUTO_OSK_EN           (0x01)
#define OSK_EN                (0x02)
#define LOAD_ARR_CONTROL			(0x04)
#define RAM_DESTINATION       (0x40)
#define RAM_EN                (0x80)


#define PUMP_HI								(0x01)
#define PUMP_LOW							(0x02)
#define VCO_RANGE							(0x04)
#define CLK_PLL								(0x10<<3)


#define NOTHING 							(0x00)

#define DDS_SPI_CS_LOW	(HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, GPIO_PIN_RESET))
#define DDS_SPI_CS_HIGH	(HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, GPIO_PIN_SET))

#define PS0_PIN_LOW 		(HAL_GPIO_WritePin(PS0_GPIO_Port, PS0_Pin, GPIO_PIN_RESET))
#define PS0_PIN_HIGH 		(HAL_GPIO_WritePin(PS0_GPIO_Port, PS0_Pin, GPIO_PIN_SET))
#define PS1_PIN_LOW 		(HAL_GPIO_WritePin(PS1_GPIO_Port, PS1_Pin, GPIO_PIN_RESET))
#define PS1_PIN_HIGH 		(HAL_GPIO_WritePin(PS1_GPIO_Port, PS1_Pin, GPIO_PIN_SET))
#define DDS_IO_LOW			(HAL_GPIO_WritePin(IO_Upd_GPIO_Port, IO_Upd_Pin, GPIO_PIN_RESET))
#define DDS_IO_HIGH			(HAL_GPIO_WritePin(IO_Upd_GPIO_Port, IO_Upd_Pin, GPIO_PIN_SET))
#define DDS_RST_ON			(HAL_GPIO_WritePin(DDS_RST_GPIO_Port, DDS_RST_Pin, GPIO_PIN_SET))
#define DDS_RST_OFF			(HAL_GPIO_WritePin(DDS_RST_GPIO_Port, DDS_RST_Pin, GPIO_PIN_RESET))

#define SPI_WORD_LEN		(1)
#define SPI_TIMEOUT			(100)


#define DDS_CLK					(XTAL_FREQ*CLK_PLL)	//MHz -> 384 MHz
#define DDS_FREQ_DELTA	(DDS_FTW1_FREQ - DDS_FTW0_FREQ) //Delta of freq. frequency change from FTW0 to FTW1


//Functions prototype
void DDS_IO_Update(void);
void DDS_Init(void);
void DDS_loop(void);
void SendByte(uint8_t byte);
void getReg_DDS_CFR1(void);
void getReg_DDS_CFR2(void);
void getReg_DDS_FTW0(void);
void getReg_DDS_FTW1(void);
void getReg_DDS_NLSCW(void);
void getReg_DDS_PLSCW(void);
void DDS_CheckReg(void);

void setReg_DDS_CFR1(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31);
void setReg_DDS_CFR2(uint8_t data0_7,
										 uint8_t data8_15,
									 	 uint8_t data16_23);
void setReg_DDS_FTW0(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31);
void setReg_DDS_FTW1(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31);
void setReg_DDS_NLSCW(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31,
										 uint8_t data32_39);
void setReg_DDS_NLSCp(uint8_t data0_7, 
										 uint8_t data8_15,
										 uint8_t data16_23, 
										 uint8_t data24_31,
										 uint8_t data32_39);

#endif /* DDS_CONF_H_ */
