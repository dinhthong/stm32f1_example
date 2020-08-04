#include "MPU6050.h"
u8				    mpu6050_buffer[14];					//iic读取后存放数据 	
int16_t ax, ay, az, gx, gy, gz;
void InitMPU6050(void)
{
	Single_Write(MPU6050_DEFAULT_ADDRESS<<1, MPU6050_RA_PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(MPU6050_DEFAULT_ADDRESS<<1, MPU6050_RA_SMPLRT_DIV, 0x07);
	Single_Write(MPU6050_DEFAULT_ADDRESS<<1, 0x1A, 0x03);
	Single_Write(MPU6050_DEFAULT_ADDRESS<<1, MPU6050_RA_GYRO_CONFIG, 0x10);
	Single_Write(MPU6050_DEFAULT_ADDRESS<<1, MPU6050_RA_ACCEL_CONFIG, 0x09);//+-4G
//	ACC_OFFSET.X=-20;
//	ACC_OFFSET.Y=18;
//	ACC_OFFSET.Z=34;
//	GYRO_OFFSET.X=-38.9979;
//	GYRO_OFFSET.Y=-30.6081;
//	GYRO_OFFSET.Z=-31.9918;
}

//**************************实现函数********************************************
//读取MPU6050数据
//******************************************************************************
void MPU6050_Read(void)
{
	mpu6050_buffer[0]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_XOUT_H);
	mpu6050_buffer[1]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_XOUT_L); 
	mpu6050_buffer[2]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_YOUT_H);
	mpu6050_buffer[3]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_YOUT_L);
	mpu6050_buffer[4]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_ZOUT_H);
	mpu6050_buffer[5]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, ACCEL_ZOUT_L);
	mpu6050_buffer[8]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_XOUT_H);
	mpu6050_buffer[9]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_XOUT_L);
	mpu6050_buffer[10]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_YOUT_H);
	mpu6050_buffer[11]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_YOUT_L);
	mpu6050_buffer[12]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_ZOUT_H);
	mpu6050_buffer[13]=Single_Read(MPU6050_DEFAULT_ADDRESS<<1, GYRO_ZOUT_L);
	
}
/**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器
*******************************************************************************/
void MPU6050_Dataanl(void)
{
	MPU6050_Read();
	ax=((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]);
	ay=((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]);
	az=((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]);

	gx= ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	gy= ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	gz= ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
}	
