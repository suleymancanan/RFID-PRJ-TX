 for(;;)
   {
      //lcd_backlight=ON;
      if(msgrdy)
      {
         lcd_backlight=ON;
         //IOpin.errorLED=1;
         set_CHID();
         init_nrf24();
         for(i=0;i<100;i++)
         {
            IOpin.buzzer=0;
            delay_us(500);
            IOpin.buzzer=1;
            delay_us(500);
         }
         
          lcd_putc('\f');
          lcd_gotoxy(1,1);
          printf(lcd_putc,"ID:");
         for(i=0;i<16;i++)
         {
            lcd_gotoxy(1+i,2);
            printf(lcd_putc,"%c",RFIDmsg[i]);
         }
         //IOpin.errorLED=0;
         delay_ms(1000);
         lcd_gotoxy(1,2);
         lcd_putc('\f');
         get_date_time();
          
          for(i=0;i<17;i++) RFIDmsg_[i]=RFIDmsg[i]-48;
               TXBuffer[0]=0;
               TXBuffer[1]=hr;
               TXBuffer[2]=min;
               TXBuffer[3]=dt;
               TXBuffer[4]=mt;
               TXBuffer[5]=yr;
               TXBuffer[6]=RFIDmsg_[0];// country code
               TXBuffer[7]=RFIDmsg_[1];// country code
               TXBuffer[8]=RFIDmsg_[2];// country code
               /*
               TXBUffer[9]=RFIDmsg_[4];
               TXBuffer[10]=RFIDmsg_[5];
               TXBuffer[11]=RFIDmsg_[6];
               TXBuffer[12]=RFIDmsg_[7];
               TXBuffer[13]=RFIDmsg_[8];
               TXBuffer[14]=RFIDmsg_[9];
               TXBuffer[15]=RFIDmsg_[10];
               lcd_putc('\f');
              
              lcd_gotoxy(1,2);
              printf(lcd_putc,"%d",RFIDmsg_[8]);
              
              */
              /*
              for(i=0;i<10;i++)
         {
            lcd_gotoxy(1+i,2);
            
            if(i!=3)
               printf(lcd_putc,"%d",RFIDmsg_[i]);
            else
               printf(lcd_putc,"%c",RFIDmsg[i]);
         }*/
//         delay_ms(2000);
               
               tmpbcd=(RFIDmsg_[4]<<4)|RFIDmsg_[5];
               TXBuffer[9]=tmpbcd;//ID
               
               tmpbcd=(RFIDmsg_[6]<<4)|RFIDmsg_[7];
               TXBuffer[10]=tmpbcd;
               
               tmpbcd=(RFIDmsg_[8]<<4)|RFIDmsg_[9];
               TXBuffer[11]=tmpbcd;
               
               tmpbcd=(RFIDmsg_[10]<<4)|RFIDmsg_[11];
               TXBuffer[12]=tmpbcd;
               
               tmpbcd=(RFIDmsg_[12]<<4)|RFIDmsg_[13];
               TXBuffer[13]=tmpbcd;
               
               tmpbcd=(RFIDmsg_[14]<<4)|RFIDmsg_[15];
               TXBuffer[14]=tmpbcd;
               TXBUffer[15]=0;
               
              
         /*      
               for(i=9;i<15;i++)
         {
            //lcd_gotoxy(1+i*2,2);
            printf(lcd_putc,"%0x",TXBuffer[i]);
            delay_ms(500);
         }
               delay_ms(15000);
               */
               lcd_putc('\f');
               transmit_data();
               msgrdy=0;
               lcdlightenable=1;
}
               get_date_time();
               //printf("SRD\r");
               if(s!=sec)
               {
               show_parameters();
               //printf("SRA\r");
               //delay_ms();
               }
               
               
               //lcd_backlight=OFF;
               /*
               for(i=0;i<PAYLOADSIZE;i++)
               TXBuffer[i]=i;
               transmit_data();
               */
         
   }
   //==============================================================================
/*
unsigned int16 calculate_crc16(unsigned int16 old_crc, unsigned int8 data)
{ 
unsigned int16 crc16bit;
unsigned int16 x; 

x = make8(old_crc,1) ^ data;  //x = ((old_crc>>8) ^ data) & 0xff; 
x ^= x>>4; 
crc16bit = (old_crc << 8) ^ (x << 12) ^ (x <<5) ^ x; 
return crc16bit; 
}
*/
//==============================================================================
/*
void transmit_data(void)
{
int8 a,b;

iopin.modulePWRUP=1;

delay_ms(3);

IOpin.moduleCE=1;//
IOpin.moduleCS=0;//TXRX Aktif nrf24'e veri yüklenebilir

delay_us(5);

for(a=0;a<ADDRESSSIZE;a++){
databit=nrfaddress[a];

   for(b=0;b<8;b++)
   {
      IOpin.moduleDATA=tempdatabit;
         IOpin.moduleCLK=1;
         IOpin.moduleCLK=1;
           
         IOpin.moduleCLK=0;
         IOpin.moduleCLK=0;
      databit=databit<<1;
   }
}

for(a=0;a<PAYLOADSIZE;a++){
databit=TXBuffer[a];

   for(b=0;b<8;b++)
   {
      IOpin.moduleDATA=tempdatabit;
      IOpin.moduleCLK=1;
      IOpin.moduleCLK=1;
      
      IOpin.moduleCLK=0;
      IOpin.moduleCLK=0;
      databit=databit<<1;
   }
}

IOpin.modulepower=1; //Yükselteciyi aktive et
delay_us(5);
IOpin.moduleDATA=0;
IOpin.moduleCE=0; // Veri iletimine başla
delay_us(2200);
IOpin.modulepower=0;// Yükselticiyi kapat
IOpin.modulePWRUP=0;
delay_us(13000);
//delay_ms(100);
}
*/
/*
if(lcdlightenable)
{
lcd_backlight=ON;
lcdlightcounter++;
   if(lcdlightcounter>=3000)
   {
      lcdlightenable=0;
      lcd_backlight=OFF;
      lcdlightcounter=0;
   }
}
*/
//lcd_gotoxy(1,1);
   //printf(lcd_putc,"ID:");
   //setTime( hr,min,s,am_pm,hr_format);
   //setDate(dy, dt, mt, yr);   
   /*   
   txmode=1;
   
   get_date_time();
   show_parameters();
   set_CHID();
   init_nrf24();
   enable_interrupts(GLOBAL);
  lcdlightenable=1;
  //printf("SRD\r");
  printf("SRA\r");
  delay_ms(5000);
  */

