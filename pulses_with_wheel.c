#include  <msp430x22x2.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned int round=0;
unsigned char output[10];
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

void main(void){
	WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer
     
        P4SEL=BIT7;
        TBCTL=TBSSEL_0+TBCLR;
        

	TACTL = TASSEL_1 + TACLR;  
        
        TACCTL0=CCIE;
        TACCR0=32768/10;
        TACTL|=MC_1;// Start Timer_A im up mode (Mode Control = 1)
        TBCTL|=MC_2;
        
        lcd_init(16);
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_puts( "round");
	
	
       __enable_interrupt();      // enable general interrupt (Interrupts global frei schalten)  
    
	__low_power_mode_0();      	// low power mode 0:  CPU wird gestoppt
  }
 #pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0 (void)
{  
  
  round=(TBR*5)/2;
  TBR=0;+
  uint2string(output,round);
  lcd_gotoxy(6,0);
  lcd_puts(output);

  
}

void Warteschleife(unsigned long Anzahl){
unsigned long i;    
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}