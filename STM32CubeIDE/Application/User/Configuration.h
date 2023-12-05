/*
 * Configuratoin.h
 *
 *  Created on: 10 Feb 2022
 *      Author: robin
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Generic includes ----------------------------------------------------------*/
#include "stdbool.h"
#include "string.h"

/* Public definitions ------------------------------------------------------------*/
/** Data definitions **/
#define DEV_DEFINE_BUFFER_SIZE     1024
#define DEV_DEFINE_NO_BUFFERS      2
#define DEV_DEFINE_ADC_NO_CHANNELS 3
#define DEV_DEFINE_ADC_NO_SAMPLES  10

typedef struct deviceData_struct
{
  unsigned int rxId;
  unsigned int rxCount[DEV_DEFINE_NO_BUFFERS];
  uint8_t      rxArray[DEV_DEFINE_NO_BUFFERS][DEV_DEFINE_BUFFER_SIZE];
  unsigned int txId;
  unsigned int txCount[DEV_DEFINE_NO_BUFFERS];
  uint8_t      txArray[DEV_DEFINE_NO_BUFFERS][DEV_DEFINE_BUFFER_SIZE];
} deviceData_t;

/** Task communication definitions **/
#define ALL_BITS UINT32_MAX
#define NO_BITS  0x00

/* Public macros -------------------------------------------------------------*/
#define EXTERNAL extern
#define LOCAL
#define DEV_DECLARE_ARRAYS(location)                                                                                                       \
  /** debug data **/                                                                                                                       \
  location deviceData_t deviceDebug;                                                                                                       \
  /** device data **/                                                                                                                      \
  location deviceData_t deviceGps;                                                                                                         \
  location deviceData_t deviceBps;                                                                                                         \
  location deviceData_t deviceEeprom;                                                                                                      \
  location deviceData_t deviceAdc1;                                                                                                        \
  location deviceData_t deviceAdc2;                                                                                                        \
  location deviceData_t deviceAdc3;                                                                                                        \
  location deviceData_t deviceDac;

#define DEV_PERIPHERAL_TYPEDEFS(location)                                                                                                  \
  location DMA_HandleTypeDef  hdma_adc1;                                                                                                   \
  location ADC_HandleTypeDef  hadc1;                                                                                                       \
  location DAC_HandleTypeDef  hdac;                                                                                                        \
  location I2C_HandleTypeDef  hi2c1;                                                                                                       \
  location DMA_HandleTypeDef  hdma_spi3_rx;                                                                                                \
  location DMA_HandleTypeDef  hdma_spi3_tx;                                                                                                \
  location SPI_HandleTypeDef  hspi3;                                                                                                       \
  location TIM_HandleTypeDef  htim1;                                                                                                       \
  location TIM_HandleTypeDef  htim6;                                                                                                       \
  location DMA_HandleTypeDef  hdma_usart1_rx;                                                                                              \
  location DMA_HandleTypeDef  hdma_usart1_tx;                                                                                              \
  location DMA_HandleTypeDef  hdma_usart2_rx;                                                                                              \
  location DMA_HandleTypeDef  hdma_usart2_tx;                                                                                              \
  location UART_HandleTypeDef huart1;                                                                                                      \
  location UART_HandleTypeDef huart2;                                                                                                      \
  location TIM_HandleTypeDef  htim2;

/** peripheral device names **/
#define DEV_HANDLE_DEBUG         huart2
#define DEV_HANDLE_DEBUG_DMA_RX  hdma_usart2_rx
#define DEV_HANDLE_DEBUG_DMA_TX  hdma_usart2_tx
#define DEV_HANDLE_GPS           huart1
#define DEV_HANDLE_GPS_DMA_RX    hdma_usart1_rx
#define DEV_HANDLE_GPS_DMA_TX    hdma_usart1_tx
#define DEV_HANDLE_BPS           hi2c1
#define DEV_HANDLE_EEPROM        hspi3
#define DEV_HANDLE_EEPROM_DMA_RX hdma_spi3_rx
#define DEV_HANDLE_EEPROM_DMA_TX hdma_spi3_tx
#define DEV_HANDLE_ADC_1         hadc1
#define DEV_HANDLE_ADC_1_DMA     hdma_adc1
#define DEV_HANDLE_ADC_2         hadc1
#define DEV_HANDLE_ADC_3         hadc1
#define DEV_HANDLE_TIM_1         htim1
#define DEV_HANDLE_TIM_2         htim2
#define DEV_HANDLE_TIM_6         htim6
#define DEV_HANDLE_DAC           hdac

/* Public function prototypes ------------------------------------------------*/

#endif /* CONFIGURATION_H_ */
