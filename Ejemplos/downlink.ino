#define SigfoxDeb
#include <SoftwareSerial.h>
#ifdef SigfoxDeb
SoftwareSerial mySerial(0, 1); // RX, TX
#endif
const int boton=6;
const int led6=8;
char RespuestaSigfox[50];
char ID[51];
char PAC[51];
char res[51];


void setup() 
{
  Serial.begin(9600);
  #ifdef SigfoxDeb
  mySerial.begin(9600);
  #endif
  pinMode(boton, INPUT);
  pinMode(led6, OUTPUT);
  pinMode(7, OUTPUT);
  #ifdef SigfoxDeb
  mySerial.println("\n\n\n\n\n\n\n\n\rInicio");
  #endif
}

void leer_info()
{
  int i;
  int count;
  String V_temp;
  digitalWrite(7, HIGH);
  delay(1000);
  enviarcomandoATSigfox("AT$RC");
  downlink_SIGFOX("AT$SF=0102030405,1");
  strcpy(res,RespuestaSigfox);
  digitalWrite(7, LOW);
  delay(500);
  Serial.print("respuesta Sigfox: ");
  Serial.println(res);
  V_temp=res[20];
  count=V_temp.toInt();
  Serial.print("Parpadeo del Led: ");
  Serial.print(count);
  Serial.println(" veces");
  for(i=1;i<=count;i++)
  {
    digitalWrite(led6, HIGH);
    delay(500);
    digitalWrite(led6, LOW);
    delay(500);
  }
  #ifdef SigfoxDeb
  mySerial.print("\n\n\n\rID: ");
  mySerial.println(ID);
  mySerial.print("PAC: ");
  mySerial.println(PAC);
  #endif
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    leer_info();
    delay(2000);
  }
}

void enviarcomandoATSigfox(char* comandoAT)
{
  unsigned long x=0;
  #ifdef SigfoxDeb
  mySerial.print("\r\n\tSigfox-->");
  mySerial.println(comandoAT);
  #endif
  while( Serial.available() > 0) Serial.read();
    x = 0;
  memset(RespuestaSigfox, '\0',sizeof(RespuestaSigfox)); 
  Serial.print(comandoAT);
  Serial.print("\r\n");
  while(true)
  {
    if(Serial.available() != 0)
    {   
      RespuestaSigfox[x] = Serial.read();
      x++;
      if (strstr(RespuestaSigfox, "\n") != NULL)
      {
        #ifdef SigfoxDeb
        mySerial.print("Comando OK\n\r");
        mySerial.println(RespuestaSigfox);
        #endif
        break;
      }
    }
  }
}
void downlink_SIGFOX(char* comandoAT)
{
  unsigned long x=0;
  int c=0;
  #ifdef SigfoxDeb
  mySerial.print("\r\n\tSigfox-->");
  mySerial.println(comandoAT);
  #endif
  while( Serial.available() > 0) Serial.read();
    x = 0;
  memset(RespuestaSigfox, '\0',sizeof(RespuestaSigfox)); 
  Serial.print(comandoAT);
  Serial.print("\r\n");
  while(true)
  {
    //Serial.print(Serial.available() );
    if(Serial.available() != 0)
    {   
      RespuestaSigfox[x] = Serial.read();
      x++;
      if (strstr(RespuestaSigfox, "\n") != NULL)
      {
        c++;
      }
      if(x>30)
      {
        #ifdef SigfoxDeb
        mySerial.print("Comando OK\n\r");
        mySerial.println(RespuestaSigfox);
        #endif
        break;
      }
    }
  }
}
