#include "lcd.h"
#include "icu.h"
#include "gpio.h"
#include "buzzer.h"
#include "leds.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>

unsigned char prev_distance=0;

void Distance_to_LED_and_Buzzer_Mapping(uint16 distance);
void LCD_display_distance(uint8 distance);

int main(void)
{
	uint8 distance=Ultrasonic_readDistance() ;

	/* Create configuration structure for ICU driver */
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize the Ultrasonic , leds , BUZZER , LCD and ICU driver */
	LCD_init();
	ICU_init(&ICU_Configurations);
	Ultrasonic_init();
	Buzzer_init();
	LEDS_init();

	LCD_moveCursor(0,0);
	LCD_displayString("distance=    cm");


	while(1)
	{
		distance=Ultrasonic_readDistance();
		LCD_display_distance(distance);
		Distance_to_LED_and_Buzzer_Mapping(distance);
		_delay_ms(100);
	}
}


/*
 * Description :
 * Distance to LED and Buzzer Mapping:
 * Distance <= 5 cm: All LEDs are flashing (Red, Green, Blue), Buzzer sounds, LCD shows "Stop."
 * 6 cm <= Distance <= 10 cm: All LEDs ON (Red, Green, Blue), No buzzer.
 * 11 cm <= Distance <= 15 cm: Red and Green LEDs ON, Blue LED OFF.
 * 16 cm <= Distance <= 20 cm: Only Red LED ON, others OFF.
 * Distance > 20 cm: All LEDs OFF, Buzzer OFF.
 *
 */
void Distance_to_LED_and_Buzzer_Mapping(uint16 distance)
{
	if(distance>20)
	{
		LED_off(RED);
		LED_off(GREEN);
		LED_off(BLUE);
		Buzzer_off();
	}
	else if(distance>=16 && distance<=20)
	{
		LED_on(RED);
		LED_off(GREEN);
		LED_off(BLUE);
		Buzzer_off();
	}
	else if(distance>=11 && distance<=15)
	{
		LED_on(RED);
		LED_on(GREEN);
		LED_off(BLUE);
		Buzzer_off();
	}
	else if(distance>=6 && distance<=10)
	{
		LED_on(RED);
		LED_on(GREEN);
		LED_on(BLUE);
		Buzzer_off();
	}
	else if(distance>0 && distance<=5)
	{
		LED_on(RED);
		LED_on(GREEN);
		LED_on(BLUE);
		Buzzer_on();
		_delay_ms(100);
		LED_off(RED);
		LED_off(GREEN);
		LED_off(BLUE);
		Buzzer_off();
		_delay_ms(50);
	}
}

void LCD_display_distance(uint8 distance)
{
	if(prev_distance!=distance)
	{
		LCD_moveCursor(0,9);
		LCD_intgerToString(distance);
	}
	if(distance<100)
	{
		LCD_displayCharacter(' ');
	}
	LCD_moveCursor(1,7);
	if(distance>0 && distance<=5)
	{
		LCD_displayString("STOP!");
	}
	else
	{
		LCD_displayString("     ");
	}

}
