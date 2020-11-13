ADC
/****************************************************/ 
/* Read ADC channel 2 and display it on LCD Display
/****************************************************/
#include "LPC214x.h" /* LPC21xx definitions */
int ReadADC(char ChannelNumber);
int main(void)
{
int a;
unsigned char Channel = 2;
PINSEL1 = 0x04000000; // Select ADC to pin P0.29
InitializeLCD(); // Initialize LCD
DisplayLCD(0," ADC DEMO "); // Display message
DisplayLCD(1,"Channel 2: "); // Display message
while(1)
{
a=ReadADC(Channel); // Read ADC channel 2
DisplayLCD2Digit(1,10, (a >> 8)); // Display it on 2nd line of LCD
DisplayLCD2Digit(1,12, (a & 0xff));
LCDDelay1600(); 
}
}
//Read ADC data from given channel number
int ReadADC(char ChannelNumber)
{ 
int val,ch;
ch = 1<<ChannelNumber;
AD0CR = 0x00210400 | ch; // Setup A/D: 10-bit AIN @ 3MHz
AD0CR |= 0x01000000; // Start A/D Conversion
do
{
val = AD0DR2; // Read A/D Data Register
} 
while ((val & 0x80000000) == 0); // Wait for the conversion to complete
val = ((val >> 6) & 0x03FF); // Extract the A/D result
AD0CR &= ~0x01000000; // Stop A/D Conversion
return(val); // Return the Data Read
}
