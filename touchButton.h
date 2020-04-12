#ifndef __MAIN_H__
#define __MAIN_H__

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"

#define TOUCH_PORT  PORTB
#define DDR			DDRB
#define TOUCH_PIN   PINB

#define BUTTON1    PORTB0				//������ ������ �� PORTB0
#define BUTTON2    PORTB1				//������ ������ �� PORTB1


int CalibArray[2], CurrentArray[2];		//������� ��� �������� ������� ������ ������� ��������� ������
char Used_Pins [2];						//������������ ������
char TouchKey [2]; 						//���� ��������� ������. ����� ��� ������� ��������� � ������� �� ������� ����
char KeyPressed;						//���������� ��� �������� ���� ������� ������



int Charge_Time(char array);	//������� ������� ������ ������

void Button_Count (int *array);	//�-��� ���������� ������� ������ ������ ��� ��������� ������

void Calibration (void);		//���������� ��� ���������

void TOUCH_CompareKey (void);	//������� ������ ��������� ������ � ����������� ������� ������

char Button_One_Pressed(void);	//��� ������� ����� ������ ���������� true

char Button_Two_Pressed(void);	//��� ������� ������ ������ ���������� true

#endif