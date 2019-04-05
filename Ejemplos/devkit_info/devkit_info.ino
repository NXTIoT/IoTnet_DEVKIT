#define SigfoxDeb
#include <SoftwareSerial.h>
#ifdef SigfoxDeb
SoftwareSerial mySerial(0, 1); // RX, TX
#endif
const int boton=6;
char RespuestaSigfox[50];
char ID[51];
char PAC[51];

void setup() 
{
  Serial.begin(9600);
  #ifdef SigfoxDeb
  mySerial.begin(9600);
  #endif
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);
  #ifdef SigfoxDeb
  mySerial.println("\n\n\n\n\n\n\n\n\rInicio");
  #endif
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
  enviarcomandoATSigfox("AT$SF=486F6C61206D756E646F");
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
