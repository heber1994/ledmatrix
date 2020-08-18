#ifndef F_CPU
#define F_CPU 16000000L // or whatever may be your frequency
#endif

#define LATCH 0x02
#define SHIFT 0x04 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>   
#include <avr/interrupt.h>
#include <math.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "Export\export.h"
#include "displaypicture.h"

//PORTB0 is data input
//PORTB1 is the storage register clock input (STCP)
//PORTB2 is the Shift Register Clock Input (SHCP)


void drawpixel(uint8_t x, uint8_t y, uint8_t bright);
void alpha(char alphabet);
volatile void display();
void scrollingtext();
void fillmemorywithscrolltext(char string[]);
void displayscrolltext();
void charperchar(char character);
void displaypicture(uint8_t picnumber, uint8_t heightinpixels, uint8_t cycles, uint8_t speed);

char *ptr;
const char string_1[] PROGMEM = "COQUITO CLAVO UN CLAVITO..   ";

uint8_t temp1=0; // initialize variable to 0
uint8_t temp2=0; // initialize variable to 0
uint8_t screenbuffer1[6]; // buffer only works with 8-bit letters ABCDEFG...Z 8 pixels in height and 6-7 pixels width
uint8_t screenbuffer2[6];
uint8_t screenbuffer3[6];
uint8_t screenbuffer4[6];

//global variable declarations
const uint8_t sizeofx=24;
const uint8_t sizeofy=12;
uint8_t br = 11;

//global variables for interrupt routine
uint8_t currentrow=0;
uint8_t bright=0;
/////////

const uint8_t brightmax = 12;
volatile uint8_t matrix1[12][12];
volatile uint8_t matrix2[12][12];
volatile uint8_t matrix3[12][12];

ISR(TIMER1_COMPA_vect)
{
uint8_t datatransfer;
uint8_t mask = 0x01;
uint8_t buffer = 0x00;
//the matrix is divided into 3 sections, each containing 8 leds in width and 12 leds in height.
//each section receives data from an array matrix1[][], matrix2[][] and matrix3[][]
//data from the matrix array is saved in the "datatransfer" variable and then edited to shift bits using PORT B.
			for(datatransfer=0; datatransfer<= 7; datatransfer++)
			{
			buffer = matrix1[currentrow][bright]>>datatransfer; //shift bits by "sizeofx" then mask		 
				if(buffer&mask)	//apply mask. if true, then HIGH, if false, LOW.			
			 	{
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
				 PORTB = 0x05;	// 0000 0101	a shift with data as HIGH
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
		   	 	}				 
				else	//false, trow a LOW
				{
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				 PORTB = 0x04;	// 0000 0100	a shift with data as LOW
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				}
			}
			for(datatransfer=0; datatransfer<= 7; datatransfer++)
			{
			buffer = matrix2[currentrow][bright]>>datatransfer; //shift bits by "sizeofx" then mask		 
				if(buffer&mask)	//apply mask. if true, then HIGH, if false, LOW.			
			 	{
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
				 PORTB = 0x05;	// 0000 0101	a shift with data as HIGH
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
		   	 	}			 
				else	//false, trow a LOW
				{
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				 PORTB = 0x04;	// 0000 0100	a shift with data as LOW
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				}
			}
			for(datatransfer=0; datatransfer<= 7; datatransfer++)
			{
			buffer = matrix3[currentrow][bright]>>datatransfer; //shift bits by "sizeofx" then mask		 
				if(buffer&mask)	//apply mask. if true, then HIGH, if false, LOW.			
			 	{
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
				 PORTB = 0x05;	// 0000 0101	a shift with data as HIGH
				 PORTB = 0x01;	// 0000 0001	shift read by chips since high to low transition is seen
		   	 	}				 
				else	//false, trow a LOW
				{
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				 PORTB = 0x04;	// 0000 0100	a shift with data as LOW
				 PORTB = 0x00;	// 0000 0000	shift read by chips since high to low transition is seen
				}
			}
			if(currentrow<=7)
			{
			PORTD = 0x00;
			PORTC = (1<<currentrow);
			}
			else
			{
			PORTC = 0x00;
			PORTD = (1<<(currentrow-8));
			}
		 PORTB = LATCH;	// LATCH releases data for the current row. e.g. the entire row #1 for all sections light up with different LED data.
		 PORTB = 0x00;
		 currentrow+=1;		 
		 if(currentrow==(sizeofy))
		 {
		 	currentrow = 0;
			bright+=1;
		 }
		 if(bright==brightmax)
		 {
		 	bright = 0;
		 }
}

//start of main
int main(int argc, char *argv[])
{
memset(matrix1,0, sizeof(matrix1));//initialize matrix array to 0
memset(matrix2,0, sizeof(matrix2));//initialize matrix array to 0
memset(matrix3,0, sizeof(matrix3));//initialize matrix array to 0
memset(screenbuffer1,0, sizeof(screenbuffer1));//initialize screen buffer array to 0. screenbuffer 1-4 used to display letters.
memset(screenbuffer2,0, sizeof(screenbuffer2));//initialize screen buffer array to 0. screenbuffer 1-4 used to display letters.
memset(screenbuffer3,0, sizeof(screenbuffer2));//initialize screen buffer array to 0. screenbuffer 1-4 used to display letters.
memset(screenbuffer4,0, sizeof(screenbuffer2));//initialize screen buffer array to 0. screenbuffer 1-4 used to display letters.

DDRB = 0x0F; //setting first four pins of port B as outputs.
DDRC = 0xFF; // setting port C as output
DDRD = 0xFF; // setting port D as output

PORTC = 0x00; // turn all rows off initialize port C with all pins low.
PORTD = 0x00; // turn all rows off. initialize port D with all pins low.
PORTB = 0x00; // initialize port B with all pins LOW
//interrup subroutine settings
TCCR1A = 0x00;
 TCCR1B |= (1 << WGM12);
 TCCR1B |= (1 << CS10);
 TCCR1B |= (1 << CS11); // CTC mode. clear counter on TCNT2 == OCR1A


 TCNT1 = 0; // start counting at 0
 OCR1A = 30;
 TIMSK=0x00;
 TIMSK = (1 << OCIE1A);
 sei();

//this section of code just calculates how long a string is... specifically, string_1. it is then used to stop displaying text on-screen
//once the counter reaches a maximum number, denoted by the size of the string.
int anotherloop;
int counter = 0;
do
{
counter = counter+1;
}while(pgm_read_byte(&(string_1[counter])) != '\0');

	while(1)
	{
			runpictureprogram();	// executes picture program from Export/export.h

		for(anotherloop=0;anotherloop<counter;anotherloop++)
		{
		charperchar(pgm_read_byte(&(string_1[anotherloop])));
		}
	}

return 0;
}

void charperchar(char character)
{
uint8_t charinbinary[6];

switch(character)

{
case '.':
charinbinary[0] = 0xC0; charinbinary[1] = 0xC0; charinbinary[2] = 0x00; charinbinary[3] = 0x00; charinbinary[4] = 0x00; charinbinary[5] = 0x00;
break;

case ',':
charinbinary[0] = 0x60; charinbinary[1] = 0xE0; charinbinary[2] = 0x00; charinbinary[3] = 0x00; charinbinary[4] = 0x00; charinbinary[5] = 0x00;
break;

case ' ':
charinbinary[0] = 0x00; charinbinary[1] = 0x00; charinbinary[2] = 0x00; charinbinary[3] = 0x00; charinbinary[4] = 0x00; charinbinary[5] = 0x00;
break;

case 'A':
charinbinary[0] = 0xFE; charinbinary[1] = 0xFF; charinbinary[2] = 0x33; charinbinary[3] = 0x33; charinbinary[4] = 0xFF; charinbinary[5] = 0xFE;
break;

case 'B':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xDB;charinbinary[3] = 0xDB;charinbinary[4] = 0xFF;charinbinary[5] = 0x66;
break;

case 'C':
charinbinary[0] = 0x7E;charinbinary[1] = 0xFF;charinbinary[2] = 0xC3;charinbinary[3] = 0xC3;charinbinary[4] = 0xC3;charinbinary[5] = 0xC3;
break;

case 'D':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xC3;charinbinary[3] = 0xC3;charinbinary[4] = 0xFF;charinbinary[5] = 0x7E;
break;

case 'E':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xDB;charinbinary[3] = 0xDB;charinbinary[4] = 0xC3;charinbinary[5] = 0xC3;
break;

case 'F':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0x1B;charinbinary[3] = 0x1B;charinbinary[4] = 0x3;charinbinary[5] = 0x3;
break;

case 'G':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xC3;charinbinary[3] = 0xDB;charinbinary[4] = 0xFB;charinbinary[5] = 0xFB;
break;

case 'H':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0x18;charinbinary[3] = 0x18;charinbinary[4] = 0xFF;charinbinary[5] = 0xFF;
break;

case 'I':
charinbinary[0] = 0x0;charinbinary[1] = 0x81;charinbinary[2] = 0xFF;charinbinary[3] = 0xFF;charinbinary[4] = 0x81;charinbinary[5] = 0x0;
break;

case 'J':
charinbinary[0] = 0xC3;charinbinary[1] = 0xC3;charinbinary[2] = 0xFF;charinbinary[3] = 0xFF;charinbinary[4] = 0x3;charinbinary[5] = 0x3;
break;

case 'K':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0x3C;charinbinary[3] = 0x66;charinbinary[4] = 0xC3;charinbinary[5] = 0x81;
break;

case 'L':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xC0;charinbinary[3] = 0xC0;charinbinary[4] = 0xC0;charinbinary[5] = 0x0;
break;

case 'M':
charinbinary[0] = 0xFF;charinbinary[1] = 0x6;charinbinary[2] = 0xC;charinbinary[3] = 0xC;charinbinary[4] = 0x6;charinbinary[5] = 0xFF;
break;

case 'N':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0xC;charinbinary[3] = 0x30;charinbinary[4] = 0xFF;charinbinary[5] = 0xFF;
break;

case 'O':
charinbinary[0] = 0x7E;charinbinary[1] = 0xFF;charinbinary[2] = 0xC3;charinbinary[3] = 0xC3;charinbinary[4] = 0xFF;charinbinary[5] = 0x7E;
break;

case 'P':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0x33;charinbinary[3] = 0x33;charinbinary[4] = 0x3F;charinbinary[5] = 0x1E;
break;

case 'Q':
charinbinary[0] = 0x80;charinbinary[1] = 0x7E;charinbinary[2] = 0xFF;charinbinary[3] = 0xC3;charinbinary[4] = 0xFF;charinbinary[5] = 0x7E;
break;

case 'R':
charinbinary[0] = 0xFF;charinbinary[1] = 0xFF;charinbinary[2] = 0x3B;charinbinary[3] = 0x7B;charinbinary[4] = 0xDF;charinbinary[5] = 0x8E;
break;

case 'S':
charinbinary[0] = 0xCE;charinbinary[1] = 0xDF;charinbinary[2] = 0xDB;charinbinary[3] = 0xDB;charinbinary[4] = 0xFB;charinbinary[5] = 0x73;
break;

case 'T':
charinbinary[0] = 0x3;charinbinary[1] = 0x3;charinbinary[2] = 0xFF;charinbinary[3] = 0xFF;charinbinary[4] = 0x3;charinbinary[5] = 0x3;
break;

case 'U':
charinbinary[0] = 0x7F;charinbinary[1] = 0xFF;charinbinary[2] = 0xC0;charinbinary[3] = 0xC0;charinbinary[4] = 0xFF;charinbinary[5] = 0x7F;
break;

case 'V':
charinbinary[0] = 0x1F;charinbinary[1] = 0x3F;charinbinary[2] = 0xF0;charinbinary[3] = 0xF0;charinbinary[4] = 0x3F;charinbinary[5] = 0x1F;
break;

case 'W':
charinbinary[0] = 0x7F;charinbinary[1] = 0xC0;charinbinary[2] = 0x60;charinbinary[3] = 0x60;charinbinary[4] = 0xC0;charinbinary[5] = 0x7F;
break;

case 'X':
charinbinary[0] = 0xC3;charinbinary[1] = 0xE7;charinbinary[2] = 0x3C;charinbinary[3] = 0x3C;charinbinary[4] = 0xE7;charinbinary[5] = 0xC3;
break;

case 'Y':
charinbinary[0] = 0x3;charinbinary[1] = 0x7;charinbinary[2] = 0xFC;charinbinary[3] = 0xFC;charinbinary[4] = 0x7;charinbinary[5] = 0x3;
break;

case 'Z':
charinbinary[0] = 0xC3;charinbinary[1] = 0xE3;charinbinary[2] = 0xF3;charinbinary[3] = 0xDB;charinbinary[4] = 0xCF;charinbinary[5] = 0xC7;
break;

}
uint8_t placeholder;
uint8_t tempmask = 0x01;	
uint8_t loop1, loop2, loop3;



for(loop3=0;loop3<(7*1)+0;loop3++)
{
memset(matrix1,0, sizeof(matrix1));//initialize matrix array to 0
memset(matrix2,0, sizeof(matrix2));//initialize matrix array to 0
memset(matrix3,0, sizeof(matrix3));//initialize matrix array to 0
	for(loop2=0;loop2<6;loop2++)
	{

		for(loop1=0;loop1<8; loop1++)
		{
		 placeholder = screenbuffer4[loop2]>>loop1;
			 if(placeholder&tempmask)
			 {
			 drawpixel(-5+loop2-loop3, 9-loop1, br);
			 }
		
		}


		for(loop1=0;loop1<8; loop1++)
		{
		 placeholder = screenbuffer3[loop2]>>loop1;
			 if(placeholder&tempmask)
			 {
			 drawpixel(2+loop2-loop3, 9-loop1, br);
			 }		
		}

		for(loop1=0;loop1<8; loop1++)
		{
		 placeholder = screenbuffer2[loop2]>>loop1;
			 if(placeholder&tempmask)
			 {
			 drawpixel(9+loop2-loop3, 9-loop1, br);
			 }		
		}

		for(loop1=0;loop1<8; loop1++)
		{
		 placeholder = screenbuffer1[loop2]>>loop1;
			 if(placeholder&tempmask)
			 {
			 drawpixel(16+loop2-loop3, 9-loop1, br);
			 }		
		}

		for(loop1=0;loop1<8; loop1++)
		{
		 placeholder = charinbinary[loop2]>>loop1;
			 if(placeholder&tempmask)
			 {
			 drawpixel(23+loop2-loop3, 9-loop1, br);
			 }		
		}	
	}
	delay_ms(17);
}
for(loop1 = 0; loop1<6;loop1++)
{
screenbuffer4[loop1] = screenbuffer3[loop1]; // they are just getting zeroes at this point...
}
for(loop1 = 0; loop1<6;loop1++)
{
screenbuffer3[loop1] = screenbuffer2[loop1]; // they are just getting zeroes at this point...
}
for(loop1 = 0; loop1<6;loop1++)
{
screenbuffer2[loop1] = screenbuffer1[loop1]; // they are just getting zeroes at this point...
}

for(loop1 = 0; loop1<6;loop1++)
{
screenbuffer1[loop1] = charinbinary[loop1]; // they are just getting zeroes at this point...
}
}





void drawpixel(uint8_t x, uint8_t y, uint8_t bright)
{
uint8_t loop;
	switch(x)
	{
	case 0 ... 7:
		for(loop=0;loop<bright;loop++)
		{
		matrix1[y][loop] |= 1<<x;
		}
	break;
	case 8 ... 15:
		for(loop=0;loop<bright;loop++)
		{
		matrix2[y][loop] |= 1<<(x-8);
		}
	break;
	case 16 ... 23:
		for(loop=0;loop<bright;loop++)
		{
		matrix3[y][loop] |= 1<<(x-16);
		}
	break;
	}
}
void delay_ms(int ms)
{
  while (0 < ms)
  {  
    _delay_ms(1);
    --ms;
  }
}

void alpha(char alphabet)
{
memset(matrix1,0x00, sizeof(matrix1));//initialize matrix array to 0
memset(matrix2,0x00, sizeof(matrix2));//initialize matrix array to 0
memset(matrix3,0x00, sizeof(matrix3));//initialize matrix array to 0
switch(alphabet)
{
case 'A':
drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);			drawpixel(4,8,br);	drawpixel(5,8,br);
drawpixel(0,7,br);	drawpixel(1,7,br);			drawpixel(4,7,br);	drawpixel(5,7,br);
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);	drawpixel(4,6,br);	drawpixel(5,6,br);
drawpixel(0,5,br);	drawpixel(1,5,br);	drawpixel(2,5,br);	drawpixel(3,5,br);	drawpixel(4,5,br);	drawpixel(5,5,br);
drawpixel(0,4,br);	drawpixel(1,4,br);			drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);			drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);			drawpixel(4,2,br);	drawpixel(5,2,br);
break;

case 'B':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	
drawpixel(0,9,br);	drawpixel(1,9,br);			drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);			drawpixel(4,8,br);	drawpixel(5,8,br);
drawpixel(0,7,br);	drawpixel(1,7,br);			drawpixel(4,7,br);	drawpixel(5,7,br);
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);	drawpixel(4,6,br);	
drawpixel(0,5,br);	drawpixel(1,5,br);			drawpixel(4,5,br);	drawpixel(5,5,br);
drawpixel(0,4,br);	drawpixel(1,4,br);			drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);			drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	

break;

case 'C':
	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);				
drawpixel(0,7,br);	drawpixel(1,7,br);				
drawpixel(0,6,br);	drawpixel(1,6,br);				
drawpixel(0,5,br);	drawpixel(1,5,br);				
drawpixel(0,4,br);	drawpixel(1,4,br);				
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);	drawpixel(5,3,br);
	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'D':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);			drawpixel(4,8,br);	drawpixel(5,8,br);
drawpixel(0,7,br);	drawpixel(1,7,br);			drawpixel(4,7,br);	drawpixel(5,7,br);
drawpixel(0,6,br);	drawpixel(1,6,br);			drawpixel(4,6,br);	drawpixel(5,6,br);
drawpixel(0,5,br);	drawpixel(1,5,br);			drawpixel(4,5,br);	drawpixel(5,5,br);
drawpixel(0,4,br);	drawpixel(1,4,br);			drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	

break;

case 'E':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);				
drawpixel(0,7,br);	drawpixel(1,7,br);				
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);		
drawpixel(0,5,br);	drawpixel(1,5,br);				
drawpixel(0,4,br);	drawpixel(1,4,br);				
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'F':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);				
drawpixel(0,7,br);	drawpixel(1,7,br);	drawpixel(2,7,br);	drawpixel(3,7,br);		
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);		
drawpixel(0,5,br);	drawpixel(1,5,br);				
drawpixel(0,4,br);	drawpixel(1,4,br);				
drawpixel(0,3,br);	drawpixel(1,3,br);				
drawpixel(0,2,br);	drawpixel(1,2,br);				

break;

case 'G':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);				
drawpixel(0,7,br);	drawpixel(1,7,br);				
drawpixel(0,6,br);	drawpixel(1,6,br);		drawpixel(3,6,br);	drawpixel(4,6,br);	drawpixel(5,6,br);
drawpixel(0,5,br);	drawpixel(1,5,br);		drawpixel(3,5,br);	drawpixel(4,5,br);	drawpixel(5,5,br);
drawpixel(0,4,br);	drawpixel(1,4,br);			drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'H':
drawpixel(0,10,br);	drawpixel(1,10,br);			drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);			drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);			drawpixel(4,8,br);	drawpixel(5,8,br);
drawpixel(0,7,br);	drawpixel(1,7,br);	drawpixel(2,7,br);	drawpixel(3,7,br);	drawpixel(4,7,br);	drawpixel(5,7,br);
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);	drawpixel(4,6,br);	drawpixel(5,6,br);
drawpixel(0,5,br);	drawpixel(1,5,br);			drawpixel(4,5,br);	drawpixel(5,5,br);
drawpixel(0,4,br);	drawpixel(1,4,br);			drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);			drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);			drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'I':
drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);
drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);
	drawpixel(2,8,br);	drawpixel(3,8,br);	
	drawpixel(2,7,br);	drawpixel(3,7,br);	
	drawpixel(2,6,br);	drawpixel(3,6,br);	
	drawpixel(2,5,br);	drawpixel(3,5,br);	
	drawpixel(2,4,br);	drawpixel(3,4,br);	
drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);
drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);

break;

case 'J':
drawpixel(0,10,br);	drawpixel(1,10,br);	drawpixel(2,10,br);	drawpixel(3,10,br);	drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);	drawpixel(2,9,br);	drawpixel(3,9,br);	drawpixel(4,9,br);	drawpixel(5,9,br);
		drawpixel(2,8,br);	drawpixel(3,8,br);		
		drawpixel(2,7,br);	drawpixel(3,7,br);		
		drawpixel(2,6,br);	drawpixel(3,6,br);		
		drawpixel(2,5,br);	drawpixel(3,5,br);		
drawpixel(0,4,br);		drawpixel(2,4,br);	drawpixel(3,4,br);		
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);		
	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);		

break;

case 'K':
drawpixel(0,10,br);	drawpixel(1,10,br);			drawpixel(4,10,br);	drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);		drawpixel(3,9,br);	drawpixel(4,9,br);	
drawpixel(0,8,br);	drawpixel(1,8,br);	drawpixel(2,8,br);	drawpixel(3,8,br);		
drawpixel(0,7,br);	drawpixel(1,7,br);	drawpixel(2,7,br);			
drawpixel(0,6,br);	drawpixel(1,6,br);	drawpixel(2,6,br);	drawpixel(3,6,br);		
drawpixel(0,5,br);	drawpixel(1,5,br);	drawpixel(2,5,br);	drawpixel(3,5,br);	drawpixel(4,5,br);	
drawpixel(0,4,br);	drawpixel(1,4,br);		drawpixel(3,4,br);	drawpixel(4,4,br);	drawpixel(5,4,br);
drawpixel(0,3,br);	drawpixel(1,3,br);			drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);			drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'L':
drawpixel(0,10,br);	drawpixel(1,10,br);				
drawpixel(0,9,br);	drawpixel(1,9,br);				
drawpixel(0,8,br);	drawpixel(1,8,br);				
drawpixel(0,7,br);	drawpixel(1,7,br);				
drawpixel(0,6,br);	drawpixel(1,6,br);				
drawpixel(0,5,br);	drawpixel(1,5,br);				
drawpixel(0,4,br);	drawpixel(1,4,br);				
drawpixel(0,3,br);	drawpixel(1,3,br);	drawpixel(2,3,br);	drawpixel(3,3,br);	drawpixel(4,3,br);	drawpixel(5,3,br);
drawpixel(0,2,br);	drawpixel(1,2,br);	drawpixel(2,2,br);	drawpixel(3,2,br);	drawpixel(4,2,br);	drawpixel(5,2,br);

break;

case 'M':
drawpixel(0,10,br);					drawpixel(5,10,br);
drawpixel(0,9,br);	drawpixel(1,9,br);			drawpixel(4,9,br);	drawpixel(5,9,br);
drawpixel(0,8,br);	drawpixel(1,8,br);	drawpixel(2,8,br);	drawpixel(3,8,br);	drawpixel(4,8,br);	drawpixel(5,8,br);
drawpixel(0,7,br);		drawpixel(2,7,br);	drawpixel(3,7,br);		drawpixel(5,7,br);
drawpixel(0,6,br);					drawpixel(5,6,br);
drawpixel(0,5,br);					drawpixel(5,5,br);
drawpixel(0,4,br);					drawpixel(5,4,br);
drawpixel(0,3,br);					drawpixel(5,3,br);
drawpixel(0,2,br);					drawpixel(5,2,br);

break;


}
}





























