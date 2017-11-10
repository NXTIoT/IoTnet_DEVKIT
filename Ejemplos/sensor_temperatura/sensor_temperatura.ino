#define SigfoxDeb
#include <SoftwareSerial.h>
#ifdef SigfoxDeb
SoftwareSerial mySerial(0, 1); // RX, TX
#endif

const int sensorPin = A5;
const float baselinetime=20.0;
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
  //pinMode(4, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);
  #ifdef SigfoxDeb
  mySerial.println("\n\n\n\n\n\n\n\n\rInicio");
  #endif
}

void leer_sensor()
{
  String bufer="AT$SF=";
  char payload[20];
  int sensorVal=analogRead(sensorPin);
  float voltaje=(sensorVal/1024.0)*5;
  Serial.print("Voltaje: ");
  Serial.println(voltaje); 
  Serial.print("Grados Cº: ");
  float temp=((voltaje)*100)+1;
  Serial.println(temp);
  //convierte el dato a bytes y lo agrega a nuestro mensaje a enviar
  byte* a1 = (byte*) &temp;  
  String str1;
  for(int i=0;i<4;i++)
  {
    str1=String(a1[i], HEX);
    if(str1.length()<2)
    {
      bufer+=0+str1;
    }
    else
    {
      bufer+=str1;
    }
  }
  bufer.toCharArray(payload,16);
  digitalWrite(7, HIGH);
  delay(1000);
  enviarcomandoATSigfox("AT");
  enviarcomandoATSigfox("AT$RC");
  enviarcomandoATSigfox(payload);
  digitalWrite(7, LOW);
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    leer_sensor();
    delay(2000);
  }
}

void enviarcomandoATSigfox(char* comandoAT){
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
  while(true){
    if(Serial.available() != 0){   
      RespuestaSigfox[x] = Serial.read();
      x++;
      if (strstr(RespuestaSigfox, "\n") != NULL){
        #ifdef SigfoxDeb
        mySerial.print("Comando OK\n\r");
        mySerial.println(RespuestaSigfox);
        #endif
        break;
      }
    }
  }
}
