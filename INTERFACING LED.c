LED FLASHING
#include "LPC214X.H"
void InitializeIO(void);
void InitializeTIMER0(void);
void T0_Srv(void);
void Delay(void);
extern void irq_T0(void);
unsigned int Count;
int main (void)
}
}
}
Longa;
unsigned char b;
InitializeIO();
// Initialize the I/O lines
InitializeTIMER0( // Initialize Timer 0
);
while(1)
{
//Sequentially switches from 1st LED to 8th LED with a periodic
interval for(b=0;b<8;b++)
{
IOCLR1 = 0x00ff0000;
// Clear all LED lines
IOSET1 = (0x01 << b) << 16;
// Switch on any one the line
IOCLR0 = 0x00580000;
// Clear A0,A1 and A2
IOSET0 = 0x00580000;
// Set A0,A1 and A2
Delay();
// Delay
}
//Sequentially switches from 8th LED to 1st LED with a periodic interval
for(b=0;b<8;b++)
{
IOCLR1 = 0x00ff0000;
// Clear all LED lines
IOSET1 = (0x80 >> b) << 16;
// Switch on any one the line
IOCLR0 = 0x00580000;
// Clear A0,A1 and A2
IOSET0 = 0x00580000;
// Set A0,A1 and A2
Delay();
// Delay
}
}
}
voidInitializeIO(void)
{
IODIR0 = 0x00580000;
IODIR1 = 0x00ff0000;
}
//Initialise timer0 used in LED Flashingvoid InitializeTIMER0(void)
{ //for 1msec delay
VPBDIV
= 0x00000002;
T0PR
= 0x0000012B;
T0TCR
= 0x00000002;
T0MCR
= 0x00000003;
generate an interrupt
T0MR0
= 0x00000064;
1ms
T0TCR
= 0x00000001;
VICVectAddr4 = (unsigned long)irq_T0;
VICVectCntl4 = 0x00000024;
VICIntEnable |= 0x00000010;
Count =0;
}
/* Timer0 interrupt service
routine */ void T0_Srv(void)
//Configure the VPB divider
//CCLK/2 = PCLK = 30MHz
//Load prescaler = 300, 30MHz/300=100KHz
//Reset counter and prescaler
//On match reset the counter and
//Set the cycle time, 100KHZ/100 = 1KHZ =
//enable timer
//Set the timer ISR vector address
//Set channel
//Enable the interrupt
{
Count++;
T0IR
|= 0x00000001;
VICVectAddr = 0x00000000;
//Counter is incremeted
//Clear match 0 interrupt
//Dummy write to signal end of interrupt
}
void Delay(void)
{
Count = 0;
while(Count < 1000);
}
void gccmain()
{
}

