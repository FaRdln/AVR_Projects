/*
 * ATM.c
 *
 * Created: 11/15/2018 5:36:58 PM
 * Author : Noruzi
 */ 
#include <avr/io.h>
#include <avr/delay.h>
//-----------------------arrays
int button[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; int pass[4]={}; int user[4]={};
//-----------------------integers
int temp,temp1,m=1,counter=0,status=1,s=0;
//-----------------------username&password
int username=1234,password=4321;
//-----------------------functions
void pcb(); void pdb(); void M1(); void M2(); void M3();
//-----------------------**-----------------------//
int main(void)
{
	DDRA=0xff; DDRB=0xff; DDRC=0x00; DDRD=0xc0;
		while (1)
		{
			if (PINC)pcb();
//----------------------------------------------
			if (PIND)pdb();
		}
}
//-----------------------PortC Mapping(0-7)
void pcb()
{
			for(int i=0;i<8;i++)
			{
				if (PINC==button[i])
				{
					if (m==1)
					{
						PORTA=0xff;
						PORTB=0xff;
						temp=0; temp1=0;
						PORTD=0xc0;
						_delay_ms(500);
						PORTD=0x00;
						_delay_ms(500);
						m=2;
						break;
					}
					if (m==2)
					{
						PORTA=i;
						temp=i;
						pass[0]=i;
						_delay_ms(500);
						m=3;
						break;
					}
					if (m==3)
					{
						PORTA=i+(PORTA<<4);
						temp1=i;
						pass[1]=i;
						_delay_ms(500);
						m=4;
						break;
					}
					if (m==4)
					{
						PORTA=i+(PORTA<<4);
						PORTB=temp;
						pass[2]=i;
						_delay_ms(500);
						m=5;
						break;
					}
					if (m==5)
					{
						PORTA=i+(PORTA<<4);
						PORTB=temp1+temp*16;
						pass[3]=i;
						_delay_ms(500);
						m=6;
						break;
					}
//-------------------------------------
					if (m==6)
					{
						PORTA=0x00;
						PORTB=0x00;
						temp=0; temp1=0;
						PORTD=0xc0;
						_delay_ms(500);
						PORTD=0x00;
						_delay_ms(500);
						m=7;
						break;
					}
					if (m==7)
					{
						PORTA=i;
						temp=i;
						user[0]=i;
						_delay_ms(500);
						m=8;
						break;
					}
					if (m==8)
					{
						PORTA=i+(PORTA<<4);
						temp1=i;
						user[1]=i;
						_delay_ms(500);
						m=9;
						break;
					}
					if (m==9)
					{
						PORTA=i+(PORTA<<4);
						PORTB=temp;
						user[2]=i;
						_delay_ms(500);
						m=10;
						break;
					}
					if (m==10)
					{
						PORTA=i+(PORTA<<4);
						PORTB=temp1+temp*16;
						user[3]=i;
						_delay_ms(500);
						m=1;
						break;
					}						
				}
	}
}
//-----------------------PortD Mapping(8-9 & Modes)
void pdb()
{
				for(int i=0;i<2;i++)
				{
					if (PIND==button[i])
					{
						if (m==1)
						{
							PORTA=0xff;
							PORTB=0xff;
							temp=0; temp1=0;
							PORTD=0xc0;
							_delay_ms(500);
							PORTD=0x00;
							_delay_ms(500);
							m=2;
							break;
						}
						if (m==2)
						{
							PORTA=i+8;
							temp=i+8;
							pass[0]=i+8;
							_delay_ms(500);
							m=3;
							break;
						}
						if (m==3)
						{
							PORTA=i+8+(PORTA<<4);
							temp1=i+8;
							pass[1]=i+8;
							_delay_ms(500);
							m=4;
							break;
						}
						if (m==4)
						{
							PORTA=i+8+(PORTA<<4);
							PORTB=temp;
							pass[2]=i+8;
							_delay_ms(500);
							m=5;
							break;
						}
						if (m==5)
						{
							PORTA=i+8+(PORTA<<4);
							PORTB=temp1+temp*16;
							pass[3]=i+8;
							_delay_ms(500);
							m=6;
							break;
						}
						//-------------------------------------
						if (m==6)
						{
							PORTA=0x00;
							PORTB=0x00;
							temp=0; temp1=0;
							PORTD=0xc0;
							_delay_ms(500);
							PORTD=0x00;
							_delay_ms(500);
							m=7;
							break;
						}
						if (m==7)
						{
							PORTA=i+8;
							temp=i+8;
							user[0]=i+8;
							_delay_ms(500);
							m=8;
							break;
						}
						if (m==8)
						{
							PORTA=i+8+(PORTA<<4);
							temp1=i+8;
							user[1]=i+8;
							_delay_ms(500);
							m=9;
							break;
						}
						if (m==9)
						{
							PORTA=i+8+(PORTA<<4);
							PORTB=temp;
							user[2]=i+8;
							_delay_ms(500);
							m=10;
							break;
						}
						if (m==10)
						{
							PORTA=i+8+(PORTA<<4);
							PORTB=temp1+temp*16;
							user[3]=i+8;
							_delay_ms(500);
							m=1;
							break;
						}
					}
				}
						if ((PIND&0x08)!=0)M1();
						if ((PIND&0x10)!=0)M2();
						if ((PIND&0x20)!=0)M3();
}
//-----------------------Mode1(Only Check Password)
void M1()
{
long pwd = 1000 * pass[0] + 100 * pass[1] + 10 * pass[2] + pass[3];

	if ((PIND&0x04)!=0)
	{
	while((PIND&0x04)!=0){}
			if (password==pwd)
			{
				PORTD=0x40;
				_delay_ms(500);
			}
			else
			{
				counter++;
					if (counter>2)
					{
						PORTD=0x80;
						m=10;
						_delay_ms(1000);
					}
			}
	}
}
//-----------------------Mode2(Change Password)
void M2()
{
	while((PIND&0x10)!=0){}
	long pwd = 1000 * pass[0] + 100 * pass[1] + 10 * pass[2] + pass[3];
	password=pwd;
}
//-----------------------Mode3(Check Username & Password)
void M3()
{
	long pwd = 1000 * pass[0] + 100 * pass[1] + 10 * pass[2] + pass[3];
	long usn = 1000 * user[0] + 100 * user[1] + 10 * user[2] + user[3];
//-----------------------swap
	s=pwd;
	pwd=usn;
	usn=s;
//-----------------------
	if ((PIND&0x04)!=0)
	{
		while((PIND&0x04)!=0){}
			if (password==pwd&&username==usn)
			{
				PORTD=0x40;
				_delay_ms(500);
			}
			else
			{
				counter++;
				if (counter>2)
				{
					PORTD=0x80;
					m=10;
					_delay_ms(1000);
				}
			}
	}
}
