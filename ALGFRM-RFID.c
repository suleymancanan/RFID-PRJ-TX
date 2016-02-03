#include <ALGFRM-RFID.h>
#include <string.h>
#zero_ram
#fill_rom 0x00

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)                       
#use fast_io(D)
#use fast_io(E)                   
#use fast_io(F)             
#use fast_io(G)


//---------- RFID -----------------------
#int_RDA
void rxuart1(void)
{
static char RFIDdata,cc=0;

RFIDdata=fgetc(RFID);

RFIDmsg[cc]=RFIDdata;
cc++;
 if(RFIDdata==0x0D)
 {
    cc=0;
    RFIDmsgready=1;
 }
}
//---------- GSM -----------------------
#int_RDA2
void rxuart2(void)
{
static char GSMdata,gg=0;
//enablecomLEDTimer=1;
GSMdata=fgetc(GSM);
GSMmsg[gg]=GSMdata;
//fputc(GSMdata,DEBUG);
//fprintf(DEBUG,"%c",GSMdata);
//fputc(GSMDATA,DEBUG);
gg++;
if(gg>23) gg=23;
 if((GSMdata==0x0D))
 {
    gg=0;
    GSMmsgready=1;
 }
}
//---------------------------------

#int_TIMER0
void  TIMER0_isr(void)
{
cpucounter++;

if(cpucounter<25)
{
IOpin.cpuLED=1;
}
else
{
IOpin.cpuLED=0;
}
if(cpucounter>=500)
cpucounter=0;

if(enablecomLEDTimer)
{
IOpin.comLED=1;
comLEDTimer++;
   if(comLEDTimer>=6)
   {
      comLEDTimer=0;
      enablecomLEDTimer=0;
      IOpin.comLED=0;
   }
}

set_timer0(5);
clear_interrupt(int_timer0);
}
//-----------------------------------------------------------------------------
void init_prog(void)
{
setup_wdt(WDT_OFF);
setup_adc_ports(NO_ANALOGS|VSS_VDD);
setup_adc(ADC_OFF);
setup_psp(PSP_DISABLED);                                                
setup_spi(SPI_SS_DISABLED);
setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64|RTCC_8_BIT);// TIMER0
setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DISABLED,0,1);
setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
setup_comparator(NC_NC_NC_NC);                                           
setup_vref(FALSE);
setup_low_volt_detect(FALSE);              
setup_oscillator(OSC_16MHZ);                                        

set_tris_a(0x00);//
set_tris_b(0xFF); //FF
set_tris_c(0x94);//94
set_tris_d(0xFF); //02                                     
set_tris_e(0xF0);  //f0   
set_tris_f(0xFF);//ff
set_tris_g(0x04); //04

output_a(0x00);
output_b(0x00);
output_c(0x00);
output_d(0x00);
output_e(0x00);
output_f(0x00);
output_g(0x00);

}

void text_mode(void)
{
fprintf(GSM,"AT+CMGF=1\r");
delay_ms(2000);
}
void dial_call(void)
{
fprintf(GSM,"ATD05336831199;\r");
//fprintf(GSM,"%s\r",callnumber);// dial call
}
//------------------------------------------------------------------------------
void main(void)
{
   unsigned int8 i;
   unsigned int8 smsmessage[64];
   //unsigned int8 *too;
   //unsigned int8 *smsmessage;

   init_prog();
   
EXT_INT_EDGE(2,L_TO_H);
disable_interrupts(INT_EXT2);
enable_interrupts(INT_TIMER0);
enable_interrupts(INT_RDA);
enable_interrupts(INT_RDA2);
clear_interrupt(int_timer0);
//clear_interrupt(int_RDA);
//clear_interrupt(int_RDA2);
enable_interrupts(GLOBAL);


IOpin.GSMpower=GSMON;
IOpin.RFIDpower=RFIDON;

delay_ms(3000);
//IOpin.GSMpower=GSMON;
//IOpin.RFIDpower=RFIDON;

 fprintf(RFID,"SRA\r");

 fputs("AT+CMGD=1\r",GSM);
 delay_ms(1000);
 text_mode();
 delay_ms(1000);
 
 
for(;;)
{
   
   if(RFIDmsgready)
   {
      //fprintf(DEBUG,"RFI system OK");
      fputs(RFIDmsg,DEBUG);
      RFIDmsgready=0;
      
      IOpin.GSMpower=GSMON;
      delay_ms(10000);
      fprintf(GSM,"%s",ATCMGS);
   fputc(34,GSM);
   fprintf(GSM,"%s",phonenumber);
   fputc(34,GSM);
   fputc(13,GSM);
   delay_ms(200);
   fprintf(GSM,"%s\r",RFIDmsg);
   fprintf(GSM,"Bunu becerdim bilgin olsun");
   delay_ms(200);
   fputc(0x1A,GSM);
   delay_ms(10000);
   //IOpin.GSMpower=GSMOFF;
   //IOpin.RFIDpower=RFIDOFF;
   
   }
   
   
   /*
   do{
   
   }
   while(!IOpin.Intswitch);
    */ 
   /*
   fprintf(GSM,"%s",ATCMGS);
   fputc(34,GSM);
   fprintf(GSM,"%s",phonenumber);
   fputc(34,GSM);
   fputc(13,GSM);
   delay_ms(200);
   fprintf(GSM,"ALGIFARM RFID system OK\r");
   delay_ms(200);
   fputc(0x1A,GSM);
   delay_ms(200);
   //fputs(smsmessage,GSM);
   */
   
   /*
   delay_ms(100);
   fprintf(GSM,"ALGIFARM RFID system");
   delay_ms(100);
   fputc(0x1A,GSM);
   */
   
   /*
   for(i=0;i<16;i++)
   fputc(callnumber[i],GSM);*/
  
 /*  
   if(GSMmsgready)
   {
      //fprintf(DEBUG,"%s\r\n",GSMmsg);
      enablecomLEDTimer=1;
      GSMmsgready=0;
   }
*/
//delay_ms(1000);
//fputs("DEBUG port OK",DEBUG);

//fprintf(DEBUG,"DEBUG port OK\r\n");
//fprintf(GSM,"GSM port OK\r\n");
//fprintf(RFID,"RFID port OK\r\n");

/*
   for(i=0;i<24;i++)
   {
      RFIDmsg[i]=0x00;
      GSMmsg[i]=0x00;
   }
 */  
}
}

