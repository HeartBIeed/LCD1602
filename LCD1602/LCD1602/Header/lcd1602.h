#ifndef LCD1602_H_
#define LCD1602_H_

#include "main.h"


void LCD_ini(void);
void send(unsigned char c,unsigned char mode); 
void sendbyte(unsigned char c);
void sendchar(unsigned char c); // отправка 1 символа
void setpos(unsigned char x, unsigned y); // установка позиции Х 0-15, У 0-1.
void send_flash_str(const char *str); // отправка строки записанной на флеше
void send_ptr_str(char *str); // отправка строки по указателю массива
void load_my_char();

#endif /* LCD1602_H_ */
