#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int iniport()
{
	
	DDRB=0xFF; // exit
	DDRD=0xFF; //exit
	
	PORTB=0b11100000;// pins
	PORTD=0b11110100; //pins

 

}

int main(void)
{

	
    while(1)
    {
	 iniport();
    }
}