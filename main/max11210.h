/**
  ******************************************************************************
  * @file    max11210.h 
  * @author  Domen Jurkovic
  * @version V1.0
  * @date    18-Nov-2015
  * @brief   Header for max11210.c module
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAX11210_H
#define __MAX11210_H
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"

/* Includes ------------------------------------------------------------------*/
//#include "stm32l1xx.h"

//#include "stm32l1xx_gpio_init.h"
//#include "systick_millis.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define csPin   15 // MISO
#define clkPin  14// CLK
#define mosiPin 13// MOSI
#define misoPin 12 // MISO


#define	MAX11210_SPI_BANK		NotUSED
#define	MAX11210_SPI_NSS		csPin
#define	MAX11210_SPI_SCK		clkPin
#define	MAX11210_SPI_MISO		misoPin
#define	MAX11210_SPI_MOSI		mosiPin

/*
#define	AD_GPIO1_BANK				NotUSED
#define	AD_GPIO1						GPIO_Pin_0
#define	AD_GPIO2						GPIO_Pin_1	// uncomment in MAX11210_init()
#define	AD_GPIO3						GPIO_Pin_2	// uncomment in MAX11210_init()
#define	AD_GPIO4						GPIO_Pin_3	// uncomment in MAX11210_init()
*/

// REGISTER ADDRESS
#define	STAT1	0x0	// reg size = 8 bits
#define	CTRL1	0x1	// reg size = 8 bits
#define	CTRL2	0x2	// reg size = 8 bits (FOR GPIO pins)
#define	CTRL3	0x3	// reg size = 8 bits
#define	DATA	0x4	// reg size = 24 bits
#define	SOC		0x5	// reg size = 24 bits		(System Offset Calibration)
#define	SGC		0x6	// reg size = 24 bits		(System Gain Calibration)
#define	SCOC	0x7	// reg size = 24 bits		(Self-calibration Offset)
#define	SCGC	0x8	// reg size = 24 bits		(Self-calibration Gain)

// COMMAND BYTES  (MODE = 0, LINEF = 0)
#define	SELF_CALIB				0x90
#define	SYS_OFFSET_CALIB	0xA0
#define	SYS_GAIN_CALIB		0xB0
#define	POWER_DOWN				0x88

#define	MEASURE_1_SPS			0x80
#define	MEASURE_2p5_SPS		0x81
#define	MEASURE_5_SPS			0x82
#define	MEASURE_10_SPS		0x83
#define	MEASURE_15_SPS		0x84
#define	MEASURE_30_SPS		0x85
#define	MEASURE_60_SPS		0x86
#define	MEASURE_120_SPS		0x87

// MEASUREMENT MODE
#define MODE_SINGLE				0x02
#define MODE_CONTINUOUS		0x00

//ADC WAIT TIMEOUT
#define MAX_TIME_TO_WAIT 5  //this is in seconds

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SPI_init(void);
void MAX11210_init(void);
void read_registers(void);

void MAX11210_calibration(void);
void MAX11210_self_calib(void);
void MAX11210_sys_offset_calib(void);
void MAX11210_sys_gain_calib(void);

void			MAX11210_set_meas_mode(uint8_t mode);
void 			MAX11210_start_meas(uint8_t rate);
uint32_t	MAX11210_read_result(void);
uint8_t 	MAX11210_meas_status(void);


uint32_t   	MAX11210_read_reg(uint8_t reg);
void  			MAX11210_write_reg(uint8_t reg, uint8_t reg_val_HSB, uint8_t reg_val_MSB, uint8_t reg_val_LSB);
//void        MAX11210_write_reg(uint8_t reg, uint8_t reg_val_HSB, uint8_t reg_val_MSB, uint8_t reg_val_LSB, uint8_t length);
//void 			MAX11210_send_command(uint8_t command);
void        MAX11210_send_command(uint8_t command, uint8_t length);






#endif /* __MAX11210_H */

/*****	END OF FILE	****/