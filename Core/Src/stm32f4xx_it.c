/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"
/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "Configuration.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN TD */
DEV_PERIPHERAL_TYPEDEFS(EXTERNAL);
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
DEV_DECLARE_ARRAYS(EXTERNAL);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles DMA1 stream2 global interrupt.
 */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
 * @brief This function handles DMA1 stream5 global interrupt.
 */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */
  extern osThreadId_t deviceTaskHandle;           // RTOS Task related to the DMA stream.
  size_t              deviceRxNextId;             // Buffer index for the next transfer.
  BaseType_t          xPrioTaskAwoken = pdFALSE;  // A higher priority task has become awake.
  uint32_t            notificationBit = 1 << 1;   // Set bit 0
  bool                isTransferCompleteInterrupt // Was the transfer complete interrupt enabled and triggered.
    = (__HAL_DMA_GET_FLAG(&DEV_HANDLE_DEBUG_DMA_RX, DMA_FLAG_TCIF1_5) && __HAL_DMA_GET_IT_SOURCE(&DEV_HANDLE_DEBUG_DMA_RX, DMA_IT_TC));
  if (isTransferCompleteInterrupt)
  {
    deviceDebug.rxCount[deviceDebug.rxId] = DEV_DEFINE_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&DEV_HANDLE_DEBUG_DMA_RX);
    deviceRxNextId                        = (deviceDebug.rxId + 1) % DEV_DEFINE_NO_BUFFERS;
  }
  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */
  if (isTransferCompleteInterrupt)
  {
    __HAL_DMA_CLEAR_FLAG(&DEV_HANDLE_DEBUG_DMA_RX,
                         DMA_FLAG_FEIF1_5 | DMA_FLAG_DMEIF1_5 | DMA_FLAG_TEIF1_5 | DMA_FLAG_HTIF1_5 | DMA_FLAG_TCIF1_5);
    __HAL_DMA_ENABLE(&DEV_HANDLE_DEBUG_DMA_RX);
    HAL_UART_Receive_DMA(&DEV_HANDLE_DEBUG, deviceDebug.rxArray[deviceRxNextId], DEV_DEFINE_BUFFER_SIZE);
    xTaskNotifyFromISR(deviceTaskHandle, notificationBit, eSetBits, &xPrioTaskAwoken);
    portYIELD_FROM_ISR(xPrioTaskAwoken);
  }
  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
 * @brief This function handles DMA1 stream6 global interrupt.
 */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
 * @brief This function handles ADC1, ADC2 and ADC3 interrupts.
 */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
 * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
 */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
 * @brief This function handles I2C1 event interrupt.
 */
void I2C1_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_EV_IRQn 0 */

  /* USER CODE END I2C1_EV_IRQn 0 */
  HAL_I2C_EV_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_EV_IRQn 1 */

  /* USER CODE END I2C1_EV_IRQn 1 */
}

/**
 * @brief This function handles I2C1 error interrupt.
 */
void I2C1_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_ER_IRQn 0 */

  /* USER CODE END I2C1_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_ER_IRQn 1 */

  /* USER CODE END I2C1_ER_IRQn 1 */
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
  bool isIdleFlagInterrupt
    = (__HAL_UART_GET_FLAG(&DEV_HANDLE_GPS, UART_FLAG_IDLE) && __HAL_UART_GET_IT_SOURCE(&DEV_HANDLE_GPS, UART_IT_IDLE));
  if (isIdleFlagInterrupt)
  {
    __HAL_DMA_DISABLE(&DEV_HANDLE_GPS_DMA_RX);
  }
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
  if (isIdleFlagInterrupt)
  {
    __HAL_UART_CLEAR_IDLEFLAG(&DEV_HANDLE_GPS);
  }
  /* USER CODE END USART1_IRQn 1 */
}

/**
 * @brief This function handles USART2 global interrupt.
 */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  bool isIdleFlagInterrupt
    = (__HAL_UART_GET_FLAG(&DEV_HANDLE_DEBUG, UART_FLAG_IDLE) && __HAL_UART_GET_IT_SOURCE(&DEV_HANDLE_DEBUG, UART_IT_IDLE));
  if (isIdleFlagInterrupt)
  {
    __HAL_DMA_DISABLE(&DEV_HANDLE_DEBUG_DMA_RX);
  }
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  if (isIdleFlagInterrupt)
  {
    __HAL_UART_CLEAR_IDLEFLAG(&DEV_HANDLE_DEBUG);
  }
  /* USER CODE END USART2_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
 * @brief This function handles DMA1 stream7 global interrupt.
 */
void DMA1_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream7_IRQn 0 */

  /* USER CODE END DMA1_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_tx);
  /* USER CODE BEGIN DMA1_Stream7_IRQn 1 */

  /* USER CODE END DMA1_Stream7_IRQn 1 */
}

/**
 * @brief This function handles SPI3 global interrupt.
 */
void SPI3_IRQHandler(void)
{
  /* USER CODE BEGIN SPI3_IRQn 0 */

  /* USER CODE END SPI3_IRQn 0 */
  HAL_SPI_IRQHandler(&hspi3);
  /* USER CODE BEGIN SPI3_IRQn 1 */

  /* USER CODE END SPI3_IRQn 1 */
}

/**
 * @brief This function handles TIM6 global interrupt and DAC1, DAC2 underrun error interrupts.
 */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_DAC_IRQHandler(&hdac);
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream5 global interrupt.
 * @details Clean up old-, start new transfer and notify task for processing.
 *  See https://www.freertos.org/xTaskNotifyFromISR.html
 */
void DMA2_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream5_IRQn 0 */
  extern osThreadId_t deviceTaskHandle;           // RTOS Task related to the DMA stream.
  size_t              deviceRxNextId;             // Buffer index for the next transfer.
  BaseType_t          xPrioTaskAwoken = pdFALSE;  // A higher priority task has become awake.
  uint32_t            notificationBit = 1 << 0;   // Set bit 0
  bool                isTransferCompleteInterrupt // Was the transfer complete interrupt enabled and triggered.
    = (__HAL_DMA_GET_FLAG(&DEV_HANDLE_GPS_DMA_RX, DMA_FLAG_TCIF1_5) && __HAL_DMA_GET_IT_SOURCE(&DEV_HANDLE_GPS_DMA_RX, DMA_IT_TC));
  if (isTransferCompleteInterrupt)
  {
    deviceGps.rxCount[deviceGps.rxId] = DEV_DEFINE_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&DEV_HANDLE_GPS_DMA_RX);
    deviceRxNextId                    = (deviceGps.rxId + 1) % DEV_DEFINE_NO_BUFFERS;
  }
  /* USER CODE END DMA2_Stream5_IRQn 0 */

  HAL_DMA_IRQHandler(&hdma_usart1_rx);

  /* USER CODE BEGIN DMA2_Stream5_IRQn 1 */
  if (isTransferCompleteInterrupt)
  {
    __HAL_DMA_CLEAR_FLAG(&DEV_HANDLE_GPS_DMA_RX,
                         DMA_FLAG_FEIF1_5 | DMA_FLAG_DMEIF1_5 | DMA_FLAG_TEIF1_5 | DMA_FLAG_HTIF1_5 | DMA_FLAG_TCIF1_5);
    __HAL_DMA_ENABLE(&DEV_HANDLE_GPS_DMA_RX);
    HAL_UART_Receive_DMA(&DEV_HANDLE_GPS, deviceGps.rxArray[deviceRxNextId], DEV_DEFINE_BUFFER_SIZE);
    xTaskNotifyFromISR(deviceTaskHandle, notificationBit, eSetBits, &xPrioTaskAwoken);
    portYIELD_FROM_ISR(xPrioTaskAwoken);
  }
  /* USER CODE END DMA2_Stream5_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream7 global interrupt.
 */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
