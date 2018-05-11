/**
  ******************************************************************************
  * @file    max11210.c
   * @author  Domen Jurkovic
  * @version V1.0
  * @date    18-Nov-2015
  * @brief   This file provides functions for MAX11210
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "max11210.h"
//#include "intrin.h"
#include "byteswap.h"

static const char* tag = "MAX11210";
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define install
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
	SPI SETUP FUNCTION
	SPI2: 
		NSS:	PB12
		SCK:	PB13
		MISO:	PB14
		MOSI:	PB15
		
*/
spi_bus_config_t bus_config;
spi_device_handle_t handle;
spi_device_interface_config_t dev_config;
//spi_transaction_t trans_desc;


void SPI_init(void){
	
	ESP_LOGD(tag, ">> test_spi_task");

    
    bus_config.sclk_io_num = clkPin; // CLK
    bus_config.mosi_io_num = mosiPin; // MOSI
    bus_config.miso_io_num = misoPin; // MISO
    bus_config.quadwp_io_num = -1; // Not used
    bus_config.quadhd_io_num = -1; // Not used	
    ESP_LOGI(tag, "... Initializing bus.");
    ESP_ERROR_CHECK(spi_bus_initialize(HSPI_HOST, &bus_config, 1));
  

    ESP_LOGI(tag, "... Initializing handle.");
   
    dev_config.address_bits = 0;
    dev_config.command_bits = 8;
    dev_config.dummy_bits = 0;
    dev_config.mode = 0;
    dev_config.duty_cycle_pos = 0;
    dev_config.cs_ena_posttrans = 0;
    dev_config.cs_ena_pretrans = 0;
    dev_config.clock_speed_hz = (500*1000);
    dev_config.spics_io_num = csPin;
    dev_config.flags = 0;
    dev_config.queue_size = 1;
    dev_config.pre_cb = NULL;
    dev_config.post_cb = NULL;
    ESP_LOGI(tag, "... Adding device bus.");
    ESP_ERROR_CHECK(spi_bus_add_device(HSPI_HOST, &dev_config, &handle)); 
}

void MAX11210_init(void){
	
	SPI_init();	
	ESP_LOGI(tag, "... Bus Initilized.");
	
    //MAX11210_read_reg(DATA);
	//ESP_LOGI(tag, "...TEST.");
    //for(;;);


	MAX11210_send_command(POWER_DOWN,1);

	vTaskDelay(200 / portTICK_PERIOD_MS);


	
	//MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 0; GAIN = 1;
	MAX11210_write_reg(SOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SGC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCGC, 0x00, 0x00, 0x00);
	//MAX11210_write_reg(CTRL3, 0x1E, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 1; GAIN = 1;
	
	MAX11210_write_reg(CTRL3,0x18,0,0);	
    MAX11210_write_reg(CTRL1,0x42,0,0);
    MAX11210_write_reg(CTRL2,0xF0,0,0);  //Set GPIO to outputs
   

}
/*
	Read 8 or 24 bit register.
	8bit reg:	STAT1, CTRL1, CTRL2, CTRL3
	24bit reg:	DATA, SOC, SGC, SCOC, SCGC
*/


uint32_t MAX11210_read_reg(uint8_t reg){

	uint8_t read_command = 0xC1;	
	uint32_t result = 0;		
	

	read_command |= (reg << 1);
    
	spi_transaction_t reg_read;	 
	
	memset(&reg_read, 0, sizeof(reg_read));  //sets trans_desc1 to zero.  Errors will occur if this is not done.
    
    reg_read.addr = 0;
	reg_read.cmd  = read_command;
	reg_read.flags = SPI_TRANS_USE_RXDATA; 

    if((reg == STAT1) | (reg == CTRL1) | (reg == CTRL2) | (reg == CTRL3)){	// read 1 byte
		reg_read.length = (1 * 8);    
		reg_read.user =(void*)1;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &reg_read));
		result = *(uint32_t *)reg_read.rx_data; 
	}
	else{		
		reg_read.length = (3 * 8);    
		reg_read.user =(void*)1;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &reg_read));
		//result = __bswap_32(*(uint32_t *)reg_read.rx_data);
		result = reg_read.rx_data[0];
	 	result = (result << 16);
	 	result = (result | (reg_read.rx_data[1] << 8));
	 	result = (result | reg_read.rx_data[2]);
	}		

    return result;

}

/*
	Write 8 or 24 bit register.
	8bit reg: 	CTRL1, CTRL2, CTRL3
	24bit reg:	SOC, SGC, SCOC, SCGC	
*/


void MAX11210_write_reg(uint8_t reg, uint8_t reg_val_HSB, uint8_t reg_val_MSB, uint8_t reg_val_LSB){
	
	uint8_t write_command = 0xC0;
    uint8_t length = 1;
    

	write_command |= (reg << 1);
   
    spi_transaction_t write_reg;	 

    memset(&write_reg, 0, sizeof(write_reg));  //sets trans_desc1 to zero.  Errors will occur if this is not done.
   
    if((reg == STAT1) | (reg == CTRL1) | (reg == CTRL2) | (reg == CTRL3)){	// read 1 byte
    	length = 1;
	}
	else{
		length = 3;
	}


	write_reg.addr = 0;
	write_reg.cmd  = write_command;
	write_reg.flags = SPI_TRANS_USE_TXDATA;
	write_reg.length = (length * 8);    
	write_reg.rxlength = 0;
	write_reg.tx_data[0] = reg_val_HSB;
	write_reg.tx_data[1] = reg_val_MSB;
	write_reg.tx_data[2] = reg_val_LSB;

	spi_device_transmit(handle, &write_reg);
    

}



/*
	Send command to MAX11210.
	Commands: 
		SELF_CALIB
		SYS_OFFSET_CALIB
		SYS_GAIN_CALIB
		POWER_DOWN
		MEASURE_1_SPS		
		MEASURE_2p5_SPS
		MEASURE_5_SPS	
		MEASURE_10_SPS
		MEASURE_15_SPS
		MEASURE_30_SPS
		MEASURE_60_SPS
		MEASURE_120_SPS
*/
void MAX11210_send_command(uint8_t command, uint8_t length){

   
    spi_transaction_t trans_desc;

    memset(&trans_desc,0,sizeof(trans_desc));

	trans_desc.addr = 0;
	trans_desc.cmd  = command;
	trans_desc.flags = 0;
	trans_desc.length = (length * 8);    
	trans_desc.rxlength = 0;
	
	
	ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
	vTaskDelay(200 / portTICK_PERIOD_MS);


}

/*
	Calibrate MAX11210
*/


void MAX11210_calibration(){
//#ifdef install
	// clear registers
	MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG NOSYSO NOSCG NOSCO = 0; GAIN = 1;
	MAX11210_write_reg(SOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SGC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCOC, 0x00, 0x00, 0x00);
	MAX11210_write_reg(SCGC, 0x00, 0x00, 0x00);
	/*
	//GAIN = 1
	// Enable self calibration registers
	MAX11210_write_reg(CTRL3, 0x18, 0, 0);	//	NOSYSG=1, NOSYSO=1, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_self_calib();	// Self-calibration
	
	// Enable system offset register
	MAX11210_write_reg(CTRL3, 0x10, 0, 0);	//	NOSYSG=1, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_sys_offset_calib();	// System-calibration offset
	
	// Enable system gain register
	MAX11210_write_reg(CTRL3, 0x00, 0, 0);	//	NOSYSG=0, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 1; 
	MAX11210_sys_gain_calib();	// System-calibration gain
	*/
	
	//GAIN = 16
	// Enable self calibration registers
	MAX11210_write_reg(CTRL3, 0x98, 0, 0);	//	NOSYSG=1, NOSYSO=1, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_self_calib();	// Self-calibration
	
	// Enable system offset register
	MAX11210_write_reg(CTRL3, 0x90, 0, 0);	//	NOSYSG=1, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_sys_offset_calib();	// System-calibration offset
	
	// Enable system gain register
	MAX11210_write_reg(CTRL3, 0x80, 0, 0);	//	NOSYSG=0, NOSYSO=0, NOSCG=0, NOSCO=0; GAIN = 16; 
	MAX11210_sys_gain_calib();	// System-calibration gain
//#endif	
}


/*
	System self calibration 
		The first level of calibration is the self-calibration where the part performs the required connections to zero and
	full scale internally. 
*/
void MAX11210_self_calib(void){
	MAX11210_send_command(SELF_CALIB,1);	//SCOC
  vTaskDelay(300 / portTICK_PERIOD_MS);
	
}

/*
	System offset calibration
		A second level of calibration is available where the user can calibrate a system zero scale and system full scale
	by presenting a zero-scale signal or a full-scale signal to the input pins and initiating a system zero scale or 
	system gain calibration command.
*/
void MAX11210_sys_offset_calib(void){
	MAX11210_send_command(SYS_OFFSET_CALIB,1);
	vTaskDelay(300 / portTICK_PERIOD_MS);
//	delay(300);
}

/*
	System gain calibration
		A third level of calibration allows for the user to write to the internal calibration registers through the SPI interface
	to achieve any digital offset or scaling the user requires with the following restrictions. The range of digital offset
	correction is QVREF/4. The range of digital gain correction is from 0.5 to 1.5. The resolution of offset correction is 0.5 LSB.
*/
void MAX11210_sys_gain_calib(void){
	MAX11210_send_command(SYS_GAIN_CALIB,1);
	vTaskDelay(300 / portTICK_PERIOD_MS);
//	delay(300);
}

/*
	Set measurement mode
	
*/


void MAX11210_set_meas_mode(uint8_t mode){
	uint8_t _mode = (uint8_t) MAX11210_read_reg(CTRL1);
	_mode &= 0xFD;	// mask CTRL1 register
	_mode |= mode;	
	MAX11210_write_reg(CTRL1, _mode, 0, 0);
}

/*
	Set measurement rate
		MEASURE_1_SPS		
		MEASURE_2p5_SPS
		MEASURE_5_SPS	
		MEASURE_10_SPS
		MEASURE_15_SPS
		MEASURE_30_SPS
		MEASURE_60_SPS
		MEASURE_120_SPS
*/
void MAX11210_start_meas(uint8_t rate){
	MAX11210_send_command(rate,1);
	// tole se mal precekirej
}
/*
	Read results when RDY bit in status register is 1.
		The RDY ready bit is set to 1 to indicate that a conversion result is available. Reading the DATA register resets the
	RDY bit to 0 only after another conversion has been initiated. If the DATA has not been read before another conversion
	is initiated, the RDY bit remains 1; if the DATA is read before another conversion is initiated, the RDY bit resets to 0. If
	the DATA for the previous conversion is read during a following conversion, the RDY bit is reset immediately after the
	DATA read operation has completed.
	Returns DATA register. User should check status register STAT afterwards.
*/



	uint32_t MAX11210_read_result(void){
    //volatile TickType_t t;
	//t = xTaskGetTickCount();
	TickType_t xTicksToWait = MAX_TIME_TO_WAIT;
    TimeOut_t xTimeOut;
	
	  /* Initialize xTimeOut.  This records the time at which this function was
   entered. */
    vTaskSetTimeOutState( &xTimeOut );	
	while((MAX11210_read_reg(STAT1) & 0x0001) != 1)
	{ //wait while RDY is not 1
		
    	if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )
      	{
         /* Timed out before the wanted number of bytes were available, exit the
         loop. */
			return(-1);
         //break;
      	}
	}

	return MAX11210_read_reg(DATA);
}

/*
	Check measure status
	Return masked status register STAT1
*/


uint8_t MAX11210_meas_status(void){

	return MAX11210_read_reg(STAT1) & 0x000C;
}



/*****	END OF FILE	****/