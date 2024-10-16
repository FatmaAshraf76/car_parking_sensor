#include "common_macros.h" /* For GET_BIT Macro */
#include "leds.h"
#include "gpio.h"
#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initializes all Leds (red, green, blue) pins direction.
 * Turn off all the Leds.
 */
void LEDS_init(void)
{
    GPIO_setupPinDirection(RED_LED_PORT_ID , RED_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LED_OFF);
	GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LED_OFF);
	GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LED_OFF);
}

/*
 * Description :
 * Function responsible for Turns on the specified LED.
 */
void LED_on(LED_ID id)
{
	if(id==RED)
	{
		GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LED_ON);
	}
	else if(id==GREEN)
	{
		GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LED_ON);
	}
	else if(id==BLUE)
	{
 		GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LED_ON);
	}
}

/*
 * Description :
 * Function responsible for  Turns off the specified LED.
 */
void LED_off(LED_ID id)
{
	if(id==RED)
    {
		GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LED_OFF);
	}
	else if(id==GREEN)
    {
		GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LED_OFF);
	}
	else if(id==BLUE)
	{
 		GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LED_OFF);
	}
}
