/**
  ******************************************************************************
  * @file     Beep.h
  * @author   Ruslan Khasanbaev
  * @version  V1.0.0
  * @date     19-Mart-2016
  * @brief    This file contains the headers of Beep module
  ******************************************************************************
  * @attention
  * 
  *     Permission is hereby granted, free of charge, to any person obtaining
  *     a copy of this software and associated documentation files (the
  *     "Software"), to deal in the Software without restriction, including
  *     without limitation the rights to use, copy, modify, merge, publish,
  *     distribute, sublicense, and/or sell copies of the Software, and to
  *     permit persons to whom the Software is furnished to do so, subject to
  *     the following conditions:
  *     
  *     The above copyright notice and this permission notice shall be included
  *     in all copies or substantial portions of the Software.
  *     
  *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  *     EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  *     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  *     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  *     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  *     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  *     SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BEEP_H
#define __BEEP_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  GPIO_TypeDef* Beep_Port;          /**< Holds the GPIO_Port of pinout to Light */
  GPIO_Pin_TypeDef Beep_Pin;        /**< Holds the pinout mask of Light  */
}
Beep_ConfigurationInfo;

typedef enum
{
  BEEP_OFF          = (u8)0x00,
  BEEP_IDLE         = (u8)0x01,
  BEEP_BEEP         = (u8)0x02,
  //BEEP_BUZZ         = (u8)0x03,
} BEEPState_T;

typedef struct
{
  BEEPState_T State;    
  u8 TicksToOff;
  u8 TicksToOn;
  u8 TicksToShutdown;
}
Beep_State_struct;
/* Exported variables ------------------------------------------------------- */
extern Beep_State_struct Beep_State;
/* Exported constants --------------------------------------------------------*/
#define BeepTick  (20)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Beep_Init(Beep_ConfigurationInfo config);
void Beep_Shutdown(void);
void Beep_DoBeep(void);
void Beep_DoBuzz(void);
void Beep_Timer(void); //500 msec 

#endif /* __BEEP_H */
