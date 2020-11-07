EEPROM
/**************************************************
/* Read and Display IIC RTC - PCF8583
/* (connected to IIC bus of controller)
/* in a LCD Display
/*************************************************/
#include "LPC214x.h"
// LPC21xx definitions 
extern void irq_iic(void); 
// interrupt process 
void Iic_Srv(void);  
void InitializeIIC(void);
void I2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char count,unsigned char *data);
//Background call to start master send and receive byte transfers
void WriteByte(int addr,unsigned char *data);
void ReadByte(int addr,unsigned char *data);
void delay2(void);
unsigned char *I2CData,
I2Counter,
I2CAddress,
MemAddress,
lock;
int main(void)
{
unsigned char Data=0, Address;
InitializeLCD();
InitializeIIC();
DisplayLCD(0," EEPROM DEMO ");
DisplayLCD(1,"ADDR: Data: ");
Data = 0x12;
Address = 0x00;
WriteByte(Address,&Data);
Data = 0;
ReadByte(Address,&Data);
DisplayLCD2Digit(1,5,Address);
DisplayLCD2Digit(1,14,Data);
while(1);
}
void InitializeIIC(void)
{
lock = 0;
// Initialize LCD
// Initialize IIC Interface
// Display message
// Write Data to EEPROM
// Read Data from EEPROM
// Display
//Initilise the lock flag
VICVectCntl1 = 0x00000029;
//select a priority slot for a given interrupt
VICVectAddr1 = (unsigned long)irq_iic;
//pass the address of the IRQ into the VIC slot
VICIntEnable = 0x00000200;
//enable interrupt
PINSEL0
|= 0x50;
//Switch GPIO to I2C pins
I2C0SCLH
= 0x104;
//Set bit rate 60Mhz/VPBDIV+SCLH+SCLL = 60/2+260+260 = 57.6Khz
I2C0SCLL
= 0x104;
}//Write given data in EEPROM, address(10bit) specified by addr
void WriteByte(int addr,unsigned char *data)
{
I2CTransferByte(0xAc,addr,1,&data[0]);
//write data to the I2C Memory
while(lock==1);
delay2();
}
//Read data from EEPROM,addr-10bit EEPROM address
void ReadByte(int addr,unsigned char *data)
{
I2CTransferByte(0xAc,addr,0,&data[0]);
//set address to addr
I2CTransferByte(0xAd,addr,1,&data[0]);
//read data from the I2C Memory
while(lock==1);
}
void I2CTransferByte(unsigned int I2CAddr,unsigned char MemAddr,unsigned char count,unsigned char *data )
{
while(lock == 1)
//Wait for interrupt to signal end of I2C activity
{
;
}
lock
= 1;
//Set I2C bus as active
//Place address and data in Globals to be used by the interrupt
I2CAddress = I2CAddr;
I2CData = data;
I2Counter
= count;
MemAddress = MemAddr;
I2C0CONCLR = 0x000000FF;
//Clear all I2C settings
I2C0CONSET = 0x00000040;
//Enable the I2C interface
I2C0CONSET = 0x00000020;
//Start condition
}
void Iic_Srv(void)
//I2C interrupt routine
{
switch (I2C0STAT)
//Read result code and switch to next action
{
// Start and Send byte conditions
case ( 0x08):
//Start bit
I2C0CONCLR = 0x20;
//Clear start bit
I2C0DAT
= I2CAddress;
//Send address and write bit
break;
case (0x18):
//Slave address+W, ACK
I2C0DAT
= MemAddress;
//Write Memory start address to tx register
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
I2C0DAT
= *I2CData;
//Write data to tx register
I2CData++;}
else
{
I2C0CONSET = 0x10; //Stop condition
lock = 0;
//Signal end of I2C activity
}
break;
case (0x30)
:
I2C0DAT
= *I2CData;
break;
//Receive byte conditions
case (0x40) :
I2C0CONSET = 0x04;
break;
case (0x48) :
I2C0CONSET = 0x20;
break;
case (0x50) :
if(--I2Counter>0)
{
*I2CData
= I2C0DAT;
I2CData++;
}
else
{
*I2CData
= I2C0DAT;
I2C0CONSET = 0x10;
lock
= 0;
}
break;
case (0x58):
I2C0CONSET = 0x20;
break;
default :
break;
}
I2C0CONCLR = 0x08;
VICVectAddr = 0x00000000;
}
//Small delay
void delay2(void)
{
long int i;
i=0xffff;
while(i)
{
i--;
}
}
