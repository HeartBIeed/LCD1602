#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> // для работы со сторками на флеш памяти



#define E1 PORTD|=0b00001000 // установка линии E в 1 стробирующая шина
#define E0 PORTD&=0b11110111 // установка линии E в 0
#define RS1 PORTD|=0b00000100 // установка линии RS в 1 (данные)
#define RS0 PORTD&=0b11111011 // установка линии RS в 0 (команда)

void send(unsigned char c,unsigned char mode); // прототипы
void sendbyte(unsigned char c);


void iniport(void)
{
	PORTD=0x00;
	DDRD=0xFF; 

}

void LCD_ini(void)
{
_delay_ms(15);
sendbyte(0b00000011);  // 11 включает 4 битный режим
_delay_ms(4);
sendbyte(0b00000011);
_delay_us(100);
sendbyte(0b00000011);
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
	  c<<=4; // сдвигаем байт младшей тетрадой к старшей


	E1;
		_delay_us(50);
		
	PORTD &= 0b00001111; // отчистка старшей тетрады Д порта
	PORTD  |= c; // отправляем старшую тетраду
	
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

sendbyte(hc); // старший полубайт
sendbyte(c);	// младший  полубайт
	
	
}

void sendchar(unsigned char c) // отправка 1 символа
{

	send(c,1);
	_delay_ms(10);

}

void setpos(unsigned char x, unsigned y) // установка позиции Х 0-15, У 0-1.

{

	char adress;

	adress=(0x40*y+x)|0b10000000; // адреса символов 2ой строки идут от 40, 8й бит передает команду установки позиции

	send(adress, 0);

}

void send_flash_str(const char *str) // отправка строки записанной на флеше
{
	char c;
	while(c=pgm_read_byte(str++))
	{
		sendchar(c);
		
	}
}

send_ptr_str(char *str) // отправка строки по указателю массива
{
	    while (*str) {
		    sendchar(*str++); //посимвольная передача до нуля
	    }
}

int main(void)
{
	iniport();
	LCD_ini();
	setpos(5,1);


	char mystr[] = "Hello!";
	send_ptr_str(mystr); //отправка массива 
	
	
	//send_flash_str(PSTR("Hello")); //отправка вложенного текста из Флеш строки

	
    while(1)
    {
	
    }
	
}