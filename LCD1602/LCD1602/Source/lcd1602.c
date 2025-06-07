#include "lcd1602.h"



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
	while((c = pgm_read_byte(str++)))
	{
		sendchar(c);
		_delay_ms(100);
	}
}

void send_ptr_str(char *str) // отправка строки по указателю массива
{
	    while (*str) {
		    sendchar(*str++); //посимвольная передача до нуля
			_delay_ms(50);

	    }
}


void load_my_char()
{
uint8_t my_symb[1][8] = { // 1 symbols 8 -bytes
		// П (символ 0)
			{0b00011111,
	  		0b00010001,
			0b00010001,
			0b00010001,
			0b00010001,
			0b00010001,
			0b00010001,
			0b00000000}};//CGRAM
	
	
	
	
	send(0x40, 0);
	for (int i=0; i < 1; i++) //num symbols
	{
		for (int j=0; j < 8; j++)
		{
			sendchar(my_symb[i][j]);
		}
	}
}