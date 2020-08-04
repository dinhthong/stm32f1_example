/*
On-board STM32F103C8T6 LED toggle
*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
void Delay(__IO uint32_t nTime);
static __IO uint32_t TimingDelay;
GPIO_InitTypeDef GPIO_InitStructure;
int main(void)
{
//  SysTick_Config(SystemCoreClock/1000000);
	delay_init(72);
//	USART_Configuration();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	// init imu
  while (1)
  {
		//temperature range: -50 to 200
	//	printf("Nhiet do:\n\r aa");
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
	//	MPU6050_Dataanl();
	//	delay_ms(4);
  }
}

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */

