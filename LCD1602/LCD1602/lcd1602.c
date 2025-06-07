#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> // ��� ������ �� �������� �� ���� ������



#define E1 PORTD|=0b00001000 // ��������� ����� E � 1 ������������ ����
#define E0 PORTD&=0b11110111 // ��������� ����� E � 0
#define RS1 PORTD|=0b00000100 // ��������� ����� RS � 1 (������)
#define RS0 PORTD&=0b11111011 // ��������� ����� RS � 0 (�������)

void send(unsigned char c,unsigned char mode); // ���������
void sendbyte(unsigned char c);


void iniport(void)
{
	PORTD=0x00;
	DDRD=0xFF; 

}

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
	while(c=pgm_read_byte(str++))
	{
		sendchar(c);
		
	}
}

send_ptr_str(char *str) // �������� ������ �� ��������� �������
{
	    while (*str) {
		    sendchar(*str++); //������������ �������� �� ����
	    }
}

int main(void)
{
	iniport();
	LCD_ini();
	setpos(5,1);


	char mystr[] = "Hello!";
	send_ptr_str(mystr); //�������� ������� 
	
	
	//send_flash_str(PSTR("Hello")); //�������� ���������� ������ �� ���� ������

	
    while(1)
    {
	
    }
	
}