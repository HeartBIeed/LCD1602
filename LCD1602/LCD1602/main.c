#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define E1 PORTB|=0b00000100 // установка линии E в 1 стробирующая шина
#define E0 PORTB&=0b11111011 // установка линии E в 0
#define RS1 PORTB|=0b00000001 // установка линии RS в 1 (данные)
#define RS0 PORTB&=0b11111110 // установка линии RS в 0 (команда)

int iniport(void)
{
	
	DDRB=0xFF; // выход
	DDRD=0xFF; 
	
	PORTB=0b00000111;// установка пинов
	PORTD=0b00101111; 

 

}

void LCD_ini(void)
{
_delay_ms(15);
sendbyte(0b00000011);  // 11 включает 4 битный режим
_delay_ms(5);
sendbyte(0b00000011);
_delay_us(200);
sendbyte(0b00000011);
_delay_ms(1);
sendbyte(0b00000010);
_delay_ms(1);
sendbyte(0b00000010);
_delay_ms(1);

	send(0b00101000, 0); // отправка команд

_delay_ms(1);

	send(0b00001100, 0);
	
_delay_ms(1);

	send(0b00000110, 0);
	
_delay_ms(1);


}

void sendbyte(unsigned char c) // отправка байта
{
	
	E1;
		_delay_us(50);
		
	PORTD &= 0b11110000; // отчистка Д порта
	PORTD  |= c;
	
	E0;	
		_delay_us(50);
		
	}

void send(unsigned char c,unsigned char mode)
{
	if (mode ==0) 
	{RS0; // команда 0
	} 
	else
	{RS1; // данные 1
	}
	
	unsigned char hc=0;
	hc = c >> 4;

sendbyte(hc); // мл полубайт
sendbyte(c);	// ст полубайт
	
	
}

void sendchar(unsigned char c)
{

	send(c,1);
}



int main(void)
{

	
    while(1)
    {
		
	 iniport();
	 LCD_ini();
	 sendchar("n");


	 
	 
    }
}