
#include <msp430x22x2.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);
void LCDWrite(unsigned char value);// Software Warteschleife
unsigned char value=1;
unsigned char buttons;
int main(void) {
   
  WDTCTL = WDTPW + WDTHOLD; 
 
   
   lcd_init(16);
   lcd_clear();
   lcd_gotoxy(0,0);
     
  
   P1OUT=0Xff;
   P1DIR=0Xff;
   P2IE=BIT5|BIT2|BIT1|BIT0;
   P2IFG=0;
     
   __enable_interrupt(); 
    
   while(1){
     __no_operation();
   }

}
  #pragma vector=PORT2_VECTOR
__interrupt void Port2ISR (void)
{ 
   
     buttons=P2IFG;
     if(buttons&0x01){ 
       value=value/2;
     }
     else if(buttons&0x02){ 
       value= value*2;  
     }
     else if(buttons&0x04) {
       value--;
     }
     else if(buttons&0x20){ 
       value++;
       
     }
     LCDWrite(value);
     P1OUT = ~value; 
     Warteschleife(100000);
     P2IFG=0;         	 
   
}
void Warteschleife(unsigned long Anzahl){
unsigned long i;    
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}

void LCDWrite(unsigned char value){
    unsigned char result[6];
    uint2string(result, value);
    lcd_gotoxy(0,0);
    lcd_puts(result);
}