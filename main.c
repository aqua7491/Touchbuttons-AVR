#define F_CPU 8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "touchButton.h"


int main(void)
{
	DDRD = 0xFF;			//��������� ����� �� �����������
	PORTD = 0b00000000;
	PORTD |= (1<<(PORTD0));	//��������� LED ��� ��� ��������
	_delay_ms(100);
	PORTD &= ~(1<<(PORTD0));

	DDRB=0x00;
	Calibration();		//���������� ������

	while (1)
	{
		TOUCH_CompareKey();
		if(Button_One_Pressed())
		{
			PORTD |= (1<<(PORTD0));			//�������� ���������
			_delay_ms(100);
		}
		else if(Button_Two_Pressed())
		{
			PORTD |= (1<<(PORTD0));
			_delay_ms(100);					//�������� ���������
		}
		else
		{
			PORTD &= ~(1<<(PORTD0));
		}
	}
}
