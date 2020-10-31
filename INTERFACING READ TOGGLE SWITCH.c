READ TOGGLE SWITCH :
#include "LPC214X.H"
voidInitializeIO(void);
int main (void)
{
unsigned char b;
InitializeIO();
//Initialize the I/O lines
while(1)
{
IOCLR0 = 0x00580000;
// Address Lines A0,A1,A2 set as 0
IOSET0 = 0x00080000;
// Set A0 to generate chip enable for toggle switches
IODIR1 &= 0xFF00FFFF;
b = IOPIN1 >> 16; IODIR1 |= 0x00FF0000;
IOPIN1 = b << 16; IOCLR0 = 0x00580000;
}
}
voidInitializeIO(void)
{
IODIR0 = 0x00580000; IODIR1 = 0x00ff0000;
}
void gccmain()
{
}
