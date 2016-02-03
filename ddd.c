#include <ALGFRM-RFID.h>
#zero_ram
#fill_rom 0x00

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)                       
#use fast_io(D)
#use fast_io(E)                   
#use fast_io(F)             
#use fast_io(G)


//==============================================================================
#int_RDA
void  RDA_isr(void) 
{
static char data,cc=0;

data=getc();

RFIDmsg[cc]=data;
cc++;
 if(data==0x0D)
 {
    cc=0;
    RFIDmsgready=1;
 }
}
//---------- GSM -----------------------
#int_RDA2
void  RDA_isr2(void) 
{
static char GSMdata,cc=0;

GSMdata=getc();

GSMmsg[cc]=GSMdata;
cc++;
 if(GSMdata==0x0D)
 {
    cc=0;
    GSMmsgready=1;
 }
}
//---------------------------------
#int_TIMER0
void  TIMER0_isr(void)
{
cpucounter++;

if(cpucounter<100)
{
IOpin.cpuLED=1;
IOpin.comLED=1;
}
else
{
IOpin.cpuLED=0;
IOpin.comLED=0;
}
if(cpucounter>=1000)
cpucounter=0;

set_timer0(5);
clear_interrupt(int_timer0);
}
//=============================================================================
void init_prog(void)
{
setup_wdt(WDT_OFF);
setup_adc_ports(NO_ANALOGS|VSS_VDD);
setup_adc(ADC_OFF);
setup_psp(PSP_DISABLED);                                                
setup_spi(SPI_SS_DISABLED);
setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16|RTCC_8_BIT);// TIMER0
setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DISABLED,0,1);
setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
setup_comparator(NC_NC_NC_NC);                                           
setup_vref(FALSE);
setup_low_volt_detect(FALSE);              
setup_oscillator(OSC_32MHZ);                                        

set_tris_a(0xFF);//7F
set_tris_b(0xFF); //FF
set_tris_c(0x94);//94
set_tris_d(0xFF); //02                                     
set_tris_e(0xF0);  //f0   
set_tris_f(0xFF);//ff
set_tris_g(0xFC); //04
output_a(0x00);
output_b(0x00);
output_c(0x00);
output_d(0x00);
output_e(0x00);
output_f(0x00);
output_g(0x00);
}
//------------------------------------------------------------------------------
void main(void)
{
   unsigned int8 i;
   init_prog();

EXT_INT_EDGE(2,L_TO_H);
disable_interrupts(INT_EXT2);
enable_interrupts(INT_TIMER0);
enable_interrupts(INT_RDA);
enable_interrupts(INT_RDA2);
enable_interrupts(GLOBAL);
fprintf(RFID,"SRA\r");
for(i=0;i<16;i++)
   {
   RFIDmsg[i]=' ';
   fprintf(DEBUG,"%d\r\n",i);
   }
   
    for(;;)
 {

 IOpin.RFIDpower=0;
   if(RFIDmsgready)
   {
fprintf(DEBUG,"%s\r\n",RFIDmsg);
RFIDmsgready=0;
   }
   if(GSMmsgready)
   {
   fprintf(DEBUG,"%s",GSMmsg);
   GSMmsgready=0;
   }
   fprintf(GSM,"AT\r");
   delay_ms(3000);
   fprintf(DEBUG,"ALGIFARM\r\n");
}   
}
