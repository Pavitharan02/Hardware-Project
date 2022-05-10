#ifndef F_CPU
#define F_CPU 16000000UL // clock speed is 16MHz
#endif
#include<avr/io.h> // AVR header
#include<util/delay.h> // delay header
#include "USART.h"
#include "LCD.h"
#define LCD_DATA PORTB // port B is selected as LCD data port
#define ctrl PORTD // port D is selected as LCD command port
#define en PD7 // enable signal is connected to port D pin 7
#define rw PD6 // read/write signal is connected to port D pin 6
#define rs PD5 // register select signal is connected to port D pin 5
/*void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
*/


int main()
{
	lcd();
	rfid_chk();
	
	return 0;
}

void lcd()
{
	DDRB=0xFF; // set LCD data port as output
	DDRD=0xE0; // set LCD signals (RS, RW, E) as out put
	init_LCD(); // initialize LCD
	_delay_ms(10); // delay of 100 Milli seconds
	LCD_cmd(0x0C); // display on, cursor off
	_delay_ms(10);
	
	LCD_Write_String("Show Your");
	_delay_ms(50);
	LCD_cmd(0xC0); // move cursor to the start of 2nd line
	_delay_ms(100);
	LCD_Write_String("RFID Card");
	

}

void rfid_chk()
{
	unsigned char s1,s2,s3,s4,id[12];
	unsigned char a[12]="13006F6B5391";
	unsigned char b[12]="13006FA337F5";
	unsigned char c[12]="13006F4B6773";
	unsigned char d[12]="13006FC351A2";
	uart_init();
	_delay_ms(100);
	
	while(1)
	{
		s1=0;
		s2=0;
		s3=0;
		s4=0;
		for(int i=0;i<12;i++) // reading RFID tag number
		{
			id[i]=rx_data();
			if(a[i]==id[i])
			s1++;
			if(b[i]==id[i])
			s2++;
			if(c[i]==id[i])
			s3++;
			if(d[i]==id[i])
			s4++;
		}
		
		if(s1==12)		// check for authentication
		{
			
			LCD_cmd(0x01);
			_delay_ms(1);
			LCD_Write_String("Student 1");
			_delay_ms(50);
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_Write_String("Attendance Done");
			_delay_ms(5000);
			LCD_cmd(0x01); // make display ON, cursor ON
			_delay_ms(1);
		}
		else if(s2==12)		// check for authentication
		{
			LCD_cmd(0x01);
			_delay_ms(1);
			LCD_Write_String("Student 2");
			_delay_ms(50);
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_Write_String("Attendance Done");
			_delay_ms(5000);
			LCD_cmd(0x01); // make display ON, cursor ON
			_delay_ms(1);
		}
		else if(s3==12)		// check for authentication
		{
			LCD_cmd(0x01);
			_delay_ms(1);
			LCD_Write_String("Student 3");
			_delay_ms(50);
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_Write_String("Attendance Done");
			_delay_ms(5000);
			LCD_cmd(0x01); // make display ON, cursor ON
			_delay_ms(1);
		}
		else if(s4==12)		// check for authentication
		{
			LCD_cmd(0x01);
			_delay_ms(1);
			LCD_Write_String("Student 4");
			_delay_ms(50);
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_Write_String("Attendance Done");
			_delay_ms(5000);
			LCD_cmd(0x01); // make display ON, cursor ON
			_delay_ms(1);
		}
		else               // unauthorized person
		{
			LCD_cmd(0x01);
			_delay_ms(1);
			LCD_Write_String("Unidentified");
			_delay_ms(50);
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_Write_String("RFID Card");
			_delay_ms(5000);
			LCD_cmd(0x01); // make display ON, cursor ON
			_delay_ms(1);
		}
	}

}