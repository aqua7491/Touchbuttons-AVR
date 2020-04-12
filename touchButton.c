#include "touchButton.h"


char Used_Pins [] = {BUTTON1, BUTTON2}; //������������ ������
char TouchKey [] = {1, 2}; 				//���� ��������� ������. ����� ��� ������� ��������� � ������� �� ������� ����



int Charge_Time(char array)
{
	int chargeTimeCount=0;
	char PressedPin = Used_Pins[array];
	DDR |= (1<<PressedPin);									//��� �� �����
	while((TOUCH_PIN & (1<<PressedPin)));
	DDR &=~ (1<<PressedPin);								//��� �� ����
	while(!(TOUCH_PIN & (1<<PressedPin)))  chargeTimeCount++;
	return chargeTimeCount;									//���-�� ������ ��� ������������ ������
}



void Button_Count (int *array)
{
	int channel, count=0, timeCount=5;								// ��� ��������� �������� ������������ 5 �������
	
	for (channel = 0; channel < 2; channel++) array[channel] = 0;	//�������� ������������� �����
	cli();															//���������� ���������� ����������
	do {
		for (channel = 0; channel < 2; channel++) array[channel] += Charge_Time(channel);
	} while (++count < timeCount);									 //��������� ����� �� ��������� ����� �� timeCount �������
	sei();															//���������� ���������� ����������

	for (channel = 0; channel < 2; channel++) array[channel] /= timeCount;	//������� ����� ������
}


void Calibration (void)
{
	Button_Count (CalibArray);
}


void TOUCH_CompareKey (void)
{
	unsigned char channel;
	char tempKey=0;
	
	Button_Count (CurrentArray); //������� �������� ������� ������ ������� ��������� ������
	
	for (channel = 0; channel < 2; channel++)
	{   //���� ������ ������,  � ��� ����������� � ������
		if(CurrentArray[channel] > CalibArray[channel])  //���������� ������� � ��������� ��������
		{
			tempKey=TouchKey[channel];
		}
	}
	//���� � ������ ���������� ��� ����� ������� ������
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
