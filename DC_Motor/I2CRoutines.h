/**
  ******************************************************************************
  * @file OptimizedI2Cexamples/inc/I2CRoutines.h
  * @author  MCD Application Team
  * @version  V4.0.0
  * @date  06/18/2010
  * @brief  Header for I2CRoutines.c
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2CROUTINES_H
#define __I2CROUTINES_H

void ResetModule(void);
extern uint8_t __innoCommandBuff__[32], __innoNumByteToRead__;
void __i2cWriteBuffer(uint8_t* pBuffer, uint8_t I2C_DEV_ADDR, uint8_t NumByteToWrite);
uint32_t __i2cReadBuffer(uint8_t* pBuffer, uint8_t I2C_DEV_ADDR, uint8_t NumByteToWrite, uint8_t *NumByteToRead);
void InitArmCommander(void);

#endif



/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
