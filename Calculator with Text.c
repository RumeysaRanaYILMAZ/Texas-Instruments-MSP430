
#include <msp430x22x2.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);
void LCDWrite(unsigned char value);// Software Warteschleife

int main(void) {
   
  WDTCTL = WDTPW + WDTHOLD; 
   lcd_init(16);
   lcd_clear();
   lcd_gotoxy(0,0);
     
   unsigned char buttons;
   unsigned char value=1;
   
   P1DIR=0XFF;
   P2DIR=0X00;
   
   while(1){
   
     buttons=~P2IN;
     if(buttons&0x01){ 
       value=value/2;
         LCDWrite(value);
     }
     else if(buttons&0x02){ 
       value= value*2;  
      LCDWrite(value);
     }
     else if(buttons&0x04) {
       value--;
         LCDWrite(value);
     }
     else if(buttons&0x20){ 
       value++;
       LCDWrite(value);
       
     }
     
     P1OUT = ~value; 
     Warteschleife(100000);
    } 

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

