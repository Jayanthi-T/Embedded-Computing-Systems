PWM
#include "LPC214x.H"
// LPC214x definitions
#include "string.h"
voidInitializePWM(void);
voidDisplayPWMData(intdat);
voidDisplayLCD(char LineNumber,char *Message);
voidInitializeLCD();
voidConvertHextoBCD(unsigned int a);
int main (void)
{
intval=900;
InitializeLCD();
// Initialize LCD
DisplayLCD(0," PWM Testing ");
// Display Message
DisplayLCD(1,"PWM Data:0900 ");
InitializePWM();
// Initialize PWMIODIR0 &= 0xffffff7d;
while (1)
{
if((IOPIN0 & 0x02) == 0)
{
// Increment switch pressed
if((IOPIN0 & 0x02) == 0)
{
if(val> 50)
val -= 50;
// Decrement PWM value
ConvertHextoBCD(val);
PWMMR4 = val;// Set value to PWM 4 register
PWMMR5 = 950;
// Set value for PWM 5 register
PWMLER = 0x30;
// Latch the value
PWMTCR = 0x00000002;
// Reset counter and prescaler
PWMTCR = 0x00000009;
}
while((IOPIN0 & 0x02) == 0);
}
if((IOPIN0 & 0x80) == 0)
{ // Decrement
if((IOPIN0 & 0x80) == 0)
{
if(val<900)
val += 50;
ConvertHextoBCD(val);
PWMMR4 = val;
// Set value to PWM 4 register
PWMMR5 = 950;
// Set value for PWM 5 register
PWMLER = 0x30;// Latch the value
PWMTCR = 0x00000002;
// Reset counter and prescaler
PWMTCR = 0x00000009;
}
while((IOPIN0 & 0x80) == 0);
}
}
}
voidInitializePWM (void)
{
PINSEL1 = 0x00000400;
// Enable P0.21 - PWM5
PWMPR = 0x00000000;
// Load prescaler
PWMPCR = 0x00002020;
// PWM channel 5 output enabled, double edge
control
PWMMCR = 0x00010000;
// On match with timer reset the counter
PWMMR0 = 1000;
// set cycle rate to sixteen ticks
PWMMR4 = 900;
PWMMR5 = 950;
PWMLER = 0x30;
// enable shadow latch for match 5
PWMTCR = 0x00000002;
// Reset counter and prescaler
PWMTCR = 0x00000009;
// enable counter and PWM, release counter from
reset
}voidConvertHextoBCD(unsigned int a)
{
unsigned
char
t[20]="PWM
Data:0000"; t[9] = '0';
t[10] = a/100 +
'0'; a -= (a/100) *
100; t[11] = a/10
+ '0'; t[12] =
a%10
+ '0';
DisplayLCD(1,t)
;
}
void gccmain()
{
}


