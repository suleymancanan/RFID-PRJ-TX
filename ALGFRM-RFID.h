#include <18F6310.h>
#device adc=8
#FUSES NOWDT
#FUSES WDT64                    
#FUSES INTRC_IO                  //High speed osc with HW enabled 4X PLL
#FUSES NOBROWNOUT                //Reset when brownout detected
#FUSES PUT                       //No Power Up Timer
#FUSES NOSTVREN                  //Stack full/underflow will cause reset
#FUSES NODEBUG                   //No Debug mode for ICD
#FUSES NOIESO                    //Internal External Switch Over mode enabled
#FUSES NOFCMEN                   //Fail-safe clock monitor enabled
#FUSES NOXINST                   //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PROTECT                   //Code not protected from reading
#FUSES NOLPT1OSC                 //Timer1 configured for low-power operation
#FUSES NOMCLR                    //Master Clear pin disabled                  


#use delay(clock=16000000)
//#use rs232(UART1,BAUD=9600, BITS=8, parity=N,xmit=PIN_C6,rcv=PIN_C7,ERRORS, STREAM=RFID)      
#use rs232(UART1,BAUD=9600, BITS=8, parity=N,ERRORS, STREAM=RFID)      
#use rs232(UART2, BAUD=9600, BITS=8, parity=N,ERRORS, STREAM=GSM) 
#use rs232(stream=DEBUG,baud=9600,parity=N,xmit=PIN_C1,rcv=PIN_C2,bits=8, ERRORS) 
//#use i2c(Master,Fast=400000,sda=PIN_F3,scl=PIN_F2,force_sw)

struct IOpins {
           BOOLEAN pinA0;       //A0  0          
           BOOLEAN RFIDpower;        //A1  0            
           BOOLEAN GSMpower;       //A2  0
           BOOLEAN pinA3;    //A3  0
           BOOLEAN pinA4;    //A4  0
           BOOLEAN pinA5;         //A5  0
           BOOLEAN pinA6;         //A6  0
           BOOLEAN unused1;    //A7  0
           BOOLEAN moduleDR1;     //B0  0
           BOOLEAN Intswitch;      //B1  0        
           BOOLEAN pinB2;      //B2  1    
           BOOLEAN pinB3;       //B3  0 
           BOOLEAN pinB4;       //B4  0
           BOOLEAN pinB5;     //B5  0
           BOOLEAN pgmCLK;     //B6  0
           BOOLEAN pgmDATA;        //B7  0  
           
           BOOLEAN eepromWP;     //C0  0
           BOOLEAN debugTX;     //C1  0
           BOOLEAN debugRX;       //C2  0 
           BOOLEAN SCL;       //C3  0
           BOOLEAN SDA;    //C4  0
           BOOLEAN comLED;        //C5  0   
           BOOLEAN rfIDTx;    //C6  0
           BOOLEAN rfIDRx;    //C7  1
           
           BOOLEAN moduleCLK;      //D0  0
           BOOLEAN moduleDATA;        //D1  0
           BOOLEAN moduleCS;     //D2  0
           BOOLEAN moduleCE;      //D3  0
           BOOLEAN modulePWRUP;        //D4  0
           BOOLEAN moduleCPS;        //D5  0
           BOOLEAN moduleCTX;      //D6  0
           BOOLEAN moduleCSD;        //D7  0  
           BOOLEAN modulePOWER;   //E0  0      
           BOOLEAN rfIDPOWER_;            //E1  0       
           BOOLEAN gsmPOWER_; //E2  0 
           BOOLEAN buzzer;            //E3  0
           BOOLEAN pinE4; //E4  0
           BOOLEAN pinE5;        //E5  0
           BOOLEAN pinE6;        //E6  0
           BOOLEAN pinE7;            //E7  0  
           BOOLEAN pinF0;        //F0  0      
           BOOLEAN pinF1;            //F1  0       
           BOOLEAN pinF2;       //F2  0 
           BOOLEAN pinF3;       //F3  1
           BOOLEAN pinF4;      //F4  1
           BOOLEAN pinF5;            //F5  0
           BOOLEAN pinF6;     //F6  0
           BOOLEAN pinF7;     //F7 
           BOOLEAN cpuLED;    //G0  0    
           BOOLEAN gsmTX;     //G1  0    
           BOOLEAN gsmRX;          //G2  0 
           BOOLEAN pinG3;          //G3  0                     
           BOOLEAN pinG4;    //G4  0  
           //BOOLEAN unused1;       //G5
           //BOOLEAN unused2;       //G6
           //BOOLEAN unused3;       //G7
} IOpin;
#byte IOpin=0xF80

        
#define ADDRESSSIZE 3
#define PAYLOADSIZE 16           
unsigned char channel;
unsigned char idH,idL,chXORcod;
unsigned char RFIDmsg[24],RFIDmsg_[17];
unsigned char GSMmsg[24];
short RFIDmsgready,GSMmsgready,txmode=1;
unsigned char databit;
#bit tempdatabit=databit.7
unsigned char TXBuffer[PAYLOADSIZE];
unsigned char RXBuffer[PAYLOADSIZE];
unsigned char nrfaddress[ADDRESSSIZE];
unsigned int8 config_setup[14];
char ShiftReg;
#bit ShiftRegLSB=ShiftReg.0
unsigned int16 cpucounter,lcdlightcounter;
unsigned char sec;
short lcdlightenable=0;

short enablecomLEDTimer=0;
unsigned int8 comLEDTimer=0;

//unsigned int8 phonenumber[12]="05336831199";
unsigned int8 phonenumber[12]="05549153639";
unsigned int8 callnumber[16]="ATD05336831199;";
unsigned int8 ATCMGS[9]="AT+CMGS=";
//unsigned int8 *ATCMGS="AT+CMGS=";
unsigned int8 quote[1]=34;
unsigned int8 cr=13;

#define GSMOFF 1
#define GSMON 0
#define RFIDOFF 1
#define RFIDON 0
