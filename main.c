#define F_CPU 8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "touchButton.h"


int main(void)
{
	DDRD = 0xFF;			//Включение порта со светодиодом
	PORTD = 0b00000000;
	PORTD |= (1<<(PORTD0));	//Зажигание LED для его проверки
	_delay_ms(100);
	PORTD &= ~(1<<(PORTD0));

	DDRB=0x00;
	Calibration();		//Калибровка кнопок

	while (1)
	{
		TOUCH_CompareKey();
		if(Button_One_Pressed())
		{
			PORTD |= (1<<(PORTD0));			//Зажигаем светодиод
			_delay_ms(100);
		}
		else if(Button_Two_Pressed())
		{
			PORTD |= (1<<(PORTD0));
			_delay_ms(100);					//Зажигаем светодиод
		}
		else
		{
			PORTD &= ~(1<<(PORTD0));
		}
	}
}
