KEYBOARD
/**********************************************
/* Matrix Keyboard with LCD Display
/*********************************************/
#include "LPC214x.H"
// LPC214x definitions
extern void irq_T0(void);
// Interrupt process
void T0_Srv(void);
void InitializeTIMER0(void);
void InitializeKeyboard(void);
void ScanKeyboard(void);
unsigned char ReadColumn(void);
void SetRow(unsigned char dat);
void DisplayLCD(char LineNumber,char *Message);
char KeyboardFlag;
unsigned char KeyboardCode=0;
char Counter=0,ReleaseFlag=0,StatusFlag=0,IdentificationFlag=0;
int main(void)
{
KeyboardFlag =0;
//Clear keyboard flag
InitializeLCD();
IODIR0 |= 0x00078000;
//Initialize Port lines for keyboard
InitializeTIMER0();
//Initialize TIMER0, Keyboard scan timer
DisplayLCD(0,"Matrix Keyboard ");
DisplayLCD(1,"Key Pressed: ");
while(1)
{
if(KeyboardFlag ==1)
//wait for key press
{
DisplayLCD2Digit(1,12,KeyboardCode);
KeyboardFlag=0;
//reset keyboard flag
}
}
}
//Scan keyboard
void ScanKeyboard(void)
{
unsigned char a,b,c;
unsigned char f;
if(ReleaseFlag == 1)
{
//debounce time for release
Counter++;
if(Counter ==10)
{
ReleaseFlag = 0;
}
return;
}
if(StatusFlag ==1)
{
if(IdentificationFlag == 1)
{
//Wait for key ReleaseSetRow(0x00);
if(ReadColumn() == 0x0f)
{
//No key pressed
Counter
ReleaseFlag
IdentificationFlag
StatusFlag
}
return;
//Check the keyboard status
= 0;
= 1;
= 0;
= 0;
}
else
{
Counter++;
if(Counter == 10)
{
//Check key press
KeyboardCode = 0;
SetRow(0x00);
//Set all rows to 0
if(ReadColumn() != 0x0f)
//Read column levels
{
//any one key pressed
for(a=0;a<4;a++)
{
//Row Setting
f = ~(0x01 << a);
//set one row to 0
SetRow(f);
b = ReadColumn();
//read column levels
for(c=0;c<4;c++)
{ //Column checking
f = 0x01 << c;
if(( b & f) == 0)
{
//Pressed Key identified
IdentificationFlag
= 1;
StatusFlag
= 1;
KeyboardFlag=1;
KeyboardCode &= 0x0f;
return;
}
KeyboardCode++;
}
}
}
IdentificationFlag = 0;
StatusFlag
return;
= 0;
}
else
{
return;
}
}
}
SetRow(0x00);
if(ReadColumn() != 0x0f)
{
// key press detected
Counter=0;
StatusFlag=1;
IdentificationFlag=0;
}
//Check for any key press}
/* Sets the given data to Row */
void SetRow(unsigned char dat)
{
if(dat & 0x01)
IOSET0 = 0x00008000;
else
IOCLR0 = 0x00008000;
if(dat & 0x02)
IOSET0 = 0x00010000;
else
IOCLR0 = 0x00010000;
if(dat & 0x04)
IOSET0 = 0x00020000;
else
IOCLR0 = 0x00020000;
if(dat & 0x08)
IOSET0 = 0x00040000;
else
IOCLR0 = 0x00040000;
}
/* Reads the Column status and returns the same */
unsigned char ReadColumn(void)
{
unsigned char a=0;
a = (IOPIN0>>11) & 0x0f;
return(a);
}
//Initialise timer0 used in keyboard scanning
void InitializeTIMER0(void)
{
//for 1msec delay
VPBDIV
= 0x00000002;
T0PR
T0TCR
T0MCR
T0MR0
T0TCR
= 0x0000012B;
= 0x00000002;
= 0x00000003;
= 0x00000064;
= 0x00000001;
//Configure the VPB divider
//CCLK/2 = PCLK = 30MHz
//Load prescaler = 300, 30MHz/300=100KHz
//Reset counter and prescaler
//On match reset the counter and generate an interrupt
//Set the cycle time, 100KHZ/100 = 1KHZ = 1ms
//enable timer
VICVectAddr4 = (unsigned long)irq_T0;//Set the timer ISR vector address
VICVectCntl4 = 0x00000024;
//Set channel
VICIntEnable |= 0x00000010;
//Enable the interrupt
}
/* Timer0 interrupt service routine */
void T0_Srv(void)
{
ScanKeyboard();
T0IR
|= 0x00000001;
VICVectAddr = 0x00000000;
}
//Check and update keyboard status
//Clear match 0 interrupt
//Dummy write to signal end of interrupt
