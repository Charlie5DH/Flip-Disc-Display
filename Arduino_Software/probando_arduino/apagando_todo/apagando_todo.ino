int pin_A = 0;
int pin_B = 1;
int pin_C = 2;
int pines [3] = {0,1,2};
int pin_dato = 3;
int pin_enable = 4;
int pin_dec_UP_DOWN = 5;
int pin_dec_ON_OFF = 6;
int var =0;
int aux=0;
int aux2=0;
int var3 = 0;
int var4=0;
unsigned char columna [] = {0,8,16,24};
int pin_A0 = 14;
int pin_A1 = 15;
int pin_A2 = 16;
int pin_B0 = 17;
int pin_B1 = 18;
int pines_columna [] = {14,15,16,17,18};
bool state = false;
bool state2 = false;

bool get_bit(byte N, int pos)
{
  int b = N >> pos;
  b = b & 1;
  return b;
}

void setup() 
{
  pinMode(pin_A, OUTPUT);
  pinMode(pin_B, OUTPUT);
  pinMode(pin_C, OUTPUT);
  pinMode(pin_dato, OUTPUT);
  pinMode(pin_enable, OUTPUT);
  pinMode(pin_dec_UP_DOWN, OUTPUT);
  pinMode(pin_dec_ON_OFF, OUTPUT);
  for(int i=0;i<3;i++)
  {
    pinMode(pines[i],OUTPUT);
  }
  pinMode(pin_A0,OUTPUT);
  pinMode(pin_A1,OUTPUT);
  pinMode(pin_A2,OUTPUT);
  pinMode(pin_B0,OUTPUT);
  pinMode(pin_B1,OUTPUT);

  digitalWrite(pin_dec_UP_DOWN,HIGH);
  digitalWrite(pin_dec_ON_OFF,HIGH);

  digitalWrite(pin_enable,LOW);
  digitalWrite(pin_dato,HIGH);

  for (int Cursor=0;Cursor<4;Cursor++)
  {
    for(int e=1;e<8;e++)
    {
      aux = columna[Cursor]+e;
     for(var = 0;var<5;var++)
     {
      state = get_bit(aux,var);
      digitalWrite(pines_columna[var],state);
      for(int i=0;i<8;i++)
       {
         for(int var2 = 0;var2<3;var2++)
         {
            state = get_bit(i,var2);
            digitalWrite(pines[var2],state);
         }    
     
         delay(1);
         digitalWrite(pin_enable,HIGH);
         delay(1);
         digitalWrite(pin_enable,LOW);
       }
     }
    }
 }  
  digitalWrite(pin_dec_UP_DOWN,LOW);
  
  for (int Cursor=0;Cursor<3;Cursor++)
  {
    for(int e=1;e<8;e++)
    {
      aux2 = columna[Cursor]+e;
     for(var3 = 0;var3<5;var3++)
     {
      state2 = get_bit(aux2,var3);
      digitalWrite(pines_columna[var3],state2);
      for(int i=0;i<8;i++)
       {
         for(int var2 = 0;var2<3;var2++)
         {
            state2 = get_bit(i,var2);
            digitalWrite(pines[var2],state2);
         }    
     
         delay(1);
         digitalWrite(pin_enable,HIGH);
         delay(1);
         digitalWrite(pin_enable,LOW);
       }
     }
    }
 }      
     
  delay(1);
  digitalWrite(pin_enable,HIGH);
  delay(1);
  digitalWrite(pin_enable,LOW);
  }


void loop() 
{
}

