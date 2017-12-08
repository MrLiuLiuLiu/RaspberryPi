/**
  ******************************************************************************
  * @file 		MotoRunnerB
  * @author  	Innovati Team
  * @version  	V0.1.0
  * @date     	07/18/2011
  * @brief  	Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Innovati SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Innovati, Inc</center></h2>
  */
/* Includes ------------------------------------------------------------------*/
#include "arm32f.h"
#include "I2CRoutines.h"
#include "MotorRunnerB.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*----------------------command list------------------------------------------*/                                                                
/*----------------------------------------------------------------------------*/
MotorRunnerB::MotorRunnerB(uint8_t mySlaveID)
{
	SlaveID = mySlaveID;
    InitArmCommander();
};
void MotorRunnerB::ForwardA(uint8_t Speed)
{
  __innoCommandBuff__[0] = 88;
  __innoCommandBuff__[2] = Speed;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}
void MotorRunnerB::ForwardB(uint8_t Speed)
{
  __innoCommandBuff__[0] = 89;
  __innoCommandBuff__[2] = Speed;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}
void MotorRunnerB::BackwardA(uint8_t Speed)
{
  __innoCommandBuff__[0] = 92;
  __innoCommandBuff__[2] = Speed;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}
void MotorRunnerB::BackwardB(uint8_t Speed)
{
  __innoCommandBuff__[0] = 93;
  __innoCommandBuff__[2] = Speed;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}   
void MotorRunnerB::StopA(void)
{
  __innoCommandBuff__[0] = 96;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}
void MotorRunnerB::StopB(void)
{
  __innoCommandBuff__[0] = 97;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}
void MotorRunnerB::StopDual(void)
{
  __innoCommandBuff__[0] = 98;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}
void MotorRunnerB::BrakeA(void)
{
  __innoCommandBuff__[0] = 99;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}
void MotorRunnerB::BrakeB(void)
{
  __innoCommandBuff__[0] = 100;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}
void MotorRunnerB::BrakeDual(void)
{
  __innoCommandBuff__[0] = 101;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 3);
}  						  

void MotorRunnerB::ForwardAB(uint8_t DutyCycleA, uint8_t DutyCycleB)
{        
  __innoCommandBuff__[0] = 90;
  __innoCommandBuff__[2] = DutyCycleA;
  __innoCommandBuff__[3] = DutyCycleB;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 6);
}

void MotorRunnerB::ForwardDual(uint8_t DutyCycle)
{        
  __innoCommandBuff__[0] = 91;
  __innoCommandBuff__[2] = DutyCycle;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::BackwardAB(uint8_t DutyCycleA, uint8_t DutyCycleB)
{         
  __innoCommandBuff__[0] = 94;
  __innoCommandBuff__[2] = DutyCycleA;
  __innoCommandBuff__[3] = DutyCycleB;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::BackwardDual(uint8_t DutyCycle)
{        
  __innoCommandBuff__[0] = 95;
  __innoCommandBuff__[2] = DutyCycle;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDirA(uint8_t Dir)
{   
  __innoCommandBuff__[0] = 102;
  __innoCommandBuff__[2] = Dir;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDirB(uint8_t Dir)
{     
  __innoCommandBuff__[0] = 103;
  __innoCommandBuff__[2] = Dir;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDirAB(uint8_t DirA, uint8_t DirB)
{          
  __innoCommandBuff__[0] = 104;
  __innoCommandBuff__[2] = DirA;
  __innoCommandBuff__[3] = DirB;  
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 6);
}

void MotorRunnerB::SetDirDual(uint8_t Dir)
{       
  __innoCommandBuff__[0] = 105;
  __innoCommandBuff__[2] = Dir;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDCA(uint8_t Spd)
{          
  __innoCommandBuff__[0] = 106;
  __innoCommandBuff__[2] = Spd;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDCB(uint8_t Spd)
{          
  __innoCommandBuff__[0] = 107;
  __innoCommandBuff__[2] = Spd;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::SetDCAB(uint8_t SpdA, uint8_t SpdB)
{          
  __innoCommandBuff__[0] = 108;
  __innoCommandBuff__[2] = SpdA;
  __innoCommandBuff__[3] = SpdB;  
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 6);
}

void MotorRunnerB::SetDCDual(uint8_t Spd)
{         
  __innoCommandBuff__[0] = 109;
  __innoCommandBuff__[2] = Spd;
  __i2cWriteBuffer(__innoCommandBuff__, SlaveID, 5);
}

void MotorRunnerB::GetDCA(uint8_t& Spd)
{  
  __innoCommandBuff__[0] = 110;
  __innoNumByteToRead__ = 2;
  if(!__i2cReadBuffer(__innoCommandBuff__, SlaveID, 3, &__innoNumByteToRead__))
  { 
	  Spd = __innoCommandBuff__[0];
  }	        
}

void MotorRunnerB::GetDCB(uint8_t& Spd)
{  
  __innoCommandBuff__[0] = 111;
  __innoNumByteToRead__ = 2;
  if(!__i2cReadBuffer(__innoCommandBuff__, SlaveID, 3, &__innoNumByteToRead__))
  {  
	  Spd = __innoCommandBuff__[0];
  }	        
}

void MotorRunnerB::GetDirA(uint8_t& Dir)
{  
  __innoCommandBuff__[0] = 112;
  __innoNumByteToRead__ = 2;
  if(!__i2cReadBuffer(__innoCommandBuff__, SlaveID, 3, &__innoNumByteToRead__))
  {
	  Dir = __innoCommandBuff__[0];
  }	        
}

void MotorRunnerB::GetDirB(uint8_t& Dir)
{  
  __innoCommandBuff__[0] = 113;
  __innoNumByteToRead__ = 2;
  if(!__i2cReadBuffer(__innoCommandBuff__, SlaveID, 3, &__innoNumByteToRead__))
  { 
	  Dir = __innoCommandBuff__[0];
  }	        
}
  


