/**
  ******************************************************************************
  * @file    stm8_eval_i2c_ee.h
  * @author  MCD Application Team
  * @version V2.1.3
  * @date    28-June-2013
  * @brief   This file contains all the functions prototypes for the stm8_eval_i2c_ee
  *          firmware driver.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8_EVAL_I2C_EE_H
#define __STM8_EVAL_I2C_EE_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM8_EVAL
  * @{
  */ 

/** @addtogroup Common
  * @{
  */
  
/** @addtogroup STM8_EVAL_I2C_EE
  * @{
  */  

/* Private types -------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
  
/** @defgroup STM8_EVAL_I2C_EE_Private_define
  * @{
  */
#define sEEAddress             0x56  

#define sEE_I2C                I2C1
#define I2C_SPEED              200000
#define I2C_SLAVE_ADDRESS7     0xA0
   
/**
  * @}
  */ 
  
/* Private macro -------------------------------------------------------------*/

/** @defgroup STM8_EVAL_I2C_EE_Exported_Functions
  * @{
  */ 
void sEE_DeInit(void);
void sEE_Init(void);
void sEE_WriteByte(uint8_t* pBuffer, uint16_t WriteAddr);
void sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
void sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
void sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
void sEE_WaitEepromStandbyState(void);
#endif /* __STM8_EVAL_I2C_EE_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/