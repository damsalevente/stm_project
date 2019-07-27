/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void transmit_sensordata(sensor_data_t sd)
{
  char *msg = "\r\n";
  HAL_UART_Transmit(&huart2, msg, 3,0xff);

  uint8_t data = sd.accx & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.accx >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

  data = sd.accy & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.accy >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

  data = sd.accz & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.accz >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

  data = sd.gx & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.gx >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

  data = sd.gy & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.gy >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

  data = sd.gz  & 0x00ff;
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);
  data = sd.gz >>8; 
  HAL_UART_Transmit(&huart2, &data, 1, 0xff);

}

void transmit_buffer(sensor_data_t *buffer, uint16_t size)
{
  for(uint16_t i = 0; i<size; i++)
  {
    transmit_sensordata(buffer[i]);
  }
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
