/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include "stm32_eval.h"
#include <stdio.h>

GPIO_InitTypeDef GPIO_InitStructure;
void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);
//#ifdef USE_STM32100B_EVAL
// #include "stm32100b_eval_lcd.h"
//#elif defined USE_STM3210B_EVAL
// #include "stm3210b_eval_lcd.h"
//#elif defined USE_STM3210E_EVAL
// #include "stm3210e_eval_lcd.h" 
//#elif defined USE_STM3210C_EVAL
// #include "stm3210c_eval_lcd.h"
//#elif defined USE_STM32100E_EVAL
// #include "stm32100e_eval_lcd.h"
//#endif

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#ifdef USE_STM32100B_EVAL
//  #define MESSAGE1   "STM32 MD Value Line " 
//  #define MESSAGE2   " Device running on  " 
//  #define MESSAGE3   "  STM32100B-EVAL    " 
//#elif defined (USE_STM3210B_EVAL)
//  #define MESSAGE1   "STM32 Medium Density" 
//  #define MESSAGE2   " Device running on  " 
//  #define MESSAGE3   "   STM3210B-EVAL    " 
//#elif defined (STM32F10X_XL) && defined (USE_STM3210E_EVAL)
//  #define MESSAGE1   "  STM32 XL Density  " 
//  #define MESSAGE2   " Device running on  " 
//  #define MESSAGE3   "   STM3210E-EVAL    "
//#elif defined (USE_STM3210E_EVAL)
//  #define MESSAGE1   " STM32 High Density " 
//  #define MESSAGE2   " Device running on  " 
//  #define MESSAGE3   "   STM3210E-EVAL    " 
//#elif defined (USE_STM3210C_EVAL)
//  #define MESSAGE1   " STM32 Connectivity " 
//  #define MESSAGE2   " Line Device running" 
//  #define MESSAGE3   " on STM3210C-EVAL   "
//#elif defined (USE_STM32100E_EVAL)
//  #define MESSAGE1   "STM32 HD Value Line " 
//  #define MESSAGE2   " Device running on  " 
//  #define MESSAGE3   "  STM32100E-EVAL    "   
//#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 USART_InitTypeDef USART_InitStructure;

/* Private function prototypes -----------------------------------------------*/
//#ifdef __GNUC__
///* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//   set to 'Yes') calls __io_putchar() */
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
uint16_t cnt;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

  /* Initialize LEDs, Key Button, LCD and COM port(USART) available on
     STM3210X-EVAL board ******************************************************/
		//SystemInit();
GPIO_Configuration();
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Add your application code here
     */

  /* Infinite loop */
  while (1)
  {
		    GPIO_SetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_13);                
    Delay(0xFFFFF);
		cnt++;
    GPIO_ResetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_13);
    Delay(0xFFFFF);
  }
}

void GPIO_Configuration(void)
{
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;            //D1  D2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
//PUTCHAR_PROTOTYPE
//{
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(EVAL_COM1, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
//}
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
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


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
