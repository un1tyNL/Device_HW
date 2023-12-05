/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Configuration.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t      osStaticThreadDef_t;
typedef StaticTimer_t     osStaticTimerDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
/* USER CODE BEGIN PTD */
DEV_PERIPHERAL_TYPEDEFS(EXTERNAL);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/** debug messages **/
uint8_t DBG_initCompleteMessage[] = "Device is running...\n\r";
uint8_t DBG_clearScreenMessage[]  = { '\r', 0x1B, 0x5B, 0x32, 0x4A };

DEV_DECLARE_ARRAYS(LOCAL);

/* USER CODE END Variables */
/* Definitions for osTask */
osThreadId_t         osTaskHandle;
uint32_t             osTaskBuffer[128];
osStaticThreadDef_t  osTaskControlBlock;
const osThreadAttr_t osTask_attributes = {
  .name       = "osTask",
  .cb_mem     = &osTaskControlBlock,
  .cb_size    = sizeof(osTaskControlBlock),
  .stack_mem  = &osTaskBuffer[0],
  .stack_size = sizeof(osTaskBuffer),
  .priority   = (osPriority_t) osPriorityNormal,
};
/* Definitions for deviceTask */
osThreadId_t         deviceTaskHandle;
uint32_t             deviceTaskBuffer[128];
osStaticThreadDef_t  deviceTaskControlBlock;
const osThreadAttr_t deviceTask_attributes = {
  .name       = "deviceTask",
  .cb_mem     = &deviceTaskControlBlock,
  .cb_size    = sizeof(deviceTaskControlBlock),
  .stack_mem  = &deviceTaskBuffer[0],
  .stack_size = sizeof(deviceTaskBuffer),
  .priority   = (osPriority_t) osPriorityNormal,
};
/* Definitions for debugTask */
osThreadId_t         debugTaskHandle;
uint32_t             debugTaskBuffer[128];
osStaticThreadDef_t  debugTaskControlBlock;
const osThreadAttr_t debugTask_attributes = {
  .name       = "debugTask",
  .cb_mem     = &debugTaskControlBlock,
  .cb_size    = sizeof(debugTaskControlBlock),
  .stack_mem  = &debugTaskBuffer[0],
  .stack_size = sizeof(debugTaskBuffer),
  .priority   = (osPriority_t) osPriorityLow,
};
/* Definitions for varTimer */
osTimerId_t         varTimerHandle;
osStaticTimerDef_t  varTimerControlBlock;
const osTimerAttr_t varTimer_attributes = {
  .name    = "varTimer",
  .cb_mem  = &varTimerControlBlock,
  .cb_size = sizeof(varTimerControlBlock),
};
/* Definitions for varTimer1 */
osTimerId_t         varTimer1Handle;
osStaticTimerDef_t  varTimer1ControlBlock;
const osTimerAttr_t varTimer1_attributes = {
  .name    = "varTimer1",
  .cb_mem  = &varTimer1ControlBlock,
  .cb_size = sizeof(varTimer1ControlBlock),
};
/* Definitions for varMutex */
osMutexId_t         varMutexHandle;
osStaticMutexDef_t  varMutexControlBlock;
const osMutexAttr_t varMutex_attributes = {
  .name    = "varMutex",
  .cb_mem  = &varMutexControlBlock,
  .cb_size = sizeof(varMutexControlBlock),
};
/* Definitions for varMutex1 */
osMutexId_t         varMutex1Handle;
osStaticMutexDef_t  varMutex1ControlBlock;
const osMutexAttr_t varMutex1_attributes = {
  .name    = "varMutex1",
  .cb_mem  = &varMutex1ControlBlock,
  .cb_size = sizeof(varMutex1ControlBlock),
};
/* Definitions for varMutex2 */
osMutexId_t         varMutex2Handle;
osStaticMutexDef_t  varMutex2ControlBlock;
const osMutexAttr_t varMutex2_attributes = {
  .name    = "varMutex2",
  .cb_mem  = &varMutex2ControlBlock,
  .cb_size = sizeof(varMutex2ControlBlock),
};
/* Definitions for varMutex4 */
osMutexId_t         varMutex4Handle;
osStaticMutexDef_t  varMutex4ControlBlock;
const osMutexAttr_t varMutex4_attributes = {
  .name    = "varMutex4",
  .cb_mem  = &varMutex4ControlBlock,
  .cb_size = sizeof(varMutex4ControlBlock),
};
/* Definitions for varSemaphoreB */
osSemaphoreId_t         varSemaphoreBHandle;
osStaticSemaphoreDef_t  varSemaphoreBControlBlock;
const osSemaphoreAttr_t varSemaphoreB_attributes = {
  .name    = "varSemaphoreB",
  .cb_mem  = &varSemaphoreBControlBlock,
  .cb_size = sizeof(varSemaphoreBControlBlock),
};
/* Definitions for varSemaphoreB1 */
osSemaphoreId_t         varSemaphoreB1Handle;
osStaticSemaphoreDef_t  varSemaphoreB1ControlBlock;
const osSemaphoreAttr_t varSemaphoreB1_attributes = {
  .name    = "varSemaphoreB1",
  .cb_mem  = &varSemaphoreB1ControlBlock,
  .cb_size = sizeof(varSemaphoreB1ControlBlock),
};
/* Definitions for varSemaphoreB2 */
osSemaphoreId_t         varSemaphoreB2Handle;
osStaticSemaphoreDef_t  varSemaphoreB2ControlBlock;
const osSemaphoreAttr_t varSemaphoreB2_attributes = {
  .name    = "varSemaphoreB2",
  .cb_mem  = &varSemaphoreB2ControlBlock,
  .cb_size = sizeof(varSemaphoreB2ControlBlock),
};
/* Definitions for varSemaphoreB3 */
osSemaphoreId_t         varSemaphoreB3Handle;
osStaticSemaphoreDef_t  varSemaphoreB3ControlBlock;
const osSemaphoreAttr_t varSemaphoreB3_attributes = {
  .name    = "varSemaphoreB3",
  .cb_mem  = &varSemaphoreB3ControlBlock,
  .cb_size = sizeof(varSemaphoreB3ControlBlock),
};
/* Definitions for varSemaphoreB4 */
osSemaphoreId_t         varSemaphoreB4Handle;
osStaticSemaphoreDef_t  varSemaphoreB4ControlBlock;
const osSemaphoreAttr_t varSemaphoreB4_attributes = {
  .name    = "varSemaphoreB4",
  .cb_mem  = &varSemaphoreB4ControlBlock,
  .cb_size = sizeof(varSemaphoreB4ControlBlock),
};
/* Definitions for varSemaphoreC */
osSemaphoreId_t         varSemaphoreCHandle;
osStaticSemaphoreDef_t  varSemaphoreCControlBlock;
const osSemaphoreAttr_t varSemaphoreC_attributes = {
  .name    = "varSemaphoreC",
  .cb_mem  = &varSemaphoreCControlBlock,
  .cb_size = sizeof(varSemaphoreCControlBlock),
};
/* Definitions for varSemaphoreC1 */
osSemaphoreId_t         varSemaphoreC1Handle;
osStaticSemaphoreDef_t  varSemaphoreC1ControlBlock;
const osSemaphoreAttr_t varSemaphoreC1_attributes = {
  .name    = "varSemaphoreC1",
  .cb_mem  = &varSemaphoreC1ControlBlock,
  .cb_size = sizeof(varSemaphoreC1ControlBlock),
};
/* Definitions for varSemaphoreC2 */
osSemaphoreId_t         varSemaphoreC2Handle;
osStaticSemaphoreDef_t  varSemaphoreC2ControlBlock;
const osSemaphoreAttr_t varSemaphoreC2_attributes = {
  .name    = "varSemaphoreC2",
  .cb_mem  = &varSemaphoreC2ControlBlock,
  .cb_size = sizeof(varSemaphoreC2ControlBlock),
};
/* Definitions for varSemaphoreC3 */
osSemaphoreId_t         varSemaphoreC3Handle;
osStaticSemaphoreDef_t  varSemaphoreC3ControlBlock;
const osSemaphoreAttr_t varSemaphoreC3_attributes = {
  .name    = "varSemaphoreC3",
  .cb_mem  = &varSemaphoreC3ControlBlock,
  .cb_size = sizeof(varSemaphoreC3ControlBlock),
};
/* Definitions for varSemaphoreC4 */
osSemaphoreId_t         varSemaphoreC4Handle;
osStaticSemaphoreDef_t  varSemaphoreC4ControlBlock;
const osSemaphoreAttr_t varSemaphoreC4_attributes = {
  .name    = "varSemaphoreC4",
  .cb_mem  = &varSemaphoreC4ControlBlock,
  .cb_size = sizeof(varSemaphoreC4ControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void osTaskEntry(void *argument);
void deviceTaskEntry(void *argument);
void debugTaskEntry(void *argument);
void varTimerCallback(void *argument);
void varTimer2Callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void          configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
}

__weak unsigned long getRunTimeCounterValue(void)
{
  return 0;
}
/* USER CODE END 1 */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of varMutex */
  varMutexHandle = osMutexNew(&varMutex_attributes);

  /* creation of varMutex1 */
  varMutex1Handle = osMutexNew(&varMutex1_attributes);

  /* creation of varMutex2 */
  varMutex2Handle = osMutexNew(&varMutex2_attributes);

  /* creation of varMutex4 */
  varMutex4Handle = osMutexNew(&varMutex4_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of varSemaphoreB */
  varSemaphoreBHandle = osSemaphoreNew(1, 1, &varSemaphoreB_attributes);

  /* creation of varSemaphoreB1 */
  varSemaphoreB1Handle = osSemaphoreNew(1, 1, &varSemaphoreB1_attributes);

  /* creation of varSemaphoreB2 */
  varSemaphoreB2Handle = osSemaphoreNew(1, 1, &varSemaphoreB2_attributes);

  /* creation of varSemaphoreB3 */
  varSemaphoreB3Handle = osSemaphoreNew(1, 1, &varSemaphoreB3_attributes);

  /* creation of varSemaphoreB4 */
  varSemaphoreB4Handle = osSemaphoreNew(1, 1, &varSemaphoreB4_attributes);

  /* creation of varSemaphoreC */
  varSemaphoreCHandle = osSemaphoreNew(2, 2, &varSemaphoreC_attributes);

  /* creation of varSemaphoreC1 */
  varSemaphoreC1Handle = osSemaphoreNew(2, 2, &varSemaphoreC1_attributes);

  /* creation of varSemaphoreC2 */
  varSemaphoreC2Handle = osSemaphoreNew(2, 2, &varSemaphoreC2_attributes);

  /* creation of varSemaphoreC3 */
  varSemaphoreC3Handle = osSemaphoreNew(2, 2, &varSemaphoreC3_attributes);

  /* creation of varSemaphoreC4 */
  varSemaphoreC4Handle = osSemaphoreNew(2, 2, &varSemaphoreC4_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of varTimer */
  varTimerHandle = osTimerNew(varTimerCallback, osTimerPeriodic, NULL, &varTimer_attributes);

  /* creation of varTimer1 */
  varTimer1Handle = osTimerNew(varTimer2Callback, osTimerPeriodic, NULL, &varTimer1_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of osTask */
  osTaskHandle = osThreadNew(osTaskEntry, NULL, &osTask_attributes);

  /* creation of deviceTask */
  deviceTaskHandle = osThreadNew(deviceTaskEntry, NULL, &deviceTask_attributes);

  /* creation of debugTask */
  debugTaskHandle = osThreadNew(debugTaskEntry, NULL, &debugTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_osTaskEntry */
/**
 * @brief  Function implementing the osTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_osTaskEntry */
void osTaskEntry(void *argument)
{
  /* USER CODE BEGIN osTaskEntry */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END osTaskEntry */
}

/* USER CODE BEGIN Header_deviceTaskEntry */
/**
 * @brief Function implementing the deviceTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_deviceTaskEntry */
void deviceTaskEntry(void *argument)
{
  /* USER CODE BEGIN deviceTaskEntry */
  uint32_t notificationBits;
  deviceGps.rxId = 0;
  __HAL_DMA_ENABLE_IT(&DEV_HANDLE_GPS_DMA_RX, DMA_IT_TC);
  __HAL_UART_ENABLE_IT(&DEV_HANDLE_GPS, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&DEV_HANDLE_GPS, deviceGps.rxArray[deviceGps.rxId], DEV_DEFINE_BUFFER_SIZE);
  deviceDebug.rxId = 0;
  __HAL_DMA_ENABLE_IT(&DEV_HANDLE_DEBUG_DMA_RX, DMA_IT_TC);
  __HAL_UART_ENABLE_IT(&DEV_HANDLE_DEBUG, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&DEV_HANDLE_DEBUG, deviceDebug.rxArray[deviceDebug.rxId], DEV_DEFINE_BUFFER_SIZE);
  /* Infinite loop */
  for (;;)
  {
    xTaskNotifyWait(NO_BITS, ALL_BITS, &notificationBits, portMAX_DELAY);
    // Received from GPS transfer to debug.
    if (notificationBits & (1 << 0))
    {
      memcpy(deviceDebug.txArray[deviceDebug.txId], deviceGps.rxArray[deviceGps.rxId], deviceGps.rxCount[deviceGps.rxId]);
      deviceDebug.txCount[deviceDebug.txId] = deviceGps.rxCount[deviceGps.rxId];
      deviceGps.rxId                        = (deviceGps.rxId + 1) % DEV_DEFINE_NO_BUFFERS;
    }
    // Received from debug transfer to GPS.
    if (notificationBits & (1 << 1))
    {
      memcpy(deviceGps.txArray[deviceGps.txId], deviceDebug.rxArray[deviceDebug.rxId], deviceDebug.rxCount[deviceDebug.rxId]);
      deviceGps.txCount[deviceGps.txId] = deviceDebug.rxCount[deviceDebug.rxId];
      deviceDebug.rxId                  = (deviceDebug.rxId + 1) % DEV_DEFINE_NO_BUFFERS;
    }
    xTaskNotify(debugTaskHandle, notificationBits, eSetBits);
  }
  /* USER CODE END deviceTaskEntry */
}

/* USER CODE BEGIN Header_debugTaskEntry */
/**
 * @brief Function implementing the debugTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_debugTaskEntry */
void debugTaskEntry(void *argument)
{
  /* USER CODE BEGIN debugTaskEntry */
  uint32_t notificationBits;
  deviceDebug.txId = 0;
  HAL_UART_Transmit(&huart2, DBG_initCompleteMessage, sizeof(DBG_initCompleteMessage), 500);
  /* Infinite loop */
  for (;;)
  {
    xTaskNotifyWait(0x00, UINT32_MAX, &notificationBits, portMAX_DELAY);

    // Received from GPS transfer to debug.
    if (notificationBits & (1 << 0))
    {
      if ((deviceDebug.txCount[deviceDebug.txId] != 0) && (deviceDebug.txArray[deviceDebug.txId][0] != 0))
      {
        HAL_UART_Transmit(&DEV_HANDLE_DEBUG, DBG_clearScreenMessage, sizeof(DBG_clearScreenMessage), 500);
        HAL_UART_Transmit_DMA(&DEV_HANDLE_DEBUG, deviceDebug.txArray[deviceDebug.txId], deviceDebug.txCount[deviceDebug.txId]);
        deviceDebug.txId = (deviceDebug.txId + 1) % DEV_DEFINE_NO_BUFFERS;
      }
    }
    // Received from debug transfer to GPS.
    else if ((notificationBits & (1 << 1)) && (deviceGps.txCount[deviceGps.txId] != 0))
    {
      char DEV_gpsHotRestart[]    = "$PMTK101*32\r\n";
      char DEV_gpsWarmRestart[]    = "$PMTK102*31\r\n";
      char DEV_gpsColdRestart[]    = "$PMTK103*30\r\n";
      char DEV_gpsFullColdRestart[]    = "$PMTK104*37\r\n";
      char DEV_gpsUpdateRate1Hz[]  = "$PMTK220,1000*1F\r\n";
      char DEV_gpsUpdateRate5Hz[]  = "$PMTK220,200*2C\r\n;";
      char DEV_gpsUpdateRate10Hz[] = "$PMTK220,100*2F\r\n";
      char DEV_gpsGGAOnly[]        = "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";
      char DEV_gpsThresholdLow[]     = "$PMTK386,0.2*3F\r\n";
      char DEV_gpsThresholdHigh[]    = "$PMTK386,2.0*3F\r\n";
      char DEV_gpsEnableWAAS[] = "$PMTK301,2*0A\r\n";
      char DEV_gpsEnableSBAS[] = "$PMTK313,1*2E\r\n";

      if ((deviceGps.txCount[deviceGps.txId] != 0) && (deviceGps.txArray[deviceGps.txId][0] != 0))
      {
        switch (deviceGps.txArray[deviceGps.txId][0])
        {
          case '0':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsWarmRestart, strlen(DEV_gpsWarmRestart));
          case '1':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsUpdateRate1Hz, strlen(DEV_gpsUpdateRate1Hz));
          case '2':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsUpdateRate5Hz, strlen(DEV_gpsUpdateRate5Hz));
          case '3':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsUpdateRate10Hz, strlen(DEV_gpsUpdateRate10Hz));
          case '4':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsGGAOnly, strlen(DEV_gpsGGAOnly));
          case '5':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsThresholdLow, strlen(DEV_gpsThresholdLow));
          case '6':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsThresholdHigh, strlen(DEV_gpsThresholdHigh));
          case '7':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsEnableWAAS, strlen(DEV_gpsEnableWAAS));
          case '8':
            HAL_UART_Transmit_DMA(&DEV_HANDLE_GPS, (uint8_t *) DEV_gpsEnableSBAS, strlen(DEV_gpsEnableSBAS));
          default:
            break;
        }

        deviceGps.txId = (deviceGps.txId + 1) % DEV_DEFINE_NO_BUFFERS;
      }
    }
    else
    {
      // Do nothing.
    }
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  }
  /* USER CODE END debugTaskEntry */
}

/* varTimerCallback function */
void varTimerCallback(void *argument)
{
  /* USER CODE BEGIN varTimerCallback */

  /* USER CODE END varTimerCallback */
}

/* varTimer2Callback function */
void varTimer2Callback(void *argument)
{
  /* USER CODE BEGIN varTimer2Callback */

  /* USER CODE END varTimer2Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
