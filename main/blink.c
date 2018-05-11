/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "max11210.h"

#include "sdkconfig.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 2
#define SHIFT	5
#define AV_RATE	10

static const char* tag = "BLINK";
static const char* tag1 = "MAX11210";
static const char* task_console = "CONSOLE";


SemaphoreHandle_t xSemaphore = NULL;

void read_registers(void);
static void blink_task(void *pvParameters);
static void spi_task(void *pvParameters);
static void console_task(void *pvParameters);



void read_registers(void){

    printf("\nSTAT1: 0x%08x\n",MAX11210_read_reg(STAT1));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("CTRL1:  0x%08x\n",MAX11210_read_reg(CTRL1));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("CTRL2: 0x%08x\n",MAX11210_read_reg(CTRL2));
    vTaskDelay(100 / portTICK_PERIOD_MS);   
    printf("CTRL3: 0x%08x\n",MAX11210_read_reg(CTRL3));	
    vTaskDelay(100 / portTICK_PERIOD_MS);

    printf("SCOC: 0x%08x\n",MAX11210_read_reg(SCOC));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("SOC:  0x%08x\n",MAX11210_read_reg(SOC));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("SCGC: 0x%08x\n",MAX11210_read_reg(SCGC));
    vTaskDelay(100 / portTICK_PERIOD_MS);   
    printf("SGC: 0x%08x\n\n",MAX11210_read_reg(SGC));	
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
}




void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    uint8_t j = 0;
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    for(;;) {
        /* Blink off (output low) */
        //xSemaphoreTake(xMutex, portMAX_DELAY);
              
        //xSemaphoreGive(xMutex);
        gpio_set_level(BLINK_GPIO, 0);        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
       
    }
}

void spi_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    
    int32_t result,result2;
	int32_t av_result;
    int32_t av_result2;
	uint8_t i = 0;

    static uint8_t count =0;   
    


    ESP_LOGI(tag1, ">> inializing");
    MAX11210_init();    
    ESP_LOGI(tag1, ">> initialized");     
/*
    for(i = 0; i < 5; i ++){
		MAX11210_start_meas(MEASURE_10_SPS);
		MAX11210_read_result();
	}
*/	
    ESP_LOGI(tag1, "... Calibration Start");   
    MAX11210_calibration();
    ESP_LOGI(tag1, "... Calibration END");   


    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("SCOC: 0x%08x\n",MAX11210_read_reg(SCOC));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("SOC:  0x%08x\n",MAX11210_read_reg(SOC));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("SCGC: 0x%08x\n",MAX11210_read_reg(SCGC));
    vTaskDelay(300 / portTICK_PERIOD_MS);   
    printf("SGC: 0x%08x\n\n",MAX11210_read_reg(SGC));	
    vTaskDelay(300 / portTICK_PERIOD_MS);


   // ESP_LOGI(tag1, "... Self Calibration Start");   
   // MAX11210_self_calib();
   // ESP_LOGI(tag1, "... Self Calibration End\n\n");   

    printf("SCOC: 0x%08x\n",MAX11210_read_reg(SCOC));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("SOC:  0x%08x\n",MAX11210_read_reg(SOC));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("SCGC: 0x%08x\n",MAX11210_read_reg(SCGC));
    vTaskDelay(300 / portTICK_PERIOD_MS);   
    printf("SGC: 0x%08x\n\n",MAX11210_read_reg(SGC));	
    vTaskDelay(300 / portTICK_PERIOD_MS);

    printf("STAT1: 0x%08x\n",MAX11210_read_reg(STAT1));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("CTRL1:  0x%08x\n",MAX11210_read_reg(CTRL1));
    vTaskDelay(300 / portTICK_PERIOD_MS);
    printf("CTRL2: 0x%08x\n",MAX11210_read_reg(CTRL2));
    vTaskDelay(300 / portTICK_PERIOD_MS);   
    printf("CTRL3: 0x%08x\n",MAX11210_read_reg(CTRL3));	
    vTaskDelay(300 / portTICK_PERIOD_MS);

    printf("*************\n\n");    
    printf("CTRL1:  0x%08x\n",MAX11210_read_reg(CTRL1));
    printf("*************\n\n");

    for(;;)  
    {

        if(xSemaphore != NULL)
        {
            if(xSemaphoreTake (xSemaphore, (TickType_t) (10 / portTICK_PERIOD_MS)) == pdTRUE)
            {

                for(i = 0; i < AV_RATE; i++){
		            MAX11210_start_meas(MEASURE_10_SPS);	//starts a single conversion
		            result = MAX11210_read_result() & 0x00FFFFFF;
                    result2 = result;
		            if((result >> 23) == 0){
		            }
		            else{		//negativna cifra
				        result = result << 8;
				        result  = ~result + 1;
				        result  = result >> 8;				
				        result = -result;
		            }
			        av_result += result;
                    av_result2 += result2;
			        result=0;
                    result2=0;
		        }
		
		        av_result = av_result / AV_RATE ;
                av_result2 = av_result2 / AV_RATE ;
		        //printNumberLn(av_result >> SHIFT, DEC);
                printf("av_result: 0x%08x\n",(av_result >> SHIFT));
                printf("av_result2: 0x%08x\n",av_result2);
		        av_result = 0;
                av_result2 = 0;
                count++;
                xSemaphoreGive(xSemaphore);
            }
        }

        vTaskDelay(200 / portTICK_PERIOD_MS);             
    }      

}


/* TODO : ADD EVENT DRIVEN UART CODE -- POLLING VERY SLOW */

void console_task(void *pvParameter)
{
    
    uint8_t j = 0;

    for(;;){

        if(xSemaphore != NULL)
        {
            
            if(xSemaphoreTake (xSemaphore, (TickType_t) (10 / portTICK_PERIOD_MS)) == pdTRUE)
            {
                //ESP_LOGD(task_console, "xSemaphoreTake worked!!");
                vTaskDelay(200 / portTICK_PERIOD_MS);
                j = getchar();
                if(j == 'a')ESP_LOGD(task_console, "getchar worked!!");
                if(j == 's'){
                    ESP_LOGD(task_console, "self_calibrate...");
                    MAX11210_self_calib();
                }    
                if(j == 'r'){
                    ESP_LOGD(task_console, "read registers...");
                    read_registers();
                }
                if(j == 'w'){
                    ESP_LOGD(task_console, "Write CTRL3 0x00...");
                    MAX11210_write_reg(CTRL3,0x00,0,0);
                }       
                xSemaphoreGive(xSemaphore);
            }
           // else ESP_LOGE(task_console, "xSemaphoreTake failed!!");

        } 
    
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }

}



void app_main()
{
    
    xSemaphore = xSemaphoreCreateMutex();
  // vSemaphoreCreateBinary( xSemaphore );
    xTaskCreate(&blink_task,               //Pointer to the function of the task (function pointer)
    		    "blink_task",              //Debug task name
				 2048, //Stack size
				 NULL,                     //pointer to task parameters
				 10,                        //task priority
				 NULL);                    //task handel


    xTaskCreate(&spi_task,               //Pointer to the function of the task (function pointer)
    		    "spi_task",              //Debug task name
				 2048,                   //Stack size
				 NULL,                   //pointer to task parameters
				 5,                      //task priority
				 NULL);                  //task handel

    xTaskCreate(&console_task,               //Pointer to the function of the task (function pointer)
    		    "console_task",              //Debug task name
				 2048,                   //Stack size
				 NULL,                   //pointer to task parameters
				 4,                      //task priority
				 NULL);                  //task handel


}
