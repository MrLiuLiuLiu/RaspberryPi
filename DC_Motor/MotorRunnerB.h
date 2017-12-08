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
#ifndef __INNO_MOTOR_RUNNER_B
#define __INNO_MOTOR_RUNNER_B	
#include "innotype.h" 
class MotorRunnerB
{
    private:
	uint8_t SlaveID;
	public:
	MotorRunnerB(uint8_t);
	void ForwardA(uint8_t);
	void ForwardB(uint8_t);
	void BackwardA(uint8_t);
	void BackwardB(uint8_t);
	void StopA(void);
	void StopB(void);
	void StopDual(void);
	void BrakeA(void);
	void BrakeB(void);
	void BrakeDual(void);


	void ForwardAB(uint8_t, uint8_t);
	void ForwardDual(uint8_t);
	void BackwardAB(uint8_t, uint8_t);
	void BackwardDual(uint8_t);
	void SetDirA(uint8_t);
	void SetDirB(uint8_t);
	void SetDirAB(uint8_t, uint8_t);
	void SetDirDual(uint8_t);
	void SetDCA(uint8_t);
	void SetDCB(uint8_t);
	void SetDCAB(uint8_t, uint8_t);
	void SetDCDual(uint8_t);
	void GetDCA(uint8_t&);
	void GetDCB(uint8_t&);
	void GetDirA(uint8_t&);
	void GetDirB(uint8_t&);   
};
#endif



