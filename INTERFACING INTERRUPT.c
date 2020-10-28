INTERRUPT
/* Interrupt Study using interrupts EINT0 and EINT2/*
/* Up/down counter design using Point LEDs
/* For Interrupt EINT0 - Up counter
/* For Interrupt EINT2 - Down counter
#include "LPC214x.H"
/* LPC214x definitions */
extern void irq_INT0(void);
//interrupt process
extern void irq_INT2(void);
//interrupt process
void INT0_Srv(void);
void INT2_Srv(void);
void InitializeInterrupt(void);
unsigned char Counter=0;
int main(void)
{
IODIR0 |= 0x00780000;
// Direction setting for Address lines A0, A1 and A2
IODIR1 |= 0x00ff0000;
// Direction setting for Data lines D0 to D7
IOCLR0 = 0x00780000;
// Clear A0, A1, A2
InitializeInterrupt();
// Initialize interrupts
while(1);
}
//Initialise Interrupt
void InitializeInterrupt(void)
{
PINSEL0 = 0x0000C00C;
EXTMODE
= 0x05;
// edge select enabled for interrupts EINT0 and EINT2
VICVectAddr1 = (unsigned long)irq_INT2;
// Set the Interrupt0 ISR vector address
VICVectAddr0 = (unsigned long)irq_INT0;
// Set the Interrupt2 ISR vector address
VICVectCntl0 = 0x0000002e;
// Set channel 0 to EINT0
VICVectCntl1 = 0x00000030;
// Set channel 1 to EINT2
VICIntEnable = 0x00014000;
// Enable interrupts EINT0 and EINT2
}
/* Interrupt1 service routine */
void INT0_Srv(void)
{
Counter++;
// Increment Counter
IOCLR1 = 0x00ff0000;
// Set data lines to 0
IOSET1 = Counter << 16;
// Set values for LEDs in data lines D0 to D7
IOCLR0 = 0x00400000;
// Clear A3
IOSET0 = 0x00400000;
// Set A3
EXTINT |=0x01;
VICVectAddr = 0x00000000;
//Dummy write to signal end of interrupt
}
/* Interrupt2 service routine */
void INT2_Srv(void)
{
Counter--;
// Decrement Counter
IOCLR1 = 0x00ff0000;
// Set data lines to 0
IOSET1 = Counter << 16;
// Set values for LEDs in data lines D0 to D7
IOCLR0 = 0x00400000;
// Clear A3
IOSET0 = 0x00400000;
// Set A3
EXTINT |=0x04;
VICVectAddr = 0x00000000;
//Dummy write to signal end of interrupt
}
void __gccmain()
{
}RESULT:
Thus the Embedd
