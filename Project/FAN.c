/**
  ******************************************************************************
  * @file     FAN.c
  * @author   Ruslan Khasanbaev
  * @version  V1.0.0
  * @date     19-Mart-2016
  * @brief    Main of FAN module Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "FAN.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FAN_ConfigurationInfo FAN_Config;
bool FAN_State;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void FAN_Init(FAN_ConfigurationInfo config)
{
  FAN_State = FALSE;
  FAN_Config = config;
  /* Initialize I/Os in Output Mode */
  GPIO_Init(FAN_Config.FAN_Port, FAN_Config.FAN_Pin, GPIO_MODE_OUT_PP_LOW_FAST); //FAN output
  GPIO_Init(FAN_Config.Led_Port, FAN_Config.Led_Pin, GPIO_MODE_OUT_PP_LOW_FAST); //FAN indicator
}

void FAN_Shutdown(void)
{
  FAN_Off();
}

void FAN_On(void)
{
  FAN_State = TRUE;
  GPIO_WriteHigh(FAN_Config.FAN_Port, FAN_Config.FAN_Pin);
  GPIO_WriteHigh(FAN_Config.Led_Port, FAN_Config.Led_Pin);
}

void FAN_Off(void)
{
  FAN_State = FALSE;
  GPIO_WriteLow(FAN_Config.FAN_Port, FAN_Config.FAN_Pin);
  GPIO_WriteLow(FAN_Config.Led_Port, FAN_Config.Led_Pin);
}

void FAN_Toggle(void)
{  
  if(FAN_State == TRUE)
    FAN_Off();
  else 
    FAN_On();
}

void FAN_Timer(void)
{
}
