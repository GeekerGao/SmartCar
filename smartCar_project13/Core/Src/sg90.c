#include "sg90.h"
#include "gpio.h"
#include "tim.h"

void initSG90(void)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4); //启动定时器4
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17); //将舵机置为0度
}

void sgMiddle(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17); //将舵机置为90度
}

void sgRight(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 5); //将舵机置为0度
}

void sgLeft(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 25); //将舵机置为180度
}
