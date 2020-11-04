STEPPER MOTOR
#include"LPC214X.h"
voidInitializeIO(void);
int main (void)
{
unsigned char a;
unsigned int b;
long c,d;
InitializeIO(); //Initialize the I/O lines while(1)
{
for(d=0;d<100;d++) {
// Rotate clock wise
b=0x6666;
for(a=0;a<4;a++)
{
IOPIN1 = (b & 0xff00) << 8 ;
IOCLR0 = 0x00400000;
IOSET0 = 0x00400000;
for(c=0;c<0xa000;c++);
b = b << 1;
}
}
for(d=0;d<100;d++)
{
// Rotate counter clock wise
b=0x6666;
for(a=0;a<4;a++)
{
PIN1 = (b & 0xff00) <<8 ;
IOCLR0 = 0x00400000;
IOSET0 = 0x00400000;
// Clear A3
// Set A3for(c=0;c<0xa000;c++);
b = b >> 1;
// Delay
// Shift right side one
}
}
}
}
voidInitializeIO(void)
{
IODIR0 = 0x00580000;
IODIR1 = 0x00ff0000;
IOCLR0 = 0x00580000;
IOSET0 = 0x00180000;
}
void gccmain()
{
}

