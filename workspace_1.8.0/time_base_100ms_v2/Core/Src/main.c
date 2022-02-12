/*
 * main.c
 *
 *  Created on: 02-Jun-2018
 *      Author: kiran
 */
#include "main.h"

#include <string.h>
#include "stm32f4xx_hal.h"
#include "main.h"

void SystemClockConfig(void);

void Error_handler(void);
void TIMER6_Init();
void GPIO_Init();



TIM_HandleTypeDef htimer6;


int main(void)
{
	HAL_Init();
	SystemClockConfig();
	TIMER6_Init();
	GPIO_Init();

	//Lets start timer

	HAL_TIM_Base_Start(&htimer6);

	while(1)
	{
		while(!(TIM6->SR & TIM_SR_UIF))
		{
			TIM6->SR = 0;
			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		}
	}

	while(1);

	return 0;
}


void SystemClockConfig(void)
{


}

void Error_handler(void)
{
	while(1);
}

void TIMER6_Init()
{
	htimer6.Instance = TIM6;
	//htimer6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 63999;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK)
	{
		Error_handler();
	}
}

void GPIO_Init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);

}
