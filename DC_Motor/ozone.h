/**
  ******************************************************************************
  * @file 		Ozone.h
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
#include <inttypes.h>  
uint8_t CheckModule(void);
void ResetModule(void);
#include "TimeKeeperA.h"
#include "Accelerometer3A.h"
#include "Accelerometer3B.h"
#include "BarometerA.h"
#include "ColorRGB.h"
#include "CompassA.h"
#include "CompassB.h"
#include "GamepadPS.h"
#include "GamepadBT.h"
#include "IOExtenderA.h"
#include "IRController.h"
#include "JoyStick2A.h"
#include "JoyStick3A.h"
#include "KeypadA.h"
#include "LCD2X16A.h"
#include "LCD4X20A.h"
#include "MotorRunnerA.h"
#include "MotorRunnerB.h"
#include "MotorRunnerC.h"
#include "MR2x5.h"
#include "MR2x5a.h"
#include "MR2x30.h"
#include "MR2x30a.h"
#include "MR2x30b.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include "RF24G.h"
#include "ServoRunnerA.h"
#include "ServoRunner8.h"
#include "SonarA.h"
#include "SonarB.h"
#include "SR1.h"
#include "ThermometerA.h"
uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length);
