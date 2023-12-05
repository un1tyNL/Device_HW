/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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

/* Includes ------------------------------------------------------------------*/
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
DMA_HandleTypeDef hdma_memtomem_dma2_stream1;
DMA_HandleTypeDef hdma_memtomem_dma2_stream2;
DMA_HandleTypeDef hdma_memtomem_dma2_stream3;

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma2_stream1
  *   hdma_memtomem_dma2_stream2
  *   hdma_memtomem_dma2_stream3
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma2_stream1 on DMA2_Stream1 */
  hdma_memtomem_dma2_stream1.Instance = DMA2_Stream1;
  hdma_memtomem_dma2_stream1.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma2_stream1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma2_stream1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream1.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma2_stream1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma2_stream1.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream1.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream1) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure DMA request hdma_memtomem_dma2_stream2 on DMA2_Stream2 */
  hdma_memtomem_dma2_stream2.Instance = DMA2_Stream2;
  hdma_memtomem_dma2_stream2.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream2.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream2.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream2.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma2_stream2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma2_stream2.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream2.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma2_stream2.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma2_stream2.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream2.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream2) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure DMA request hdma_memtomem_dma2_stream3 on DMA2_Stream3 */
  hdma_memtomem_dma2_stream3.Instance = DMA2_Stream3;
  hdma_memtomem_dma2_stream3.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream3.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream3.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream3.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma2_stream3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma2_stream3.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream3.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma2_stream3.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream3.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma2_stream3.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream3.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream3) != HAL_OK)
  {
    Error_Handler();
  }

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA1_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
