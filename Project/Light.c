/**
  ******************************************************************************
  * @file     Light.c
  * @author   Ruslan Khasanbaev
  * @version  V1.0.0
  * @date     19-Mart-2016
  * @brief    Main of Light module Service Routines.
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
#include "Light.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Light_ConfigurationInfo Light_Config;
bool Light_State;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Light_Init(Light_ConfigurationInfo config)
{
  Light_State = FALSE;
  Light_Config = config;
  /* Initialize I/Os in Output Mode */
  GPIO_Init(Light_Config.Light_Port, Light_Config.Light_Pin, GPIO_MODE_OUT_PP_LOW_FAST); //FAN output
}

void Light_Shutdown(void)
{
  Light_Off();
}

void Light_On(void)
{
  Light_State = TRUE;
  GPIO_WriteHigh(Light_Config.Light_Port, Light_Config.Light_Pin);
}

void Light_Off(void)
{
  Light_State = FALSE;
  GPIO_WriteLow(Light_Config.Light_Port, Light_Config.Light_Pin);
}

void Light_Toggle(void)
{  
  if(Light_State == TRUE)
    Light_Off();
  else 
    Light_On();
}

void Light_Timer(void)
{
}
