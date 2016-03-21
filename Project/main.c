/**
  ******************************************************************************
  * @file    GPIO_Toggle\main.c
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief   This file contains the main function for GPIO Toggle example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8_tsl_api.h"
#include "FAN.h"
#include "Light.h"
#include "Beep.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define POWER_LED_GPIO_PORT  (GPIOC)
#define POWER_LED_GPIO_PINS  (GPIO_PIN_4)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
bool PowerState;
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
void ExtraCode_Init(void);
void ExtraCode_StateMachine(void);
static void CLK_Config(void);

void ModulesInit(void);

void TouchPower(void);
void TouchLight(void);
void TouchFAN(void);
void TouchMusic(void);
void TouchVolumeUp(void);
void TouchVolumeDown(void);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{  
  /* Clock configuration -----------------------------------------*/
  CLK_Config();    
  
  /* Initialize Touch Sensing Library */
  TSL_Init();
  ExtraCode_Init();
  
  PowerState = FALSE;
  ModulesInit();

  while (1)
  {
    ExtraCode_StateMachine();	
    TSL_Action();    
  }

}

void ExtraCode_Init(void)
{  
#if NUMBER_OF_SINGLE_CHANNEL_KEYS > 0
  for (u8 i = 0; i < NUMBER_OF_SINGLE_CHANNEL_KEYS; i++)
  {
    sSCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sSCKeyInfo[i].Setting.b.ENABLED = 1;
    sSCKeyInfo[i].DxSGroup = 1 << i; /* 0x00 = DxS disabled, other values = DxS enabled */
  }
#endif
  
  enableInterrupts();
}

/**
  ******************************************************************************
  * @brief Example of LED switching using touch sensing keys
  * KEY1: LED1 toggles when the key is pressed
  * KEY2: LED1 ON if key is pressed, LED1 OFF if key is released
  * KEY3: LED1 ON then OFF after a delay
  * All KEYs: LED2 toggles continuously / LED2 is OFF 
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void ExtraCode_StateMachine(void)	{

  if ((TSL_GlobalSetting.b.CHANGED) && (TSLState == TSL_IDLE_STATE))
  {
    TSL_GlobalSetting.b.CHANGED = 0;
    
#if NUMBER_OF_SINGLE_CHANNEL_KEYS > 0
    for (u8 i = 0; i < NUMBER_OF_SINGLE_CHANNEL_KEYS; i++)
    {
      if(sSCKeyInfo[i].Setting.b.ERROR)
        TSL_Init(); //Detect error and restart TSL
      if(sSCKeyInfo[i].Setting.b.DETECTED)
      {
        if(i == 5)
        {
          TouchPower();
        }
        if(PowerState == TRUE)          
        {
          switch(i)
          {
          case 0:
            TouchFAN();
            break;
          case 1:
            TouchLight();
            break;
          case 2:
            TouchMusic();
            break;
          case 3:
            TouchVolumeUp();
            break;
          case 4:
            TouchVolumeDown();
            break;
          default:
            break;          
          }
        }
      }
    }
#endif
  }    
  
}

/**
  * @brief  Configure system clock to run at Maximum clock speed and output the 
  *         system clock on CCO pin
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
    CLK_DeInit();

    /* Configure the Fcpu to DIV1*/
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    
    /* Configure the HSI prescaler to the optimal value */
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
        
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}


void  ModulesInit(void)
{
  GPIO_Init(POWER_LED_GPIO_PORT, POWER_LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST); 
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST); 
  
  FAN_ConfigurationInfo fan_conf;
  fan_conf.FAN_Port = GPIOD;
  fan_conf.FAN_Pin = GPIO_PIN_6;
  fan_conf.Led_Port = GPIOD;
  fan_conf.Led_Pin = GPIO_PIN_6;
  FAN_Init(fan_conf);
  
  Light_ConfigurationInfo light_config;
  light_config.Light_Port = GPIOD;
  light_config.Light_Pin = GPIO_PIN_3;
  Light_Init(light_config);
  
  Beep_ConfigurationInfo beep_config;
  beep_config.Beep_Port = GPIOD;
  beep_config.Beep_Pin = GPIO_PIN_2;
  Beep_Init(beep_config);
  
}

void PowerSwitch(void)
{
  if(PowerState == TRUE)
  {
    PowerState = FALSE;
    GPIO_WriteLow(POWER_LED_GPIO_PORT, POWER_LED_GPIO_PINS);
  }
  else 
  {
    PowerState = TRUE;
    GPIO_WriteHigh(POWER_LED_GPIO_PORT, POWER_LED_GPIO_PINS);
  }
}

/**
  * @brief  Power touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchPower(void)
{
  Beep_DoBeep();
  PowerSwitch();
  if(PowerState == FALSE)
  {
    //throw event to other modules
    FAN_Shutdown();
    Light_Shutdown();
  }
}

/**
  * @brief  FAN touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchFAN(void)
{
    Beep_DoBeep();
  if(PowerState == TRUE)
  {
    FAN_Toggle();
  }
}

/**
  * @brief  Light touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchLight(void)
{  
    Beep_DoBeep();
  if(PowerState == TRUE)
  {
    Light_Toggle();
  }
}

/**
  * @brief  Music touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchMusic(void)
{
    Beep_DoBeep();
  if(PowerState == TRUE)
  {
    //DoSmth
  }
}

/**
  * @brief  VolumeUp touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchVolumeUp(void)
{
    Beep_DoBeep();
  if(PowerState == TRUE)
  {
    //DoSmth
  }
}

/**
  * @brief  VolumeDown touch sensor touch event 
  * @param  None
  * @retval None
  */
void TouchVolumeDown(void)
{
    Beep_DoBeep();
  if(PowerState == TRUE)
  {
    //DoSmth
  }
}

void USER_TickTimerCallback(void)
{
  //Throw to Modules - 0.05 sec
  Beep_Timer();
  
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
