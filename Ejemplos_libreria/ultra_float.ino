#include "NXTIoT_dev.h"

NXTIoT_dev  mysigfox;
#define trigPin 3
#define echoPin 2

const int boton=6;
const int sensorPin = A0;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(boton, INPUT);
}

void leer_distancia()
{
  float duracion, distancia ;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);       
  delayMicroseconds(10);            
  digitalWrite(trigPin, LOW);       
  duracion = pulseIn(echoPin, HIGH) ;
  distancia = duracion / 2 / 29.1;
  Serial.print("Distancia: ") ;
  Serial.println(distancia) ;
  mysigfox.initpayload();
  mysigfox.addfloat(distancia);
  mysigfox.sendmessage();
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    leer_distancia();
    delay(1000);
  } 
}
