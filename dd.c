
#include <18F25J50.h> 
#device ADC=10 

#FUSES HSPLL, PLL2, NOXINST, NOCPUDIV, NOFCMEN, NOIESO, NOIOL1WAY, NOWDT 
#use delay(clock=48MHz) 

#pin_select  U2TX=PIN_B2 
#pin_select  U2RX=PIN_B3 

#use rs232(uart1,baud=9600, ERRORS, STREAM=DATA1)      
#use rs232(uart2, baud=9600, ERRORS, STREAM=DATA2) 

void main() 
{ 
   setup_adc_ports(NO_ANALOGS); 
   output_drive(PIN_B2); //This may be needed depending on compiler version 
   delay_ms(100); 
   //most RS232 level generator chips _need_ a few mSec after power on 
   fprintf(DATA1,"\r\n UART1 TEST \r\n"); 
   fprintf(DATA2,"\r\n UART2 TEST \r\n"); 
    
   while(true) 
      ; 
} //Main 
