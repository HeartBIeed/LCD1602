#include "lcd1602.h"



void LCD_ini(void)
{
_delay_ms(15);
sendbyte(0b00000011);  // 11 �������� 4 ������ �����
_delay_ms(4);
sendbyte(0b00000011);
_delay_us(100);
sendbyte(0b00000011);
_delay_ms(1);
sendbyte(0b00000010);
_delay_ms(1);


	send(0b00101000, 0); // �������� ������

_delay_ms(1);

	send(0b00001100, 0);
	
_delay_ms(1);

	send(0b00000110, 0);
	
_delay_ms(1);


}

void sendbyte(unsigned char c) // �������� �����
{
	  c<<=4; // �������� ���� ������� �������� � �������


	E1;
		_delay_us(50);
		
	PORTD &= 0b00001111; // �������� ������� ������� � �����
	PORTD  |= c; // ���������� ������� �������
	
	E0;	
		_delay_us(50);
		
	}

void send(unsigned char c,unsigned char mode)
{
	if (mode ==0) 
	{RS0; // ������� 0
	} 
	else
	{RS1; // ������ 1
	}
	
	unsigned char hc=0;
	hc = c >> 4;

sendbyte(hc); // ������� ��������
sendbyte(c);	// �������  ��������
	
	
}

void sendchar(unsigned char c) // �������� 1 �������
{

	send(c,1);
	_delay_ms(10);

}

void setpos(unsigned char x, unsigned y) // ��������� ������� � 0-15, � 0-1.

{

	char adress;

	adress=(0x40*y+x)|0b10000000; // ������ �������� 2�� ������ ���� �� 40, 8� ��� �������� ������� ��������� �������

	send(adress, 0);

}

void send_flash_str(const char *str) // �������� ������ ���������� �� �����
{
	char c;
	while((c = pgm_read_byte(str++)))
	{
		sendchar(c);
		_delay_ms(100);
	}
}

void send_ptr_str(char *str) // �������� ������ �� ��������� �������
{
	    while (*str) {
		    sendchar(*str++); //������������ �������� �� ����
			_delay_ms(50);

	    }
}


void load_my_char()
{
uint8_t my_symb[1][8] = { // 1 symbols 8 -bytes
		// � (������ 0)
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