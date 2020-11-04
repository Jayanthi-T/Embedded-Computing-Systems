TEMPERATURE SENSOR
#include "LPC214x.h"
/* LPC21xx definitions */
intReadADC(char ChannelNumber);
int main(void)
{
int a;
unsigned char Channel = 1, t[7];
PINSEL1 = 0x01000000;
// Select ADC to pin P0.28
InitializeLCD();
// Initialize LCD
DisplayLCD(0,"Room Temperature");
// Display message
while(1)
{
a=ReadADC(Channel);
// Read ADC channel 1
t[0] = a/100 + '0';
a -= (a/100) * 100;
t[1] = a/10 + '0';
t[2] = '.';
t[3] = a%10 + '0';
t[4] = 'C';
t[5] = 0;
DisplayLCD(1,t);
//
Display
the
room
temperature
LCDDelay1600();
}
}//Read ADC data from given channel number
intReadADC(char ChannelNumber)
{
intval,ch;
ch = 1<<ChannelNumber;
AD0CR = 0x00210400 | ch;
// Setup A/D: 10-bit AIN @ 3MHz
AD0CR |= 0x01000000;
// Start A/D Conversion
do
{
val = AD0DR1;
// Read A/D Data Register
}while ((val& 0x80000000) == 0);
val = ((val>> 6) & 0x03FF);
AD0CR &= ~0x01000000;
return(val);
// Wait for the conversion to complete
// Extract the A/D result
// Stop A/D Conversion
// Return the Data Read
}

