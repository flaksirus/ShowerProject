/**
  ******************************************************************************
  * @file     FAN.h
  * @author   Ruslan Khasanbaev
  * @version  V1.0.0
  * @date     19-Mart-2016
  * @brief    This file contains the headers of FAN module
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
#ifndef __FAN_H
#define __FAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  GPIO_TypeDef* FAN_Port;          /**< Holds the GPIO_Port of pinout to FAN */
  GPIO_Pin_TypeDef FAN_Pin;        /**< Holds the pinout mask of FAN  */
  GPIO_TypeDef* Led_Port;          /**< Holds the GPIO_Port of pinout to Led */
  GPIO_Pin_TypeDef Led_Pin;        /**< Holds the pinout mask of Led indicator*/
}
FAN_ConfigurationInfo;
/* Exported variables ------------------------------------------------------- */
extern bool FAN_State;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void FAN_Init(FAN_ConfigurationInfo config);
void FAN_Shutdown(void);
void FAN_On(void);
void FAN_Off(void);
void FAN_Toggle(void);
void FAN_Timer(void);

#endif /* __FAN_H */
