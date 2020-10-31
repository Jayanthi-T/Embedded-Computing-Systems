INTERFGACING RELAY :
#include "LPC214X.H" void InitializeIO(void); int main (void)
{
long a;
IODIR0 = 0X40000400; ouput lines
while(1)
{
IOCLR0 = 0x00000400;
IOSET0 = 0x40000000; for(a=0;a<0xF0000;a++); IOCLR0
0x40000000; IOSET0 = 0x00000400; for(a=0;a<0xF0000;a++);
}
}
void gccmain()
{
}
