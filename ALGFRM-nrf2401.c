/****************************************************************************/
void init_nrf24(void)
{
 unsigned int i, j, temp;

//set_CHID();
IOpin.modulepower=0;
delay_ms(10);
#bit tempbit=temp.7

    // nrf24 konfig�rasyon dizisinin kurulmas�
    //===================================================================
    //111-104 data bitleri 1 hatta en fazla CRC ve adres hari� 232 bittir
    config_setup[0] = 8*PAYLOADSIZE;

    //nrf24 �ipte ba��ms�z 2 adet al�c� kanal vard�r
    //103-64  data bitleri  Al�c� 2. kanal adresi
    config_setup[1] = 0;
    config_setup[2] = 0;
    config_setup[3] = 0;
    config_setup[4] = 0;
    config_setup[5] = 0; 

    //63-24   data bitleri Al�c� 1. kanal adresi 
    config_setup[6] = 0;
    config_setup[7] = 0;
    config_setup[8]=idH;//24 bit i�in
    config_setup[9]=chXORcod; // 1. kanal hat adresi
    config_setup[10]=idL; // 1. kanal hat adresi
   
    /*
    23: 0  adres bit say�si
    22: 1  adres bit say�si
    21: 0  adres bit say�si
    20: 0  adres bit say�si
    19: 0  adres bit say�si
    18: 0  adres bit say�si
    17: 1 16-Bit CRC
    16: 1 CRC Enabled

    15: 0 1 al�c� kanal (0 ise 1 al�c� kanal 1 ise 2 al�c� kanal)
    14: 1 ShockBurst Mode
    13: 1 1Mbps veri ileti�imi ( 0 ise 256 kps)
    12: 0 16 MHZ kristal
    11: 1 16 MHZ kristal
    10: 1 16 MHZ kristal
    9: 1 RF Output Power
    8: 1 RF Output Power

    7: 0 Kanal numaras�
    6: 0 Kanal numaras�
    5: 0 Kanal numaras�
    4: 0 Kanal numaras�
    3: 0 Kanal numaras�
    2: 1 Kanal numaras�
    1: 0 Kanal numaras�
    0: 0 G�nderme modu ( 0 ise g�nderme 1 ise alma)
    
*/
    //Data bits 23-16 Address width and CRC
    config_setup[11] = 0b01100011; //24 bit adres(COD) CRC 16 bit CRC enable
    //Data bits 15-8
    // 1. al�c� kanal shockburst mod 1Mbit veri 16 Mhz kristal 0dB g�� 1Mbit i�in 0x6F, 250Kbit i�in 0x4F
   config_setup[12] = 0x4F;
    //Data bits 7-0
    config_setup[13] = channel<<1;

IOpin.moduleCE=0;
IOpin.moduleCS=1;
delay_us(5);

    // nrf24 konfigurasyon verilerini y�kle
    for(i = 0 ; i < 14 ; i++)
    {
        temp = config_setup[i];
        
        for(j = 0 ; j < 8 ; j++)
        {   
            IOpin.moduleDATA=tempbit;
            IOpin.moduleCLK=1;
            IOpin.moduleCLK=1;
                        
            IOpin.moduleCLK=0;
            IOpin.moduleCLK=0;
        
            temp <<= 1;
        }
    }
    //Konfigurasyon ayarlar� CS nin d��en kenar�nda aktif hale gelir
    IOpin.moduleCE=0;
    IOpin.moduleCS=0;
}
/****************************************************************************/


