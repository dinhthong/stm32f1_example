/*
On-board STM32F103C8T6 LED toggle
*/
#include "main.h"
//#include "common.h"

//#ifdef __GNUC__
//  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//     set to 'Yes') calls __io_putchar() */
//  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
//void Delay(__IO uint32_t nTime);
//static __IO uint32_t TimingDelay;
//void USART_Configuration(void);
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

	extern uint32_t systick_cnt;

int x;
uint32_t miliii;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  SysTick_Config(SystemCoreClock/1000000);
	GPIO_InitTypeDef  GPIO_InitStructure; 
//	delay_init(72);
//	USART_Configuration();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  /* GPIOA and GPIOB clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


//  /* TIM3 channel 2 pin (PA.07) configuration */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// interrupt

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
	EXTI_InitTypeDef  EXTI_InitStructure;
	   EXTI_InitStructure.EXTI_Line = EXTI_Line4 ;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		
	NVIC_InitTypeDef NVIC_InitStructure;
	//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel= EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  /* Enable the CC2 Interrupt Request */
//  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
//	  /* TIM enable counter */
//  TIM_Cmd(TIM3, ENABLE);
//	  /* Enable the TIM3 global Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
  while (1)
  {
		//temperature range: -50 to 200
	//	printf("Nhiet do:\n\r aa");
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		_delay_ms(200);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		_delay_ms(200);
    miliii = milis();
  }
}


uint32_t micros(void)
{
    float us;
    us = systick_cnt;
    return us;
}

void _delay_us(uint32_t us)
{
    uint32_t now = micros();
    while (micros() - now < us);
}

uint32_t milis(void)
{
    float ms;
    ms = systick_cnt*0.001;
    return ms;
}

void _delay_ms(uint32_t ms)
{
    uint32_t now = milis();
    while (milis() - now < ms);
}
int interrupt_cnt=0;
volatile uint16_t ch0;
volatile uint32_t a;
void EXTI4_IRQHandler(void) {
//	 static 
	 if(EXTI_GetFlagStatus(EXTI_Line4) != RESET)
    {
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)) {
			//check GPIO port
			    a = systick_cnt;
			}
			else {
				ch0 = systick_cnt - a;
			}
		//	interrupt_cnt++;
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
}
