/*
On-board STM32F103C8T6 LED toggle
*/
#include "main.h"
//#include "common.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
//void Delay(__IO uint32_t nTime);
//static __IO uint32_t TimingDelay;
//void USART_Configuration(void);
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

	extern uint32_t systick_cnt;

int x;
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
	
	// interrupt
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
//	EXTI_InitTypeDef  EXTI_InitStructure;
//	   EXTI_InitStructure.EXTI_Line = EXTI_Line4 ;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//		
//	NVIC_InitTypeDef NVIC_InitStructure;
//	//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStructure.NVIC_IRQChannel= EXTI4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	// init imu
//	
//	GPIO_InitTypeDef  GPIO_InitStructure; 
// 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //Ê¹ÄÜGPIOBÊ±ÖÓ
//  
//	GPIO_InitStructure.GPIO_Pin =  SCL_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//	InitMPU6050();
 // GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


  /* TIM3 channel 2 pin (PA.07) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 TIM_TimeBaseInitTypeDef timer_base;
	  TIM_TimeBaseStructInit(&timer_base);
	  timer_base.TIM_Prescaler = 72-1;
	  TIM_TimeBaseInit(TIM3, &timer_base);
		
	 NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
// TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
//  
// /* Select the TIM3 Input Trigger: TI2FP2 */
//  TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);

//  /* Select the slave Mode: Reset Mode */
//  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
//  TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);



  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
	  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);
	  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  while (1)
  {
		//temperature range: -50 to 200
	//	printf("Nhiet do:\n\r aa");
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		_delay_us(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		_delay_us(500);
//		x+=2;
	//	MPU6050_Dataanl();
	//	delay_ms(4);
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
			    a = micros();
			}
			else {
				ch0 = micros() - a;
			}
			interrupt_cnt++;
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
}
