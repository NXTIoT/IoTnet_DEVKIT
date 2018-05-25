#include "NXTIoT_dev.h" //incluimos la libreria

NXTIoT_dev  mysigfox;  //creamos una clase de tipo NXTIoT_dev llamada mysigfox

const int boton=6;    //declaramos el pin 6 donde esta conectado el boton, en caso de utilizarlo

void setup() 
{
  Serial.begin(9600);     
  pinMode(boton, INPUT); //Inicializamos el pin 6 como entrada
}

void funcion_que_hace_algo()
{
  //************************
  //tu codigo


  
  //************************
  mysigfox.initpayload();   //Inicializamos nuestro Payload (hasta 12 bytes)
  //mysigfox.addint(tu_variable);  //esta funcion agrega un entero de un byte (de 0 a 255 ó -127 a 127)
  //mysigfox.addfloat(tu_variable); //esta funcion agrega un flotante utilizando 4 bytes en formato little-endian
  mysigfox.sendmessage(); //enviamos la informacion 
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    funcion_que_hace_algo();
    delay(1000);
  } 
}
