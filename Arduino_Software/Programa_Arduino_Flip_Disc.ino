unsigned char tabla_A[] = {192,56,38,38,56,192,0};
unsigned char enable[] = {1,1,2,2,2,2,4,4,4,4,8,8,8,8,16,16,16,16};
unsigned char columna[] = {0,8,0,8,16,24,0,8,16,24,0,8,16,24,0,8,16,24};
unsigned char video[7];
char sym;
char cnt_byte=0;
bool f_v_ram_full = false;
bool f_screen_enable = true;
bool pixel;
unsigned char col = 0;
unsigned char fila = 0;
unsigned char Cursor = 0;
int A0_pin = 0;
int A1_pin = 1;
int A2_pin = 2;
int B0_pin = 3;
int B1_pin = 4;
unsigned char _columna;
bool f_wrap = false;
int EN_ON_OFF_pin = 5;
int EN_LINEAS_pin = 6;
int fila_A_pin = 7;
int fila_B_pin = 8;
int fila_C_pin = 9;
int EN_0_pin = 10;
int EN_1_pin = 11;
int EN_2_pin = 12;
int EN_3_pin = 13;
int EN_4_pin = 14;
int dato_pin = 15;

void setup() {
pinMode(A0_pin,OUTPUT);
pinMode(A1_pin,OUTPUT);
pinMode(A2_pin,OUTPUT);
pinMode(B0_pin,OUTPUT);
pinMode(B1_pin,OUTPUT);
pinMode(EN_ON_OFF_pin,OUTPUT);
pinMode(EN_LINEAS_pin,OUTPUT);
pinMode(fila_A_pin,OUTPUT);
pinMode(fila_B_pin,OUTPUT);
pinMode(fila_C_pin,OUTPUT);
pinMode(EN_0_pin,OUTPUT);
pinMode(EN_1_pin,OUTPUT);
pinMode(EN_2_pin,OUTPUT);
pinMode(EN_3_pin,OUTPUT);
pinMode(EN_4_pin,OUTPUT);
pinMode(dato_pin,OUTPUT);
}

void loop() {
 get_map();
 if(f_v_ram_full == true)
 {
  visualizar();
 }
 
}

void get_map ()
{
  sym =0;
  for(int i=0;i<7;i++)
  {
    video[cnt_byte] = tabla_A[sym+cnt_byte];
  }
  f_v_ram_full =true;
  cnt_byte =0;
}

void visualizar()
{
  if(f_screen_enable == true)
  {
    f_screen_enable = false;
    pixel = GetBit(video[col],fila);
    if(pixel == true)
    {
      //EN_ON_OFF =
      digitalWrite(dato_pin,LOW); 
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
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 1:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 2:                    
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 3:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 4:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 5:              
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 6:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
        break;
      case 7:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
      }
        if(f_wrap == true)
        {
          //EN_LINEAS = 
        }
        else
        {
          //EN_LINEAS =
        }
    }
    else
    {
      //EN_ON_OFF = 
      digitalWrite(dato_pin,HIGH);
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
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 1:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,LOW);
        break;
      case 2:                    
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 3:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,LOW);
        break;
      case 4:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 5:              
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,LOW);
        digitalWrite(A2_pin,HIGH);
        break;
      case 6:               
        digitalWrite(A0_pin,LOW);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
        break;
      case 7:               
        digitalWrite(A0_pin,HIGH);
        digitalWrite(A1_pin,HIGH);
        digitalWrite(A2_pin,HIGH);
      }
        if(f_wrap == true)
        {
          //EN_LINEAS = 
        }
        else
        {
          //EN_LINEAS =
        }
    }
    mandar_fila();
        mandar_enable();
        f_screen_enable = true;
        fila = fila+1;
        if(fila == 7)
        {
          col = col +1;
          fila = 0;
          if(col == 7)
          {
            col =0;
            f_v_ram_full = false;
            Cursor = Cursor +1;
            if(Cursor == 17)
            {
              f_wrap = !f_wrap;
              Cursor = 0;
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

void mandar_enable()
{
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
