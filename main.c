#ifndef F_CPU
#define F_CPU 16000000UL // 16
#endif
#include<avr/io.h>
#include<util/delay.h>

#define LCD_DATA PORTB//LCD data port
#define ctrl PORTD
#define en PD2//enable signal
#define rw PD1// read/write signal
#define rs PD0//register select signal

int count=0;
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_write_string(char *str);
int main()
{
	DDRB=0xFF;//make PORT B as output
	DDRD=0x07;
	init_LCD();// initialization of LCD
	_delay_ms(50);// delay of 50 miliseconds
	LCD_write_string("LCD you are");//function to print string on LCD
	LCD_cmd(0xc6);
	LCD_write_string("8 bit");
	_delay_ms(5);
	
	return 0;
}
void init_LCD(void)
{
	LCD_cmd(0x38);// initialization of 16X2 LCD in 8bit mode
	_delay_ms(1);
	LCD_cmd(0x01);//clear LCD
	_delay_ms(1);
	LCD_cmd(0x0c);// cursor ON
	_delay_ms(1);
	LCD_cmd(0x83);// ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
	return;
	
}
void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(1);
	return;
}
void LCD_write(unsigned char data)
{
	LCD_DATA= data;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(1);
	return;
}
void LCD_write_string(char *str)//store address value of the string in pointer *str
{
	int i=0;
	while(str[i]!='\0')// loop will go on till the NULL character in the string
	{
		LCD_write(str[i]);//sending data on LCD byte by byte
		i++;
	}
	return;
}