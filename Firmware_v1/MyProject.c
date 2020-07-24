/*---------Inicializacioned para el HID--------------------------------*/
/* todos los dispositivos USB se identifican por un vendor ID(VID) y un Product ID()PID
al realizar la interfaz host es necesario conocer el VID y el PID para saber que dispositivo USB
se esta utilizando(product name:USB HID FOR FDD; Vendor name: CUJAE)*/

unsigned char readUSB[64]          absolute 0x500;     // este buffer se encuentra a partir del 0x500 de la RAM
unsigned char writeUSB[64]         absolute 0x540;    //64 bytes mas
unsigned char reservUSB[256]       absolute 0x400;

/*---------Definicion de pines para habilitaciones de los modulos----------*/
sbit EN_M0 at RA0_bit;
sbit EN_M1 at RA1_bit;
sbit EN_M2 at RA2_bit;
sbit EN_M3 at RA3_bit;
sbit EN_M4 at RA4_bit;
sbit EN_M5 at RA5_bit;
/*---------Definicion de pines para selectores de columnas y Dato----------------*/
sbit A_0 at RB1_bit;
sbit A_1 at RB2_bit;
sbit A_2 at RB3_bit;
sbit B_0 at RB4_bit;
sbit B_1 at RB5_bit;
sbit DATO at RB6_bit;
/*---------Definicion de pines para datos de los decodificadores------------*/
sbit D0 at RD0_bit;
sbit D1 at RD1_bit;
sbit D2 at RD2_bit;
sbit EN_ON_OFF at RD3_bit;
sbit EN_UP_DOWN at RD4_bit;

sbit D_minus at RC4_bit;  // D- del USB
sbit D_plus at RC6_bit;   // D+ del USB
sbit L_USB at RC6_bit;   // Led que indica comunicacion USB
sbit L_working at RC7_bit;   // Led que indica comunicacion PS/2
sbit KBDDATA at RE0_bit;   // pin de entrada de datos del teclado

void config_PIC()
{
     ADCON1 = 0x0F;
     TRISA = 0x00;      // configurado PORTA como salida
     TRISB = 0x01;      // utilizando la interrupcion del RB0(INT0), resto del puerto como salida
     TRISC = 0x00;      // configurado PORTC como salida
     TRISD = 0x00;      // configurado PORTD como salida
     TRISE = 0xFF;      // configurado PORTE como entrada

     PORTA = 0x00;      // inicializando los puertos (borrando los latches)
     PORTB = 0x00;
     PORTC = 0x00;
     PORTD = 0x00;
}

void config_IT()
{
     GIE_bit = 1;       //bit activador del permiso global de interrupciones (global interruption enable)
     IPEN_bit = 0;      // niveles de prioridad no permitidos (interruption priority enable)
     RBPU_bit = 0;      // activador del pull-up interno del puerto B
     INTEDG0_bit = 1;   // selector de flanco de la INT0, frente de subida
     INT0IE_bit = 1;    // bit de permiso de la interrupcion externa 0 (INT0 input enable)
     TMR0IE_bit = 1;    // activado permiso de interrupcion por desbordamiento del TMR0(sirve para enmascarar)
}
void config_TMR0()
{
     TMR0ON_bit = 1;    // permite  timer0
     T08BIT_bit = 0;    // se configura como contador de 16 bits (65536)
     T0CS_bit = 0;      // reloj interno del ciclo de instruccion
     PSA_bit = 1;       // no prescaler
     TMR0L = 0xFF;
     TMR0H = 0xFF;
}
void interrupt(void)
{
     USB_Interrupt_Proc();        // mantiene la comunicacion con la PC
     
     if(INT0IF == 1){               // si la interrupcion llego por la interrupcion externa0                    (revisar si no funciona el USB)
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
                                0,0,0,254,254,0,0,          //letra I
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
                                0,0,0,0,0,0,0,       //0x5B      ESPACIO
                                0,250,250,0,0,0,0,0 //0x5C  !!!!!
                               };
                               
unsigned char videoMem[7] = {0};                                                  // 7 columnas x 8 filas
unsigned char enMap[] = {1,1,2,2,2,2,4,4,4,4,8,8,8,8,16,16,16,16};               //  habilitaciones de los modulos
unsigned char columns[] = {0,8,0,8,16,24,0,8,16,24,0,8,16,24,0,8,16,24};        //  inicio de cada caracter
unsigned char ptrCharMem = 0;                                                  // puntero a memoria de caracteres
unsigned int initPtrCharMem = 0;
unsigned char array_B1_values[18] = {0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01};
unsigned char array_EN_values[18] = {0x01,0x01,0x02,0x02,0x02,0x02,0x04,0x04,0x04,0x04,0x08,0x08,0x08,0x08,0x10,0x10,0x10,0x10};  // diferentes modulos, en dependencia de cual sea el modulo se activara el EN
 
unsigned char tamMsg = 46;                                                      //tamano del mensaje
unsigned char ptrVideoMem = 0;                                              // puntero a memoria de video
unsigned char fila = 0;
unsigned char cursor = 2; 
                                                  // posicion del caracter a escribir(bloque)
unsigned int aux0 = 0;
unsigned char invertido = 0;
unsigned char contador = 0;
unsigned char sizeUSB = 0;
unsigned char buffer_USB = 0;
unsigned char mensaje1_flag = 0;
unsigned char mensaje2_flag = 0;
unsigned char mensaje3_flag = 0;

bit flagVMemFull;                                                           // Memoria de video llena, caracter listo
bit flagScreenEn;                                                          // bandera que indica que paso el tiempo necesario de giro de un pixel
bit pixel;                                                                 //  valor del pixel a girar
bit fWrap;                                                                 // indica en que renglon se encuentra en caracter a escribir
unsigned char aux3 = 0xFF;


unsigned char mensaje1[] = {'F','A','C',0X5B,'D','E','A','U','T','O','M','A','T','I','C','A','Y',0X5B,'B','I','O','M','E','D','I','C','A'};
unsigned char mensaje2[] = {'B','U','E','N','A',0x5B,'S','U','E','R','T',0x5B,'E','N',0x5B,'L','O','S',0x5B,'P','A','R','C','I','A','L','E','S'};
unsigned char mensaje3[] = {'H','A','Y',0x5B,'G','U','A','R','D','I','A',0x5C};

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
 unsigned char signal = 0x00;                     // variable temporal que sera enviada al puerto B

 flagVMemFull = 0;
 if(flagScreenEn == 1)
 {
  flagScreenEn = 0;
  pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;      // obtener el pixel a girar(getbit)

  while(cursor != i && cursor < 18){ i++; }
  while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
  signal = (j << 1);                                    // ubicados A0,A1,A2 (bits 1,2 y 3)
  signal = ((i << 4) & 0x10) | signal;                // hallando el valor de B0 y ubicandolo en el 5to bit de la palabra
  signal = ((array_B1_values[i] << 5) | signal);      // hallando el valor de B1 y ubicandolo en su posicicon correespondiente
  
  if(pixel == 1)                                       // si es encendido el pixel
  {
   EN_ON_OFF = 0;                                      // habilita los decodificadores para encender
   signal = signal & 0xBF;                             // DATO en 0 (bit 6 de signal)
  }
  else                                                 // apagado el pixel
  {
   EN_ON_OFF = 1;                                      //habilita los decoder para apagar
   signal = signal | 0x40;                             // DATO en 1 (bit 6 de signal)
  }
  PORTB = signal;                                     // escribe en PB <- A0,A1,A2,B0,B1,DATO
  
  if(fWrap == 1) { EN_UP_DOWN = 0x00; }
  else { EN_UP_DOWN = 0x01; }
  
  PORTD = (PORTD & 0x18) | (fila & 0x07);              // leer del mismo puerto para no afectar los valores de los EN (mandar fila)

  if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }                                                                          //                             (REVISAR)
  else { flagScreenEn = 0x01; }
  
  //-------pulso enable------------------
  PORTA = 0x00;                                        // enable de los decodificadores en nivel bajo para dar el pulso
  Delay_ms(1);
  PORTA = array_EN_values[cursor];
  Delay_ms(1);
  PORTA = 0x00;

  fila = fila +1;                                      // acceder al siguiente bit
  if(fila == 8)                                        //terminando la columna
  {
   ptrVideoMem = ptrVideoMem + 1;
   fila = 0;
   if(ptrVideoMem == 7)                                // termino el caracter
   {
    ptrVideoMem = 0;
    flagVMemFull = 0;                                  //desechar memoria de video
    initPtrCharMem = initPtrCharMem + 7;
    cursor = cursor + 1;
    aux0 = aux0 + 1;
    flagScreenEn = 0x01;
    if(cursor == 17)                                   // finalizado primer renglon
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
 unsigned char signal = 0x00;                     // variable temporal que sera enviada al puerto B

 flagVMemFull = 0;
 if(flagScreenEn == 1)
 {
  flagScreenEn = 0;
  pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;      // obtener el pixel a girar(getbit)

  while(cursor != i && cursor < 18){ i++; }
  while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
  signal = (j << 1);                                    // ubicados A0,A1,A2 (bits 1,2 y 3)
  signal = ((i << 4) & 0x10) | signal;                // hallando el valor de B0 y ubicandolo en el 5to bit de la palabra
  signal = ((array_B1_values[i] << 5) | signal);      // hallando el valor de B1 y ubicandolo en su posicicon correespondiente

  if(pixel == 0)                                       // si es encendido el pixel
  {
   EN_ON_OFF = 0;                                      // habilita los decodificadores para encender
   signal = signal & 0xBF;                             // DATO en 0 (bit 6 de signal)
  }
  else                                                 // apagado el pixel
  {
   EN_ON_OFF = 1;                                      //habilita los decoder para apagar
   signal = signal | 0x40;                             // DATO en 1 (bit 6 de signal)
  }
  PORTB = signal;                                     // escribe en PB <- A0,A1,A2,B0,B1,DATO

  if(fWrap == 1) { EN_UP_DOWN = 0x00; }
  else { EN_UP_DOWN = 0x01; }

  PORTD = (PORTD & 0x18) | (fila & 0x07);              // leer del mismo puerto para no afectar los valores de los EN (mandar fila)     Mascara

  if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }
  else { flagScreenEn = 0x01; }

  //-------pulso enable------------------
  PORTA = 0x00;                                        // enable de los decodificadores en nivel bajo para dar el pulso
  Delay_ms(1);
  PORTA = array_EN_values[cursor];
  Delay_ms(1);
  PORTA = 0x00;

  fila = fila +1;                                      // acceder al siguiente bit
  if(fila == 8)                                        //terminando la columna
  {
   ptrVideoMem = ptrVideoMem + 1;
   fila = 0;
   if(ptrVideoMem == 7)                                // termino el caracter
   {
    ptrVideoMem = 0;
    flagVMemFull = 0;                                  //desechar memoria de video
    initPtrCharMem = initPtrCharMem + 7;
    cursor = cursor + 1;
    aux0 = aux0 + 1;
    flagScreenEn = 0x01;
    if(cursor == 18)                                   // finalizado primer renglon
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
              sizeUSB = HID_Read();                 //Devuelve el numero de bytes recibidos
              if(sizeUSB)                           // si se han recibido datos de la PC
              {
               L_USB = 1;
               buffer_USB = readUSB[0];             // recibido caracter por USB
               invertido = readUSB[1];              // invertir colores
               /*mensaje1_flag = readUSB[2];
               mensaje2_flag = readUSB[3];
               mensaje3_flag = readUSB[4];
               */
               contador = contador +1;
              }
              if(aux0 < contador)
              {
               ptrCharMem = (buffer_USB - 0x30);
               initPtrCharMem = ptrCharMem*7;
               getMap();
               if(flagVMemFull == 1 && invertido == 'n') { visualizar(); }
               if(flagVMemFull == 1 && invertido == 's') { visualizar_invertido(); }
              }
              L_working = 1;
     }

}