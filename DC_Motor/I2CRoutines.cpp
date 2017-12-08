#include <inttypes.h>
#include "Arduino.h" // for digitalWrite

#define BUFFER_LENGTH   44  
#define kinnoDelay      5
 
#define __kInnoTimeOut    500
uint8_t __innoCommandBuff__[BUFFER_LENGTH], __innoNumByteToRead__;
uint8_t __initI2C__  = 0, __i2cModuleStatus__=0, __i2cBusy__=0;

#if defined(__AVR_ATmega32U4__)

  #define   __SYNC__    0x02
  #define   __SDA__     0x04
  #define   __SCL__     0x08
    
  #define _SYNC_H_()    (PORTB |= __SYNC__)  
  #define _SYNC_L_()    (PORTB &= ~__SYNC__)
  void _SCL_H_(void) 
  {
    DDRB &= ~__SCL__;
    uint32_t Timeout = 0;
    volatile uint8_t ___PINx___;
    do {
      ___PINx___ = PINB;
    } while(!(___PINx___ & __SCL__) && --Timeout);                      
  }
  #define _SCL_L_()     (DDRB |=  __SCL__)  
  #define _SDA_H_()     (DDRB &= ~__SDA__)  
  #define _SDA_L_()     (DDRB |=  __SDA__)
  #define _IN_SDA_()    (PINB & __SDA__)          
  void _INIT_IO_(void)   
  {
    DDRB  |= __SYNC__;
    PORTB |= __SYNC__;     
    DDRB  &= ~(__SCL__ | __SDA__);
    PORTB &= ~(__SCL__ | __SDA__);      
  }
#elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)

  #define   __SYNC__    0x10
  #define   __SDA__     0x40
  #define   __SCL__     0x20
  
  #define _SYNC_H_()    (PORTJ |= __SYNC__)  
  #define _SYNC_L_()    (PORTJ &= ~__SYNC__) 
  void _SCL_H_(void)     {
    DDRJ &= ~__SCL__;
    uint32_t Timeout = 0;
    volatile uint8_t ___PINx___;
    do {
      ___PINx___ = PINJ;
    } while(!(___PINx___ & __SCL__) && --Timeout);
  } 
  #define _SCL_L_()     (DDRJ |=  __SCL__)
  #define _SDA_H_()     (DDRJ &= ~__SDA__) 
  #define _SDA_L_()     (DDRJ |=  __SDA__)
  #define _IN_SDA_()    (PINJ & __SDA__)  
  void _INIT_IO_(void)  
  {
    DDRJ  |= __SYNC__;
    PORTJ |= __SYNC__;      
    DDRJ  &= ~(__SDA__ | __SCL__);
    PORTJ &= ~(__SDA__ | __SCL__);   
  }   
#else
  #error your device is not supported 
  #define _SYNC_H_()    
  #define _SYNC_L_()    
  #define _SCL_H_()
  #define _SCL_L_()     
  #define _SDA_H_()     
  #define _SDA_L_()  
  #define _IN_SDA_()  1 
  #define _INIT_IO_()       
#endif
  
static void I2CStart(void) 
{
    _SCL_H_();        
    delayMicroseconds(kinnoDelay*2);
    _SDA_L_();
    delayMicroseconds(kinnoDelay*2); 
    _SCL_L_();
    delayMicroseconds(kinnoDelay*2); 
}

static void I2CStop(void)
{   
    _SDA_L_();
    delayMicroseconds(kinnoDelay*2);
    _SCL_H_();         
    delayMicroseconds(kinnoDelay*2); 
    _SDA_H_();  
    delayMicroseconds(kinnoDelay*2);     
}
static void I2CSendData(uint8_t Data) 
{ 
    for(int ii = 0 ; ii < 8 ; ) {
       if(Data & 0x80)  _SDA_H_();
       else             _SDA_L_();
       Data <<= 1;        
       ii++;     
       _SCL_H_();  
       delayMicroseconds(kinnoDelay);     
       _SCL_L_();
       delayMicroseconds(kinnoDelay); 
    }  
}  
static uint8_t I2CReceiveData(void)
{ 
    uint8_t Data; 
    _SDA_H_();                   
    for(int ii = 0 ; ii < 8 ; ii++) {                                                              
       _SCL_H_();  
       Data <<= 1;  
       delayMicroseconds(kinnoDelay);
       if(_IN_SDA_())  Data |= 1;                    
       _SCL_L_(); 
       delayMicroseconds(kinnoDelay);
    }          
    return Data;
} 
void ResetModule(void)
{
    _SYNC_L_();
    delayMicroseconds(20);
    _SYNC_H_(); 
    delayMicroseconds(200);
    for(int u = 0 ; u < 4 ; u++) {   
      I2CStart();
      delayMicroseconds(20);
      I2CStop();
      delayMicroseconds(20); 
    }
}
uint8_t CheckModule(void)
{
    return __i2cModuleStatus__;     
}
static void SetAck(unsigned char Ack)
{
    if(Ack == 1)  _SDA_H_();  
    else          _SDA_L_();  
    _SCL_H_(); 
    delayMicroseconds(kinnoDelay);  
    _SCL_L_(); 
    delayMicroseconds(kinnoDelay);
}

static uint8_t CheckAck(void)
{
    uint8_t Data;
    _SDA_H_(); 
    _SCL_H_();        
    delayMicroseconds(kinnoDelay);
    Data = _IN_SDA_();             
    _SCL_L_(); 
    delayMicroseconds(kinnoDelay);
    return Data; 
}
void InitArmCommander(void)
{   
  if(!__initI2C__)
  {
    __initI2C__ = 1;
               
    _INIT_IO_();
    ResetModule();                                
  }
}

void __i2cWriteBuffer(uint8_t* pBuffer, uint8_t I2C_DEV_ADDR, uint8_t NumByteToWrite)
{
  uint8_t i, Ack;	
  uint8_t *ptr;
  uint8_t CheckSum;      
  uint16_t Timeout;
  
  if(__i2cBusy__) return;
  __i2cModuleStatus__ = 0;     
  __i2cBusy__ = 1;    

  *(pBuffer+1) = 255 - *pBuffer - I2C_DEV_ADDR - I2C_DEV_ADDR;
  if(NumByteToWrite >= 5) {
      i = NumByteToWrite - 4;
      ptr = pBuffer + 2;
      CheckSum = 255;
      do {
        CheckSum -= *ptr++;  
      }while(--i);
      *ptr = CheckSum;   
  } 
  Timeout = __kInnoTimeOut;
  do  {
    I2CStart();   
    I2CSendData(I2C_DEV_ADDR + I2C_DEV_ADDR);
    Ack = CheckAck();  
    if(!Ack) {
        __i2cModuleStatus__ = 0;
        ptr = pBuffer;
        for(i = 0 ; (i < NumByteToWrite) ; i++)
        {
            I2CSendData(*ptr++); 
            CheckAck();                        
        }
    }
    else    __i2cModuleStatus__ = 2;  
    I2CStop();   
  } while(Ack && --Timeout);
  __i2cBusy__ = 0;
  return;  
}

uint32_t __i2cReadBuffer(uint8_t* pBuffer, uint8_t I2C_DEV_ADDR, uint8_t NumByteToWrite, uint8_t *NumByteToRead)
{  
  uint8_t* ptr;    
  uint8_t Ack, CheckSum;
  uint8_t i, SkipWrite = 0;
  uint16_t Timeout;
  
  if(__i2cBusy__) return 0;
  __i2cModuleStatus__ = 0;     
  __i2cBusy__ = 1;  

  *(pBuffer+1) = 255 - *pBuffer  - I2C_DEV_ADDR  - I2C_DEV_ADDR; 
  if(NumByteToWrite >= 5)  {
    i = NumByteToWrite - 4;
    CheckSum = 255;
    ptr = pBuffer + 2;
    do {
        CheckSum -= *ptr++;
    }while(--i);
    *ptr = CheckSum;     
  }

  Timeout = __kInnoTimeOut;
  while(--Timeout)  {
    if(!SkipWrite) {
        I2CStart();  
        I2CSendData(I2C_DEV_ADDR + I2C_DEV_ADDR);
        Ack = CheckAck();    
        if(!Ack)  {
            __i2cModuleStatus__ = 0;
            ptr = pBuffer;                     
            for(i = 0 ; (i < NumByteToWrite)  ; i++) {
                I2CSendData(*ptr++);
                CheckAck();                       
            }
        }
        else __i2cModuleStatus__ = 2;
        I2CStop(); 
        if(Ack != 0) continue;       
    }
    delayMicroseconds(4*kinnoDelay);
    SkipWrite = 1;

    I2CStart();  
    I2CSendData(I2C_DEV_ADDR + I2C_DEV_ADDR + 1);
    Ack = CheckAck();   
    if(!Ack) {
        __i2cModuleStatus__ = 0;
        ptr = pBuffer;
        for(i = *NumByteToRead ; i ; i--) {
            *ptr++ = I2CReceiveData(); 
            SetAck(i);             
        }
    }
    else __i2cModuleStatus__ = 3;

    I2CStop();    
    if(!Ack) break; 
  } 
  __i2cBusy__ = 0;  
  if(!Timeout)   return 1;

  CheckSum = 255 - I2C_DEV_ADDR;
  i = *NumByteToRead; 
  ptr = pBuffer;      
  do {
    CheckSum -= *ptr++;
  }while(--i);

  if(CheckSum) {
    __i2cModuleStatus__ = 2;
    return 1;
  }
  return 0;
}

