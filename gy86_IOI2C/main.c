/*
On-board STM32F103C8T6 LED toggle
*/
#include "stm32f10x.h"
#include "common.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
void Delay(__IO uint32_t nTime);
static __IO uint32_t TimingDelay;
void USART_Configuration(void);
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
int16_t MPU6050data[6];
float HMC5883data[3];
float gyro_x, gyro_y, gyro_z;
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
	IIC_Init();
	// init imu
	
//	GPIO_InitTypeDef  GPIO_InitStructure; 
// // i2c1 is on APB1 bus
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟
//  
//	GPIO_InitStructure.GPIO_Pin =  SCL_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);  //使能GPIOB时钟
//	I2C_InitTypeDef I2C_InitStruct;
//	I2C_InitStruct.I2C_ClockSpeed = 100000;
//    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
//    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
//    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
//    I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
//    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//    I2C_Init(I2C1, &I2C_InitStruct);
//    I2C_Cmd(I2C1, ENABLE);
////	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_I2C1);
////  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_I2C1);
//	 MPU6050_Initialize(); 
//	InitMPU6050();
  MPU6050_initialize();
	HMC5883L_SetUp();
  while (1)
  {
	//	MPU6050_GetRawAccelTempGyro(MPU6050data);
		MPU6050_getMotion6(&MPU6050data[0], &MPU6050data[1], &MPU6050data[2], &MPU6050data[3], &MPU6050data[4], &MPU6050data[5]);
		HMC58X3_mgetValues(&HMC5883data[0]);	//
		gyro_x = MPU6050data[4]/ 65.5;
		gyro_y = MPU6050data[5]/ 65.5;
		//temperature range: -50 to 200
	//	printf("Nhiet do:\n\r aa");
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	//	delay_ms(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	//	delay_ms(1000);
//		MPU6050_Dataanl();
		delay_ms(4);
  }
}
void USART_Configuration()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
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

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
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

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
