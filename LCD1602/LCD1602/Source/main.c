#include "main.h"
#include "lcd1602.h"



void iniport(void)
{
	PORTD=0x00;
	DDRD=0xFF;

}





int main(void)
{
	iniport();
	LCD_ini();
	
//	setpos(0,0);
	//char mystr[] = "Hello World!";
//	send_ptr_str(mystr); //отправка массива
	
//	setpos(0,1);
//	char mystr2[] = "random text";
//	send_ptr_str(mystr2);
	
	
	
	//send_flash_str(PSTR("Hello")); //отправка вложенного текста из Флеш строки
	
	load_my_char();
	_delay_ms(10);
	sendchar(0);
	
	while(1)
	{
		
	}
}