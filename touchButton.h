#ifndef __MAIN_H__
#define __MAIN_H__

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"

#define TOUCH_PORT  PORTB
#define DDR			DDRB
#define TOUCH_PIN   PINB

#define BUTTON1    PORTB0				//Первая кнопка на PORTB0
#define BUTTON2    PORTB1				//Вторая кнопка на PORTB1


int CalibArray[2], CurrentArray[2];		//Массивы для хранения времени заряда ёмкости сенсорных кнопок
char Used_Pins [2];						//Используемые кнопки
char TouchKey [2]; 						//Коды сенсорных кнопок. Нужно для решения конфликта с кнопкой на нулевом пине
char KeyPressed;						//Переменная для хранения кода нажатой кнопки



int Charge_Time(char array);	//Подсчёт времени заряда кнопки

void Button_Count (int *array);	//Ф-ция заполнения массива тактов кнопок при ненажатой кнопке

void Calibration (void);		//Калибровка при включении

void TOUCH_CompareKey (void);	//Функция опроса сенсорных кнопок и определение нажатой кнопки

char Button_One_Pressed(void);	//При нажатой перой кнопке возвращает true

char Button_Two_Pressed(void);	//При нажатой второй кнопке возвращает true

#endif