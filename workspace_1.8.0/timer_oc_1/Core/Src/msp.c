/*
 * msp.c
 *
 *  Created on: 02-Jun-2018
 *      Author: kiran
 */


#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

void HAL_MspInit(void)
{
 //Here will do low level processor specific inits.
	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exceptions

	//3. configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
}
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2ch1_gpio;
	// 1.enable the clock for timer 2
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();


	//2. Configures gpios to behave as channel 1,2,3,4
	//PA0 --> TIM2_CH1
	//PA1 --> TIM2_CH2
	//PA10 --> TIM2_CH3
	//PA2 --> TIM2_CH4

	tim2ch1_gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Pull = GPIO_NOPULL;
	tim2ch1_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);

	tim2ch1_gpio.Pin = GPIO_PIN_2 | GPIO_PIN_10;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Pull = GPIO_NOPULL;
	tim2ch1_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB, &tim2ch1_gpio);


	//NVID setting
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);




}



