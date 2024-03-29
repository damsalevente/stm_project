/**
  ******************************************************************************
  * File Name          : SPI.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */
typedef struct sensor_data_t {
 uint16_t accx,accy,accz;
 uint16_t gx,gy,gz;
}sensor_data_t;
/* USER CODE END Private defines */

void MX_SPI2_Init(void);


/* USER CODE BEGIN Prototypes */
void NAP_SPI_Read( SPI_HandleTypeDef* spiHandle, uint8_t *data,volatile uint8_t *rec);
void NAP_SPI_Write( SPI_HandleTypeDef* spiHandle, uint8_t *addr,volatile uint8_t *data);
void NAP_SPI_INIT_Modify(uint8_t *addr, uint8_t *data);
void NAP_SPI_INIT_LSM6DS3(uint8_t config);
void NAP_SPI_Check_Fifo(uint8_t *result);
void NAP_SPI_Read_Fifo(uint16_t *resultArray,uint8_t  size);
sensor_data_t NAP_SPI_GetData();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
