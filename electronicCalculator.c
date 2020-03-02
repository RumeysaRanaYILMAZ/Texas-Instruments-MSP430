
#include <msp430x22x2.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

int main(void) {
   
  WDTCTL = WDTPW + WDTHOLD; 
   unsigned char buttons;
   unsigned char value=1;
   P1DIR=0XFF;
   P2DIR=0X00;
   while(1){
   
     buttons=~P2IN;
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
     P1OUT = ~value;
     Warteschleife(100000);
     
     
} 



}void Warteschleife(unsigned long Anzahl){
unsigned long i;    
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
