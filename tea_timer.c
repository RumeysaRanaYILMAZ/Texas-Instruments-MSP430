#include  <msp430x22x2.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned int timer = 10;		
unsigned char output[3];
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

void main(void){
	WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

	TACTL = TASSEL_1 + TACLR;  // Beschreiben des TimerA-Controlregisters, es werden zwei Bits gesetzt:
		//   - TimerA Source Select = 0 (Eingangstakt ist AClock)
		//   - Clear TimerA-Register    (Zählregister auf 0 setzen)
        		// Timer startet noch nicht

	TACCTL0 = CCIE;      		// Capture/Compare-Unit0 Control-Register beschreiben:
	
	TACCR0 = 32768;           	// Capture/Compare-Register 0 mit Zählwert belegen
	P1SEL |= 0x00;             		// P1 hat Standard-IO-Funktion
	P1DIR |= 0x01;             		// P1.0 ist Ausgang
	P2DIR |= BIT4;    		
  
	lcd_init(16);
	lcd_clear();
	lcd_gotoxy(0, 0);
	
  
	TACTL |= MC_1;             // Start Timer_A im up mode (Mode Control = 1)
	__enable_interrupt();      // enable general interrupt (Interrupts global frei schalten)  
    
	__low_power_mode_0();      	// low power mode 0:  CPU wird gestoppt
  }
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void){
	P1OUT ^= 0x01;  
        lcd_clear(); 
	lcd_gotoxy(0,0);
	uint2string(output, timer); 
	lcd_puts(output);
  
	if (timer == 0){ 	   
		P2OUT |= BIT4;
                 timer = 11;
                 lcd_clear();
             
                 lcd_puts( " TIME OVER");
                for (int i = 0; i< 2500; i++){ 
			P2OUT ^= BIT4; 
                        Warteschleife(200);
                }
                       
			}
		
      else{
		timer--;
	}
}
void Warteschleife(unsigned long Anzahl){
unsigned long i;    
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
