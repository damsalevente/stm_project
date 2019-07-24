/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#include "spi.h"
#include "lsm6ds3.h"

/* USER CODE BEGIN 0 */
#define NAP_SPI_READ_FLAG 0x80
#define CONF_COUNT 10;

/* USER CODE END 0 */

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration    
    PB10     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();
  
    /**SPI2 GPIO Configuration    
    PB10     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
} 

// Todo: Read multiple, polling is probably fine tho 
void NAP_SPI_Read( SPI_HandleTypeDef* spiHandle, uint8_t data, uint8_t *rec)
{
  // the first bit is 1, indicating the read (lsm6ds3 datasheet spi config)
  data |= NAP_SPI_READ_FLAG;
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,GPIO_PIN_RESET);
  HAL_SPI_Transmit(spiHandle, &data,1,HAL_MAX_DELAY);
  HAL_SPI_Receive(spiHandle, rec,1,HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,GPIO_PIN_SET);
}

// R/W is 0 so we can use pointer
void NAP_SPI_Write( SPI_HandleTypeDef* spiHandle, uint8_t *addr, uint8_t *data)
{
  // Check if r/w permission is available 
  // the first bit is 1, indicating the read (lsm6ds3 datasheet spi config)
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,GPIO_PIN_RESET);
  HAL_SPI_Transmit(spiHandle, addr,1,HAL_MAX_DELAY);
  HAL_SPI_Transmit(spiHandle, data,1,HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,GPIO_PIN_SET);
}
void NAP_SPI_INIT_Modify(uint8_t addr, uint8_t data)
{
   uint8_t read_val = 0;
   NAP_SPI_Read(&hspi2, addr,&read_val);
   read_val |= data;
   NAP_SPI_Write(&hspi2, &addr, &read_val); 
}

void NAP_SPI_INIT_LSM6DS3(uint8_t config)
{
  /* default conf
   FIFO enabled
   Continuous mode
   12.5Hz
   Timestamp enabled 
   */
  if(config == 0)
  {
   // Continous Mode settings 110 in the first 3 register 
   NAP_SPI_INIT_Modify(FIFO_CTRL5,0x06);
   // Fifo ctrl 1 can set threshold, skip for now 
    //NAP_SPI_INIT_Modify(, );
   // Fifo ctrl2 register skipped
   //Fifo ctrol3 enable gyro to fifo
   NAP_SPI_INIT_Modify(FIFO_CTRL3,0x09);
   // Fifo odr selection set to 12.5Khz
   NAP_SPI_INIT_Modify(FIFO_CTRL5,1<<3);
   NAP_SPI_INIT_Modify(CTRL3_C,1<<6);
   NAP_SPI_INIT_Modify(CTRL1_XL, 1<<4);
   NAP_SPI_INIT_Modify(CTRL2_G, 1<<4);
  }
  
}
// returns result parameter as a number of how many unwritten data is in the fifo
void NAP_SPI_Check_Fifo(uint8_t *result)
{
  uint8_t addr = FIFO_STATUS1;
  NAP_SPI_Read(&hspi2,addr,result);
}
void NAP_SPI_Read_Fifo(uint16_t *resultArray,uint8_t  size)
{
  if(size<1)
  {
    return;
  }
  uint8_t data_l;
  uint8_t data_h;

  for(uint8_t i = 0; i<size;i++)
  {
    NAP_SPI_Read(&hspi2, FIFO_DATA_OUT_L, &data_l);
    NAP_SPI_Read(&hspi2, FIFO_DATA_OUT_H, &data_h);
    resultArray[i] = data_l | (data_h << 8);
  }
}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
