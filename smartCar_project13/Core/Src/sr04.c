#include "sr04.h"
#include "gpio.h"
#include "tim.h"

void TIM2_Delay_us(uint16_t n_us)
{
    /* 使能定时器2计数 */
    __HAL_TIM_ENABLE(&htim2);
    __HAL_TIM_SetCounter(&htim2, 0);
    while(__HAL_TIM_GetCounter(&htim2) < ((1 * n_us)-1) );
    /* 关闭定时器2计数 */
    __HAL_TIM_DISABLE(&htim2);
}

double get_distance(void)
{
		int cnt=0;
		//1. Trig ，给Trig端口至少10us的高电平
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//拉高
		TIM2_Delay_us(20);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);//拉低

		//2. echo由低电平跳转到高电平，表示开始发送波
		//波发出去的那一下，开始启动定时器
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET);//等待输入电平拉高
		HAL_TIM_Base_Start(&htim2);
		__HAL_TIM_SetCounter(&htim2,0);

		//3. 由高电平跳转回低电平，表示波回来了
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET);//等待输入电平变低
		//波回来的那一下，我们开始停止定时器
		HAL_TIM_Base_Stop(&htim2);

		//4. 计算出中间经过多少时间
		cnt = __HAL_TIM_GetCounter(&htim2);

		//5. 距离 = 速度 （340m/s）* 时间/2（计数1次表示1us）
		return (cnt*340/2*0.000001*100); //单位：cm
}
