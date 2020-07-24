#line 1 "E:/Documentos/4to Automatica/FlipDisc/@@MI PROYECTO/FIRM_TEST/MyProject.c"
#line 6 "E:/Documentos/4to Automatica/FlipDisc/@@MI PROYECTO/FIRM_TEST/MyProject.c"
unsigned char readUSB[64] absolute 0x500;
unsigned char writeUSB[64] absolute 0x540;
unsigned char reservUSB[256] absolute 0x400;


sbit EN_M0 at RA0_bit;
sbit EN_M1 at RA1_bit;
sbit EN_M2 at RA2_bit;
sbit EN_M3 at RA3_bit;
sbit EN_M4 at RA4_bit;
sbit EN_M5 at RA5_bit;

sbit A_0 at RB1_bit;
sbit A_1 at RB2_bit;
sbit A_2 at RB3_bit;
sbit B_0 at RB4_bit;
sbit B_1 at RB5_bit;
sbit DATO at RB6_bit;

sbit D0 at RD0_bit;
sbit D1 at RD1_bit;
sbit D2 at RD2_bit;
sbit EN_ON_OFF at RD3_bit;
sbit EN_UP_DOWN at RD4_bit;

sbit D_minus at RC4_bit;
sbit D_plus at RC6_bit;
sbit L_USB at RC6_bit;
sbit L_working at RC7_bit;
sbit KBDDATA at RE0_bit;

void config_PIC()
{
 ADCON1 = 0x0F;
 TRISA = 0x00;
 TRISB = 0x01;
 TRISC = 0x00;
 TRISD = 0x00;
 TRISE = 0xFF;

 PORTA = 0x00;
 PORTB = 0x00;
 PORTC = 0x00;
 PORTD = 0x00;
}

void config_IT()
{
 GIE_bit = 1;
 IPEN_bit = 0;
 RBPU_bit = 0;
 INTEDG0_bit = 1;
 INT0IE_bit = 1;
 TMR0IE_bit = 1;
}
void config_TMR0()
{
 TMR0ON_bit = 1;
 T08BIT_bit = 0;
 T0CS_bit = 0;
 PSA_bit = 1;
 TMR0L = 0xFF;
 TMR0H = 0xFF;
}
void interrupt(void)
{
 USB_Interrupt_Proc();

 if(INT0IF == 1){
 INT0IF_bit = 0;
 }
}


unsigned char characterMem[] = {0,124,254,130,254,124,0,
 0,64,254,254,0,0,0,
 0,70,206,154,242,98,0,
 0,68,198,146,254,108,0,
 0,24,120,254,254,8,0,
 0,244,246,162,190,156,0,
 0,124,254,146,222,76,0,
 0,128,142,190,240,192,0,
 0,108,254,146,254,108,0,
 0,100,246,146,254,124,0,
 0,144,0,0,0,0,0,
 0,2,22,0,0,0,0,
 0,8,20,34,0,0,0,
 0,20,20,20,0,0,0,
 0,34,20,8,0,0,0,
 0,64,138,144,192,0,
 0,240,132,153,165,185,133,136,
 0,6,56,200,200,56,6,
 0,254,146,146,146,254,108,
 0,254,130,130,130,130,198,
 0,254,130,130,130,254,124,
 0,254,254,146,146,146,130,
 0,254,254,144,144,144,128,
 0,124,254,130,146,150,222,
 0,254,254,16,16,254,254,
 0,0,0,254,254,0,0,
 0,12,14,2,254,252,0,
 0,254,254,56,108,198,130,
 0,254,254,2,2,2,0,
 0,254,240,60,12,60,240,
 0,254,254,240,60,14,254,
 0,124,254,130,130,130,254,
 0,254,254,144,144,240,96,
 0,254,130,138,142,254,124,
 0,254,254,144,144,144,254,
 0,100,246,146,146,222,76,
 0,128,128,254,254,128,128,
 0,252,254,2,2,254,252,
 0,192,248,62,62,248,192,
 0,192,56,6,24,6,56,192,
 0,198,238,56,56,238,198,
 0,192,224,62,62,224,192,
 0,134,142,154,178,226,194,
 0,0,0,0,0,0,0,
 0,250,250,0,0,0,0,0
 };

unsigned char videoMem[7] = {0};
unsigned char enMap[] = {1,1,2,2,2,2,4,4,4,4,8,8,8,8,16,16,16,16};
unsigned char columns[] = {0,8,0,8,16,24,0,8,16,24,0,8,16,24,0,8,16,24};
unsigned char ptrCharMem = 0;
unsigned int initPtrCharMem = 0;
unsigned char array_B1_values[18] = {0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01};
unsigned char array_EN_values[18] = {0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0x10,0x10,0x10,0x10};

unsigned char tamMsg = 0;
unsigned char ptrVideoMem = 0;
unsigned char fila = 0;
unsigned char cursor = 2;

unsigned int aux0 = 0;
unsigned char invertido = 0;
unsigned char contador = 0;
unsigned char sizeUSB = 0;
unsigned char buffer_USB = 0;
unsigned char mensaje_flag = 0;
unsigned char erase_flag = 0;

bit flagVMemFull;
bit flagScreenEn;
bit pixel;
bit fWrap;
unsigned char aux3 = 0xFF;


unsigned char mensaje1[] = {'F','A','C','U','L','T','A','D',0X5B,'D','E',0X5B,'A','U','T','O','M','A','T','I','C','A'};
unsigned char mensaje2[] = {'B','U','E','N','A',0x5B,'S','U','E','R','T',0x5B,'E','N',0x5B,'L','O','S',0x5B,'P','A','R','C','I','A','L','E','S'};
unsigned char mensaje3[] = {'H','A','Y',0x5B,'G','U','A','R','D','I','A',0x5C};
unsigned char mensaje4[] = {0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B,0x5B};
void getMap()
{
 int i;
 for(i = 0;i < 7;i++)
 {
 videoMem[i] = characterMem[initPtrCharMem + i];
 }
 flagVMemFull = 1;
}

unsigned char get_Array_Size(unsigned char array[])
{
 unsigned char i = 0;
 while(i != '\n')
 {i++;}
 return i;
}

void visualizar()
{
 unsigned char i = 0x00;
 unsigned char j = 0x01;
 unsigned char signal = 0x00;

 flagVMemFull = 0;
 if(flagScreenEn == 1)
 {
 flagScreenEn = 0;
 pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;

 while(cursor != i && cursor < 18){ i++; }
 while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
 signal = (j << 1);
 signal = ((i << 4) & 0x10) | signal;
 signal = ((array_B1_values[i] << 5) | signal);

 if(pixel == 1)
 {
 EN_ON_OFF = 0;
 signal = signal & 0xBF;
 }
 else
 {
 EN_ON_OFF = 1;
 signal = signal | 0x40;
 }
 PORTB = signal;

 if(fWrap == 1) { EN_UP_DOWN = 0x00; }
 else { EN_UP_DOWN = 0x01; }

 if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }
 else { flagScreenEn = 0x01; }

 PORTD = (PORTD & 0x18) | (fila & 0x07);


 PORTA = 0x00;
 Delay_ms(1);
 PORTA = array_EN_values[cursor];
 Delay_ms(1);
 PORTA = 0x00;

 fila = fila +1;
 if(fila == 8)
 {
 ptrVideoMem = ptrVideoMem + 1;
 fila = 0;
 if(ptrVideoMem == 7)
 {
 ptrVideoMem = 0;
 flagVMemFull = 0;
 initPtrCharMem = initPtrCharMem + 7;
 cursor = cursor + 1;
 aux0 = aux0 + 1;
 flagScreenEn = 0x01;
 if(cursor == 17)
 {
 fWrap = !fWrap;
 cursor = 2;
 }
 }
 }
 }
}

void visualizar_invertido()
{
 unsigned char i = 0x00;
 unsigned char j = 0x01;
 unsigned char signal = 0x00;

 flagVMemFull = 0;
 if(flagScreenEn == 1)
 {
 flagScreenEn = 0;
 pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;

 while(cursor != i && cursor < 18){ i++; }
 while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
 signal = (j << 1);
 signal = ((i << 4) & 0x10) | signal;
 signal = ((array_B1_values[i] << 5) | signal);

 if(pixel == 0)
 {
 EN_ON_OFF = 0;
 signal = signal & 0xBF;
 }
 else
 {
 EN_ON_OFF = 1;
 signal = signal | 0x40;
 }
 PORTB = signal;

 if(fWrap == 1) { EN_UP_DOWN = 0x00; }
 else { EN_UP_DOWN = 0x01; }

 PORTD = (PORTD & 0x18) | (fila & 0x07);

 if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }
 else { flagScreenEn = 0x01; }


 PORTA = 0x00;
 Delay_ms(1);
 PORTA = array_EN_values[cursor];
 Delay_ms(1);
 PORTA = 0x00;

 fila = fila +1;
 if(fila == 8)
 {
 ptrVideoMem = ptrVideoMem + 1;
 fila = 0;
 if(ptrVideoMem == 7)
 {
 ptrVideoMem = 0;
 flagVMemFull = 0;
 initPtrCharMem = initPtrCharMem + 7;
 cursor = cursor + 1;
 aux0 = aux0 + 1;
 flagScreenEn = 0x01;
 if(cursor == 18)
 {
 fWrap = !fWrap;
 cursor = 2;
 }
 }
 }
 }
}

void main() {

 flagVMemFull = 0;
 flagScreenEn = 1;
 pixel = 0;
 fWrap = 0;

 config_PIC();
 config_IT();
 HID_Enable(&readUSB,&writeUSB);

 while(1){
 L_USB = 0;
 sizeUSB = HID_Read();
 if(sizeUSB)
 {
 L_USB = 1;
 buffer_USB = readUSB[0];
 invertido = readUSB[1];
 mensaje_flag = readUSB[2];
 erase_flag = readUSB[3];
 contador = contador +1;

 if(aux0 < contador)
 {
 if (mensaje_flag == 'a'){ ptrCharMem = mensaje1[aux0] - 0x30; tamMsg = get_Array_Size(mensaje1); }
 if (mensaje_flag == 'b'){ ptrCharMem = mensaje2[aux0] - 0x30; tamMsg = get_Array_Size(mensaje2); }
 if (mensaje_flag == 'c'){ ptrCharMem = mensaje3[aux0] - 0x30; tamMsg = get_Array_Size(mensaje3); }
 if (erase_flag == 'z'){ ptrCharMem = mensaje4[aux0] - 0x30; tamMsg = get_Array_Size(mensaje4); }
 else
 {
 tamMsg = contador;
 ptrCharMem = (buffer_USB - 0x30);
 }
 initPtrCharMem = ptrCharMem*7;
 getMap();

 if(flagVMemFull == 1 && invertido == 'n'){ visualizar(); }
 if(flagVMemFull == 1 && invertido == 's'){ visualizar_invertido(); }
 }
 }
 L_working = 1;
 }

}
