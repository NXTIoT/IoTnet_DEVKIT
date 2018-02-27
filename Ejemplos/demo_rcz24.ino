#define SigfoxDeb
#include <SoftwareSerial.h>
#ifdef SigfoxDeb
SoftwareSerial mySerial(0, 1); // RX, TX
#endif
const int boton=6;
const int led6=8;
int zona;
char RespuestaSigfox[50];
char ID[51];
char PAC[51];
char frec[51];

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
  Check_zona();
  Serial.print("Configuracion para Zona: ");
  Serial.println(zona);
}

void leer_info()
{
  digitalWrite(7, HIGH);
  delay(1000);
  enviarcomandoATSigfox("AT");
  enviarcomandoATSigfox("AT$I=10");
  strcpy(ID,RespuestaSigfox);
  enviarcomandoATSigfox("AT$I=11");
  strcpy(PAC,RespuestaSigfox);
  enviarcomandoATSigfox("AT$RC"); 
  enviarcomandoATSigfox("AT$SF=0102030405");
  digitalWrite(7, LOW);
  delay(500);
  Serial.print("\n\n\n\rID: ");
  Serial.println(ID);
  Serial.print("PAC: ");
  Serial.println(PAC);
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
    delay(1400);
    if(digitalRead(boton)==LOW)
    {
      cambio();
      delay(2000);
    }
    else
    {
      leer_info();
      delay(2000);
    }
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

void cambio()
{
  digitalWrite(7, HIGH);
  delay(1000);
  if(zona==2)
  {
    enviarcomandoATSigfox("AT$DR=922300000");
    enviarcomandoATSigfox("ATS400=<00000000><F0000000><0000001F>,63");
    enviarcomandoATSigfox("AT$WR");
    enviarcomandoATSigfox("AT$RC");
    zona=4;
  }
  else
  {
    enviarcomandoATSigfox("AT$DR=905200000");
    enviarcomandoATSigfox("ATS400=<000001FF><00000000><00000000>,1");
    enviarcomandoATSigfox("AT$WR");
    enviarcomandoATSigfox("AT$RC");
    zona=2;
  }
  digitalWrite(7, LOW);
  Check_zona();
  Serial.print("Configuracion para Zona: ");
  Serial.println(zona);
}
void Check_zona()
{
  String res;
  digitalWrite(7, HIGH);
  delay(1000);
  enviarcomandoATSigfox("AT$DR?");
  strcpy(frec,RespuestaSigfox);
  Serial.print("Frec: ");
  Serial.println(frec);
  for(int i=0;i<9;i++)
  {
      res+=frec[i];
  }
  if (res=="905200000")
  {
    zona=2;
    digitalWrite(led6, LOW);
  }
  else
  {
    zona=4;
    digitalWrite(led6, HIGH);
  }
  digitalWrite(7, LOW);
}
