SERIAL PORT
#include "LPC214x.H"
// LPC214x definitions
voidInitializeSerialPort(void);
voidSendMessage(char *Message);
voidSendByteSerially(unsigned char a);
unsigned char ReadByteSerially(void);
extern char KeyboardFlag;
extern unsigned char KeyboardCode;
int main(void)
{
unsigned char a;
InitializeSerialPort();
//Initialize Serial port
SendMessage("NXP LPC 2148 ARM Evaluation System\r\n"); //Send message though
serial port
SendMessage("Message at baud 9600.\r\n\r\n");
IODIR0 |= 0x00078000;
//Initialize Port lines for keyboard
KeyboardFlag =0;
//Clear keyboard flag
InitializeLCD();
DisplayLCD(0,"Serial Port Test ");
DisplayLCD(1,"Received Char: ");
InitializeTIMER0();
//Initialize TIMER0, Keyboard scan
timer
while(1)
{
a = ReadByteSerially();
// Read a Serial port
DisplayCharacter(1,14,a);
// Display the Character
}
}// Sends Message
voidSendMessage(char *Message)
do
{
SendByteSerially(*Message);
//Send a byte of data through serial port
Message++;
//Increment pointer
}
while(*Message != 0);
} // Sends Byte
voidSendByteSerially(unsigned char a)
{
while (!(U1LSR & 0x20));
U1THR = a;
}// Reads Byte
unsigned char ReadByteSerially(void)
{
while (!(U1LSR & 0x01))
{
if(KeyboardFlag ==1)
// Wait for key press
{
if(KeyboardCode< 0x0a)
{
KeyboardCode += 0x30;
}else
{
KeyboardCode += 0x37;
}
SendByteSerially(KeyboardCode);
KeyboardFlag=0;
// Reset keyboard flag
}
}
return (U1RBR);
}// Serial Port Initialization
voidInitializeSerialPort(void)
{
PINSEL0 = 0x00050000;
// P0.8 to P0.9 Pin function select
U1LCR = 0x83;
// 8 bits, no Parity, 1 Stop bit
U1DLL = 97;
// 9600 Baud Rate @ 15MHz VPB Clock
U1LCR = 0x03;
// DLAB = 0
}
void gccmain()
{
}


