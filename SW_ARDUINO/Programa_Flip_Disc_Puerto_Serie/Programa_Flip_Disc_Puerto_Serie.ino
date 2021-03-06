unsigned char mem_char[] = {0,124,254,130,254,124,0,
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
                            0,254,254,0,0,0,0,
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
                            0,134,142,154,178,226,194
                            };
                            
unsigned char enable[] = {1,1,2,2,2,2,4,4,4,4,8,8,8,8,16,16,16,16};              //  habilitaciones de los modulos
unsigned char columna[] = {0,8,0,8,16,24,0,8,16,24,0,8,16,24,0,8,16,24};         //  iniciio de cada caracter
unsigned char video[7];           //  memoria de video 
char sym = 0;                         // puntero a memoria de caracteres   
unsigned int init_sym=0; 
int tam_msg = 0;                         //tamano del mensaje 
char bufferr[36];   

//char cnt_byte=0;                  // desplazamiento en la mem caracteres
bool f_v_ram_full = false;        // Memoria de video llena, caracter listo
bool f_screen_enable = true;      // bandera que indica que paso el tiempo necesario de giro de un pixel
bool pixel = 0;                     //  valor del pixel a girar
unsigned char col = 0;          // puntero a memoria de video
unsigned char fila = 0;
unsigned char Cursor = 2;     // posicion del caracter a escribir(bloque)
int A0_pin = 14;
int A1_pin = 15;
int A2_pin = 16;
int B0_pin = 17;
int B1_pin = 18;
unsigned char _columna = 0;
bool f_wrap = false;        // indica en que renglon se encuentra el caracter
int EN_ON_OFF_pin = 6;
int EN_UP_DOWN_pin = 5;
int fila_A_pin = 0;
int fila_B_pin = 1;
int fila_C_pin = 2;
int EN_1_pin = 4;
int EN_0_pin = 7;
int EN_2_pin = 8;
int EN_3_pin = 9;
int EN_4_pin = 10;
int dato_pin = 3;
bool flag_recibido = false;
int l=0;

void setup() {
Serial.begin(9600);
pinMode(A0_pin,OUTPUT);
pinMode(A1_pin,OUTPUT);
pinMode(A2_pin,OUTPUT);
pinMode(B0_pin,OUTPUT);
pinMode(B1_pin,OUTPUT);
pinMode(EN_ON_OFF_pin,OUTPUT);
pinMode(EN_UP_DOWN_pin,OUTPUT);
pinMode(fila_A_pin,OUTPUT);
pinMode(fila_B_pin,OUTPUT);
pinMode(fila_C_pin,OUTPUT);
pinMode(EN_1_pin,OUTPUT);
pinMode(EN_0_pin,OUTPUT);
pinMode(EN_2_pin,OUTPUT);
pinMode(EN_3_pin,OUTPUT);
pinMode(EN_4_pin,OUTPUT);
pinMode(dato_pin,OUTPUT);
if(Serial.available()){
  Serial.read();}
}

void loop() 
{
  if (Serial.available()>0) 
  {
    
    int index=0;
    delay(100);
    tam_msg = Serial.available();
    while(tam_msg--){
      bufferr[index++] = Serial.read();
    }
    Serial.println(bufferr);    
      sym = bufferr[l] - 0x30;
      if(sym==0)
        {
          init_sym=0;
        }
      else
        {
          init_sym=sym*7;
        }
        l=l+1;
     get_map();
     if(f_v_ram_full == true)
     {
      visualizar();
     }       
   
  }
}

void get_map ()
{
  
  for(int i=0;i<7;i++)
  {
    video[i] = mem_char[init_sym+ i];   // copiando de la memoria de caracteres a la de video el caracter
  }
  f_v_ram_full = true;
  //cnt_byte =0;
}

void visualizar()
{
    f_v_ram_full = false;
  if(f_screen_enable == true)
  {
    f_screen_enable = false;
    pixel = GetBit(video[col],fila);      // obtener el pixel a girar
    if(pixel == true)                     //  si se enciende
    {
      digitalWrite(EN_ON_OFF_pin,LOW);    //  habilita los decodificadores para encender(0)
      digitalWrite(dato_pin,LOW);         // dato en 0
      switch(Cursor)                 
      {
      case 0:               //0_mod 0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 1:               //8_mod 0
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 2:               //0_mod 1
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 3:               //8_mod 1
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 4:               //16_mod 1
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 5:              //24_mod 1
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 6:               //0_mod 2
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 7:               //8_mod 2
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 8:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 9:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 10:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 11:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 12:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 13:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 14:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 15:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 16:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 17:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);    
      }
    switch(col)
    {
      case 0:               
        digitalWrite(A0_pin,HIGH); 
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 1:                    
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 2:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 3:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 4:              
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 5:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
        break;
      case 6:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
      }
        if(f_wrap == true)
        {
           digitalWrite(EN_UP_DOWN_pin,LOW);
        }
        else
        {
          digitalWrite(EN_UP_DOWN_pin,HIGH);
        }
    }
    else
    {
      digitalWrite(EN_ON_OFF_pin,HIGH);    //  habilita los decodificadores para apagar(1)
      digitalWrite(dato_pin,HIGH);         // dato en 1
     switch(Cursor)
     {
      case 0:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 1:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 2:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 3:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 4:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 5:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 6:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 7:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 8:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 9:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 10:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 11:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 12:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 13:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);
        break;
      case 14:               //0
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,LOW);
        break;
      case 15:               //8
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,LOW);
        break;
      case 16:               //16
        digitalWrite(B0_pin,LOW);
        digitalWrite(B1_pin,HIGH);
        break;
      case 17:              //24
        digitalWrite(B0_pin,HIGH);
        digitalWrite(B1_pin,HIGH);    
      }
    switch(col)
    {
      case 0:               
        digitalWrite(A0_pin,HIGH); 
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 1:                    
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 2:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 3:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 4:              
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 5:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
        break;
      case 6:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
      }
        if(f_wrap == true)
        {
          digitalWrite(EN_UP_DOWN_pin,LOW);
        }
        else
        {
          digitalWrite(EN_UP_DOWN_pin,HIGH);
        }
    }
    mandar_fila();
    
     if(sym == tam_msg)
          {
                f_screen_enable = false;
          }
          else
          {
                f_screen_enable = true;
          }
    mandar_enable();
    fila = fila + 1;      //  acceder al siguiente bit
    if(fila == 8)       // termiando la columna
    {
      col = col +1;     // proxima columna
      fila = 0;         //  primer bit de la columna
      if(col == 7)      // si la columna es 7 termino el caracter
      {
        col = 0;       
        f_v_ram_full = false;   // desechar memoria de video
  
         init_sym=init_sym+7;
         sym=sym+1;
         Cursor = Cursor + 1;
         f_screen_enable = true; 
      
        if(Cursor == 17)        // finalizado primer renglon
        {
          f_wrap = !f_wrap;     // renglon sigiente
          Cursor = 0;           // principio del proximo renglon
        }

       }
      }
  }
}

bool GetBit(byte N, int pos)
   {                            
       int b = N >> pos ;       
       b = b & 1 ;              
       return b ;
   }

void mandar_fila()
{
  switch(fila)
  {
    case 0:               
        digitalWrite(fila_A_pin,LOW);
        digitalWrite(fila_B_pin,LOW);
        digitalWrite(fila_C_pin,LOW);
        break;
      case 1:               
        digitalWrite(fila_A_pin,HIGH);
        digitalWrite(fila_B_pin,LOW);
        digitalWrite(fila_C_pin,LOW);
        break;
      case 2:                    
        digitalWrite(fila_A_pin,LOW);
        digitalWrite(fila_B_pin,HIGH);
        digitalWrite(fila_C_pin,LOW);
        break;
      case 3:               
        digitalWrite(fila_A_pin,HIGH);
        digitalWrite(fila_B_pin,HIGH);
        digitalWrite(fila_C_pin,LOW);
        break;
      case 4:               
        digitalWrite(fila_A_pin,LOW);
        digitalWrite(fila_B_pin,LOW);
        digitalWrite(fila_C_pin,HIGH);
        break;
      case 5:              
        digitalWrite(fila_A_pin,HIGH);
        digitalWrite(fila_B_pin,LOW);
        digitalWrite(fila_C_pin,HIGH);
        break;
      case 6:               
        digitalWrite(fila_A_pin,LOW);
        digitalWrite(fila_B_pin,HIGH);
        digitalWrite(fila_C_pin,HIGH);
        break;
      case 7:               
        digitalWrite(fila_A_pin,HIGH);
        digitalWrite(fila_B_pin,HIGH);
        digitalWrite(fila_C_pin,HIGH);
      }
}

void mandar_enable()    // mandar enable y dar pulso
{
  digitalWrite(EN_0_pin,LOW);
  digitalWrite(EN_1_pin,LOW);
  digitalWrite(EN_2_pin,LOW);
  digitalWrite(EN_3_pin,LOW);
  digitalWrite(EN_4_pin,LOW);
  delay(15);
  switch(Cursor)
  {
      case 0:               //Modulo 0
        digitalWrite(EN_0_pin,HIGH);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 1:               //Modulo 0
        digitalWrite(EN_0_pin,HIGH);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 2:              //Modulo 1
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,HIGH);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 3:               //Modulo 1
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,HIGH);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 4:               //Modulo 1
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,HIGH);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 5:              //Modulo 1
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,HIGH);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 6:               //Modulo 2
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,HIGH);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 7:               //Modulo 2
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,HIGH);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 8:               //Modulo 2
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,HIGH);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 9:              //Modulo 2
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,HIGH);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 10:               //Modulo 3
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,HIGH);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 11:               //Modulo 3
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,HIGH);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 12:               //Modulo 3
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,HIGH);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 13:              //Modulo 3
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,HIGH);
        digitalWrite(EN_4_pin,LOW);
        break;
      case 14:               //Modulo 4
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,HIGH);
        break;
      case 15:               //Modulo 4
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,HIGH);
        break;
      case 16:               //Modulo 4
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,HIGH);
        break;
      case 17:              //Modulo 4
        digitalWrite(EN_0_pin,LOW);
        digitalWrite(EN_1_pin,LOW);
        digitalWrite(EN_2_pin,LOW);
        digitalWrite(EN_3_pin,LOW);
        digitalWrite(EN_4_pin,HIGH);
      }
      
      delay(15);
      
      digitalWrite(EN_0_pin,LOW);
      digitalWrite(EN_1_pin,LOW);
      digitalWrite(EN_2_pin,LOW);
      digitalWrite(EN_3_pin,LOW);
      digitalWrite(EN_4_pin,LOW);
}
