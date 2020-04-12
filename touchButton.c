#include "touchButton.h"


char Used_Pins [] = {BUTTON1, BUTTON2}; //Используемые кнопки
char TouchKey [] = {1, 2}; 				//Коды сенсорных кнопок. Нужно для решения конфликта с кнопкой на нулевом пине



int Charge_Time(char array)
{
	int chargeTimeCount=0;
	char PressedPin = Used_Pins[array];
	DDR |= (1<<PressedPin);									//Пин на выход
	while((TOUCH_PIN & (1<<PressedPin)));
	DDR &=~ (1<<PressedPin);								//Пин на вход
	while(!(TOUCH_PIN & (1<<PressedPin)))  chargeTimeCount++;
	return chargeTimeCount;									//Кол-во тактов при переключении кнопки
}



void Button_Count (int *array)
{
	int channel, count=0, timeCount=5;								// Для повышения точности используется 5 замеров
	
	for (channel = 0; channel < 2; channel++) array[channel] = 0;	//Очистить накопительный буфер
	cli();															//Отключение глобальных прерываний
	do {
		for (channel = 0; channel < 2; channel++) array[channel] += Charge_Time(channel);
	} while (++count < timeCount);									 //Находимся здесь до окончания цикла из timeCount замеров
	sei();															//Отключение глобальных прерываний

	for (channel = 0; channel < 2; channel++) array[channel] /= timeCount;	//Среднее время заряда
}


void Calibration (void)
{
	Button_Count (CalibArray);
}


void TOUCH_CompareKey (void)
{
	unsigned char channel;
	char tempKey=0;
	
	Button_Count (CurrentArray); //Текущие значения времени заряда ёмкости сенсорных кнопок
	
	for (channel = 0; channel < 2; channel++)
	{   //Если кнопка нажата,  её код сохраняется в буфере
		if(CurrentArray[channel] > CalibArray[channel])  //Сравниваем текущее и эталонное значение
		{
			tempKey=TouchKey[channel];
		}
	}
	//Если в буфере содержится код любой нажатой кнопки
	if(tempKey)
	{
		KeyPressed = tempKey;
		return;
	}
	else	KeyPressed=0;
}


char Button_One_Pressed(void)
{
	if (KeyPressed==TouchKey[0]) return 1;
	else return 0;
}

char Button_Two_Pressed(void)
{
	if (KeyPressed==TouchKey[1]) return 1;
	else return 0;
}
