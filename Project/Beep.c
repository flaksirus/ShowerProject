/**
  ******************************************************************************
  * @file     Beep.c
  * @author   Ruslan Khasanbaev
  * @version  V1.0.0
  * @date     19-Mart-2016
  * @brief    Main of Beep module Service Routines.
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
#include "Beep.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Beep_ConfigurationInfo Beep_Config;
//Beep_State_struct Beep_State;
Beep_State_struct Beep_State;
/* Private function prototypes -----------------------------------------------*/
void Beep_On(void);
void Beep_Off(void);
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Beep_Init(Beep_ConfigurationInfo config)
{
  Beep_State.State = BEEP_OFF;
  Beep_Config = config;
  /* Initialize I/Os in Output Mode */
  GPIO_Init(Beep_Config.Beep_Port, Beep_Config.Beep_Pin, GPIO_MODE_OUT_PP_LOW_FAST); //FAN output
}

void Beep_Shutdown(void)
{
  Beep_State.State = BEEP_OFF;
  Beep_Off();
}

void Beep_DoBeep(void)
{
  Beep_State.State = BEEP_IDLE;
}

void Beep_DoBuzz(void)
{
  //Beep_State = TRUE;
  //GPIO_WriteHigh(Beep_Config.Beep_Port, Beep_Config.Beep_Pin);
}

void Beep_On(void)
{
  GPIO_WriteHigh(Beep_Config.Beep_Port, Beep_Config.Beep_Pin);
}

void Beep_Off(void)
{
  GPIO_WriteLow(Beep_Config.Beep_Port, Beep_Config.Beep_Pin);
}

void Beep_Toggle(void)
{  
  if(Beep_State.State == TRUE)
    Beep_Off();
  else 
    Beep_On();
}

void Beep_Timer(void)
{  
  if(Beep_State.State == BEEP_IDLE)
  {
    Beep_State.State = BEEP_BEEP;
    Beep_State.TicksToOff = BeepTick;
    Beep_On();
  }
  else if(Beep_State.State == BEEP_BEEP && Beep_State.TicksToOff-- == 0)
  {
    Beep_State.State = BEEP_OFF;
    Beep_Off();
  }
}
