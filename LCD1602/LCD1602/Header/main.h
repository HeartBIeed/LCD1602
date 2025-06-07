#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "lcd1602.h"


#define E1 PORTD|=0b00001000 // ��������� ����� E � 1 ������������ ����
#define E0 PORTD&=0b11110111 // ��������� ����� E � 0
#define RS1 PORTD|=0b00000100 // ��������� ����� RS � 1 (������)
#define RS0 PORTD&=0b11111011 // ��������� ����� RS � 0 (�������)



#endif /* MAIN_H_ */

