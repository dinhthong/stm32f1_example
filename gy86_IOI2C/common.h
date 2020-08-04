/******************** (C) COPYRIGHT 2015 DUT ********************************

**********************************************************************************/


#ifndef __common_H
#define __common_H
#include "delay.h"
#include <stdio.h>
#include "IOI2C.h"
#include "MPU6050.h"
#include "HMC5883L.h"
//#include "IOI2C.h"

//#include "MPU6050.h"
//#include "HMC5883L.h"
//#include "ms5611.h"
//#include "IMU.h"
////#include "Kalman.h"
//#include "copter_config.h"
//#include "motor.h"
//#include "pid.h"
//#include "stm32f4xx_it.h"
//#include "px4flow.h"
//#include "copter_utils.h"
//#include "adns3080.h"

// define this to use hcsr 04 for altitude hold and px4 altitude compensation, other it will use default px4flow sonar
// uncomment this to use sonar px4flow

//#define USE_HCSR04

//#define rc_elev channels[0]
//#define rc_aile channels[1]
//#define rc_thro channels[2]
//#define rc_rudd channels[3]
//#define rc_gear channels[4]
//#define rc_mix channels[5]
//#define rc_aux channels[6]


//#define RC_deadband 4
//rate in microsecond
//#define FLOW_RATE 13
//#define HCSR_RATE 60

//#define YAW_ANGLE_PID
//#define PX4FLOW_SPL

//#define GET_MS5611
//#define APPLY_RC_DEADBAND

//#define M_PI  (float)3.1415926535
//	
//#define Motor_MIN 1150
//#define Motor_MAX 1800

//#define IMU_2
//struct px4_i2c_frame
//{
//    uint16_t frame_count;// counts created I2C frames
//    int16_t pixel_flow_x_sum;// accumulated x flow in pixels*10 since last I2C frame
//    int16_t pixel_flow_y_sum;// accumulated y flow in pixels*10 since last I2C frame
//    int16_t flow_comp_m_x;// x velocity*1000 in meters / timestep
//    int16_t flow_comp_m_y;// y velocity*1000 in meters / timestep
//    int16_t qual;// Optical flow quality / confidence 0: bad, 255: maximum quality
//    int16_t gyro_x_rate; //gyro x rate
//    int16_t gyro_y_rate; //gyro y rate
//    int16_t gyro_z_rate; //gyro z rate
//    uint8_t gyro_range; // gyro range
//    uint8_t sonar_timestamp;// timestep in milliseconds between I2C frames
//    int16_t ground_distance;// Ground distance in meters*1000. Positive value: distance known. Negative value: Unknown distance
//} ;

//struct px4_i2c_integral_frame
//{
//    uint16_t frame_count_since_last_readout;//number of flow measurements since last I2C readout [#frames]
//    int16_t pixel_flow_x_integral;//accumulated flow in radians*10000 around x axis since last I2C readout [rad*10000]
//    int16_t pixel_flow_y_integral;//accumulated flow in radians*10000 around y axis since last I2C readout [rad*10000]
//    int16_t gyro_x_rate_integral;//accumulated gyro x rates in radians*10000 since last I2C readout [rad*10000] 
//    int16_t gyro_y_rate_integral;//accumulated gyro y rates in radians*10000 since last I2C readout [rad*10000] 
//    int16_t gyro_z_rate_integral;//accumulated gyro z rates in radians*10000 since last I2C readout [rad*10000] 
//    uint32_t integration_timespan;//accumulation timespan in microseconds since last I2C readout [microseconds]
//    uint32_t sonar_timestamp;// time since last sonar update [microseconds]
//    int16_t ground_distance;// Ground distance in meters*1000 [meters*1000]
//    int16_t gyro_temperature;// Temperature * 100 in centi-degrees Celsius [degcelsius*100]
//    uint8_t quality;// averaged quality of accumulated flow values [0:bad quality;255: max quality]
//};

//typedef union
//{
//	float  value;
//	unsigned char byte[4];
//} f_bytes;

//整数 联合体
//typedef union
//{
//	int16_t  value;
//	unsigned char byte[2];
//} i_bytes;

//typedef struct {
//    float p,i,d;
//} pid_para_t;

//typedef struct {
//    float pout,iout,dout;
//} pid_output_t;

#endif

//------------------End of File----------------------------



