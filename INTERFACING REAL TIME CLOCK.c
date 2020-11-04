REAL TIME CLOCK
#include "LPC214x.h"
extern void irq_iic(void);
voidIic_Srv(void);
void
InitializeIIC(void);
// LPC21xx definitions
// interrupt processvoid I2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char
count,unsigned char *data); //Background call to start master send and receive byte
transfers
voidWriteByte(intaddr,unsigned char
*data);
void ReadByte(intaddr,unsigned char
*data); extern void delay2(void);
unsigned char
*I2CData,
I2Counter,
I2CAddress,
MemAddress,
lock;
int main(void)
{
int a;
unsigned char Hour=0,Min=0,Sec=0;
InitializeLCD();
// Initialize LCD
InitializeIIC();
// Initialize IIC Interface
DisplayLCD(0," RTC DEMO ");
// Display message
DisplayLCD(1," : : ");
while(1)
{
ReadByte(0x04,&Hour);
// Read Hours from
RTC
ReadByte(0x03,&Min);
// Read Minutes from RTC
ReadByte(0x02,&Sec);
// Read Seconds from RTC
DisplayLCD2Digit(1,4,Hour);
// Display
DisplayLCD2Digit(1,7,Min);
DisplayLCD2Digit(1,10,Sec);
}
}
voidInitializeIIC(void)
{
lock = 0;
VICVectCntl1
=
0x00000029;
VICVectAddr1
=
(unsigned
long)irq_iic;
VICIntEnable
=
0x00000200;
PINSEL0
|= 0x50;
=
I2C0SCLH
0x104;
=
I2C0SCLL
0x104;
}
//Write given data in RTC
voidWriteByte(intaddr,unsigned
char
*data)
{
I2CTransferByte(0xA0,addr,1,&data[0]);
while(lock==1);
}
voidReadByte(intaddr,unsigned
char
*data)
{I2CTransferByte(0xA0,addr,0,&data[0]);
I2CTransferByte(0xA1,addr,1,&data[0]);
while(lock==1);
//Initilise the lock flag
//select a priority slot for a given interrupt
//pass the address of the IRQ into the VIC
slot //enable interrupt
}
void I2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char
count,unsigned char *data )
{
while(lock == 1)
//Wait for interrupt to signal end of I2C
activity
{
}
void Iic_Srv(void)
{
switch(I2C0STAT)
switch to next action
{
case ( 0x08):
I2C0CONCLR
I2C0DAT
= 0x20;
= I2CAddress;
break;
case (0x18):
I2C0DAT
break;
case(0x20):
I2C0DAT
break;
case(0x28):
if(I2Counter-->0)
{
I2C0DAT
I2CData++;
}
Else
{
I2C0CONSET
lock = 0;
}
break;
case (0x30)
I2C0DAT
break;
=MemAddress;
= I2CAddress;
//Send address and write
bit
//Slave address+W, ACK
//Write Memory start address to tx
register
//Salve address +W, Not ACK
//Resend address and write bi
//Data sent, Ack
= *I2CData;
//Write data to tx register
= 0x10;
//Stop condition
//Signal end of I2C activity
:
= *I2CData;
//Data sent, NOT Ack
//Write data to tx registercase (0x40) :
I2C0CONSET
break;
case (0x48) :
I2C0CONSET
break;
}
}
{
Void main()
Main class();
{
{
*I2CData=
I2CData++;
}
else
{
*I2CData=
I2C0CONET
lock
}
break;
case (0x58):
I2C0CONSET
break;
default :
break;
}
I2C0CONCLR = 0x08;
VICVectAddr = 0x00000000;
}
= 0x04;
= 0x20;
//Slave Address +R, Not Ack
//Resend Start condition
I2C0DAT
I2C0DAT
= 0x10;
= 0;
= 0x20;
//Stop condition
//Signal end of I2C activity
//Data Received, Not Ack
// Resend Start condition
//Clear I2C interrupt flag
//Clear interrupt in

