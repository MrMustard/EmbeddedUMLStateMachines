/*
 * led.c
 *
 *  Created on: May 19, 2023
 *      Author: el_gl
 */


#include "led.h"



//turn on the led
void led_on(uint8_t led_number)
{
	switch(led_number)
	{
	case led_verde:
		HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
		break;
	case led_amarillo:
		HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_SET);
		break;
	case  led_rojo:
		HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
		break;
	case led_status:

		HAL_GPIO_WritePin(led_status_GPIO_Port, led_status_Pin, GPIO_PIN_SET);
		break;

	default:
		HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_status_GPIO_Port, led_status_Pin, GPIO_PIN_RESET);

		break;

	}
}
//turn off led
void led_off(uint8_t led_number)
{
	switch(led_number)
	{
	case led_verde:
		HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);
		break;
	case led_amarillo:
		HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_RESET);
		break;
	case  led_rojo:
		HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
		break;
	case led_status:

		HAL_GPIO_WritePin(led_status_GPIO_Port, led_status_Pin, GPIO_PIN_RESET);
		break;

	default:
		HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led_status_GPIO_Port, led_status_Pin, GPIO_PIN_RESET);

		break;

	}
}
//turn on all leds
void led_all_on()
{
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);



}
//turn off all leds
void led_all_off()
{

	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_yellow_GPIO_Port, led_yellow_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
}



//funcion para 5 botones
//funcion para leer los botones



