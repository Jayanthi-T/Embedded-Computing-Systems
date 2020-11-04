7 SEGMENT LED
#include "LPC214x.h"
// LPC21xx definitions
extern void irq_iic(void);
// interrupt process
voidIic_Srv(void);
voidInitializeIIC(void);
voidI2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char
count,unsigned char *data);I2Counter,//Background call to start master send and receive byte
I2CAddress
transfers
,MemAddress
,lock;
voidWriteByte(intaddr,unsigned char *data);
void ReadByte(intaddr,unsigned char *data);
void delay2(void);
unsigned charint main(void)
{
unsigned char Data=0;
InitializeIIC();
// Initialize IIC Interface
Data = 0x47; // Control byte, adds 12ma to segment current, dynamic mode, digits not
blanked
WriteByte(0x00,&Data);
// Read Hours from RTC
// Segment data for displaying
Data = 0x06;
data 1
WriteByte(0x01,&Data);
// Display in Digit 1
// Segment data for displaying
Data = 0x5b;
data 2
WriteByte(0x02,&Data);
Data = 0x4f;
WriteByte(0x03,&Data);
Data = 0x66;
WriteByte(0x04,&Data);
while(1);
// Display in Digit 2
// Segment data for displaying data 3
// Display in Digit 3
// Segment data for displaying data 4
// Display in Digit 4
}
void InitializeIIC(void)
{
lock = 0;
//Initilise the lock flag
VICVectCntl1 = 0x00000029;
//select a priority slot for a given interrupt
VICVectAddr1
=
(unsigned
//pass the address of the IRQ into the VIC
long)irq_iic;
slot
VICIntEnable = 0x00000200;
//enable interrupt
PINSEL0
|= 0x50;
//Switch GPIO to I2C pins
I2C0SCLH
= 0x104;
I2C0SCLL
= 0x104;
}
//Write given data in EEPROM, address(10bit) specified by addr
VoidWriteByte
(intaddr,unsignedchar*dat)
{
//write data to the I2C Memory
I2CTransferByte(0x70,addr,1,&data[
0]);
while(lock=
=1);
}
//Read data from EEPROM,addr-10bit EEPROM
address void ReadByte(intaddr,unsigned char *data)
{
I2CTransferByte(0x70,addr,0,&data[0]);
//set address to addr
I2CTransferByte(0x71,addr,1,&data[0]);
//read data from the I2C Memory
while(lock==1);
}void I2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char
count,unsigned char *data )
{
while(lock == 1)
//Wait for interrupt to signal end of I2C
Activity
{
;
}
Lock
= 1;
//Set I2C bus as active
//Place address and data in Globals to be used by the interrupt
I2CAddress = I2CAddr;
I2CData = data;
I2Counter
= count;
MemAddress = MemAddr;
I2C0CONCL
R
= 0x000000FF;
//Clear all I2C settings
I2C0CONSE
T
= 0x00000040;
//Enable the I2C interface
I2C0CONSE
T
= 0x00000020;
//Start condition
}
void Iic_Srv(void)
//I2C interrupt routine
{
}
}
}
switch (I2C0STAT)
//Read result code and switch to next
Action
{
case ( 0x08):
//Start bit
I2C0CONCLR=
0x20;
//Clear start bit
I2C0DAT
= I2CAddress;
//Send address and write bit
break;
case (0x18):
//Slave address+W, ACK
I2C0DAT
= MemAddress; //Write Memory start address to tx register
break;
case (0x20):
//Salve address +W, Not ACK
I2C0DAT
= I2CAddress;
//Resend address and write bi
break;
case (0x28):
if(I2Counter > 0)
//Data sent, Ack
{
I2Counter--;
I2C0DAT=
*I2CData
//Write data to tx register
;
I2CData++;
}Else
{
I2C0count
lock = 0;
= 0x10;
//Stop condition
//Signal end of I2C activity
}
break;
case (0x30)
I2C0DAT
:
//Data sent, NOT Ack
//Write data to tx register
//Receive byte conditions
= *I2CData;
break;
case (0x40) :
I2C0CONST=
break;
case (0x48) :
I2C0CONST=
//Slave Address +R, ACK
//Enable ACK for data byte
0x04;
//Slave Address +R, Not Ack
//Resend Start condition
0x20
;
break;
case (0x50)
:
if(--I2Counter>0)
{
*I2CData=
//Data Received, ACK
I2C0DA
T;
I2CData++;
}
else
{
*I2CData=
I2C0CONS
T
lock
}
I2C0DA
T;
= 0x10;
= 0;
//Stop condition
//Signal end of I2C activity
case (0x58):
I2C0CONSET = 0x20;
// Resend Start condition
break;
default :
break;
}
I2C0CONCLR = 0x08;
VICVectAddr = 0x00000000;
}
void gccmain()
{
}
//Clear I2C interrupt flag
//Clear interrupt inRESULT:
