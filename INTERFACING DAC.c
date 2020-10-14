DAC:
/***************************************************/
/* Program to DAC
/***************************************************/
#include "LPC214X.H"
void InitializeDAC(void);
int main (void)
{
long c;
InitializeDAC(); //Initialize DAC
while(1)
{
DACR = 0x00; // Set DAC = 0
for(c=0;c<0xf0000;c++); // Delay
DACR = 0x0000ffc0; // Set DAC = (0x3ff << 6)
for(c=0;c<0xf0000;c++); // Delay
}
}
void InitializeDAC(void)
{
PINSEL1 = 0x00080000; // Set P0.25 for DAC output
}
void __gccmain()
{
}
