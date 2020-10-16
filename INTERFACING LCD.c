LCD
/***************************************************/
/* LCD Routines for 2 line X 16 Characters Display
/***************************************************/
#include "LPC214x.h"
/* LPC214x definitions */
void WriteCommandLCD(unsigned char CommandByte);
void WriteDataLCD(unsigned char DataByte);
void LCDDelay(void);
void LCDDelay1600(void);
void SendByte(unsigned char Value);
void InitializeLCD();
void DataAddressDirection(void);
void DisplayLCD(char LineNumber,char *Message);
void DisplayLCD2Digit(char LineNumber,char CharPosition,char Data);
int main(void)
{
InitializeLCD();
//Initialize graphics LCD
DisplayLCD(0," NXP2148 ARM ");
DisplayLCD(1,"Evaluatin System");
while(1);
}
/* Initializes LCD */
void InitializeLCD()
{
DataAddressDirection();
IOSET0 = 0x00580000;
// Set A0, A1, A2
WriteCommandLCD(0x38);
//Command to select 8 bit interface
LCDDelay1600();
WriteCommandLCD(0x38);
//Command to select 8 bit interface
LCDDelay();
//Small delay
WriteCommandLCD(0x38);
//Command to select 8 bit interface
LCDDelay();
WriteCommandLCD(0x0c);
//Command to on cursor,blink cursor
LCDDelay();
WriteCommandLCD(0x06);
//Command for setting entry mode
LCDDelay();
WriteCommandLCD(0x01);
//Clear LCD
LCDDelay1600();
}
/* Writes a command byte to LCD */
void WriteCommandLCD(unsigned char CommandByte)
{
IOCLR1 = 0x03000000;
// Clear RS and RW
SendByte(CommandByte);
LCDDelay();
//Small delay
}
/* Send a byte of data to LCD */
void SendByte(unsigned char Value)
{
IOPIN1 &= 0xff00ffff;
IOPIN1 |= Value << 16;
/* Write data to data bus */IOSET0 = 0x00100000;
IOCLR0 = 0x00480000;
LCDDelay();
IOSET0 = 0x00580000;
LCDDelay();
/* Generate chip enable signal for LCD */
/* Set A0, A1 & A2 to disable LCD */
}
/* Writes a Data byte to LCD */
void WriteDataLCD(unsigned char DataByte)
{
IOCLR1 = 0x01000000;
/* clear RW */
IOSET1 = 0x02000000;
/* Set RS */
SendByte(DataByte);
LCDDelay();
//Small delay
}
/* Small delay */
void LCDDelay(void)
{
int
a;
for(a=0;a<0x1000;a++);
}
/* Big delay */
void LCDDelay1600(void)
{
long a;
for(a=0;a<0x050000;a++);
}
/* Makes cursor visible */
void CursorON(void)
{
WriteCommandLCD(0x0f);
//Command to switch on cursor
}
/* Makes cursor invisible */
void CursorOFF(void)
{
WriteCommandLCD(0x0c);
//Command to switch off cursor
}
void DisplayLCD2Digit(char LineNumber,char CharPosition,char Data)
{
unsigned char a;
if(LineNumber ==0)
{
//First Line
a = 0x80;
//command for first line selection
}
else
{
//Second line
a = 0xc0;
}
a+=(CharPosition);
WriteCommandLCD(a);
//command for second line selection
//Calculate the character position
//Send command to select the givendigit
if( (Data & 0xf0) < 0xa0)
//Check for less than 0xa0
{
a = ((Data & 0xf0) >> 4) + '0';
//Get the ASCII character
}
else
{
a = ((Data & 0xf0) >> 4) + 'A'- 0x0a;
//Get the ASCII character
}
WriteDataLCD(a);
//Display the first character
if( (Data & 0x0f) < 0x0a)
//Check for less tham 0x0a
{
a = (Data & 0x0f)+'0';
//Get the ASCII character
}
else
{
a = (Data & 0x0f)+'A' - 0x0a; //Get the ASCII character
}
WriteDataLCD(a);
}
/* Displays a message on LCD */
void DisplayLCD(char LineNumber,char *Message)
{
int
a;
if(LineNumber ==0)
{
//First Line
WriteCommandLCD(0x80);
//Select the first line
}
else
{
//Second line
WriteCommandLCD(0xc0);
//Select the second line
}
while(*Message)
{
WriteDataLCD(*Message);
//Display a character
Message++;
//Increment pointer
}
}
void DataAddressDirection(void)
{
IODIR0 |= 0x00580000;
// Set A0, A1, A2 output lines
IODIR1 |= 0x03ff0000;
}
void __gccmain()
{
}
