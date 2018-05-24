#include "Arduino.h"
#include "NXTIoT_dev.h"

NXTIoT_dev::NXTIoT_dev()
{
	Serial.begin(9600);
	pinMode(enable_module, OUTPUT);   //enable modulo wisol
	bufer="AT";
}
void NXTIoT_dev::initpayload()
{
	bufer="AT$SF=";
}

void NXTIoT_dev::sendmessage()
{
  //agregamos el salto de linea "\n"
  bufer+="\n";
  //*******************
  //Habilitamos el modulo Sigfox
  digitalWrite(enable_module, HIGH);
  delay(1000);
  //Reset del canal para asegurar que manda en la frecuencia correcta
  Serial.print("AT$RC\n"); 
  //************************
  //Enviamos la informacion por sigfox
  Serial.print(bufer);
  delay(3000);
  //deshabilitamos el modulo Sigfox
  digitalWrite(enable_module, LOW);
}
void NXTIoT_dev::addfloat(float var1) //funcion para agregar flotantes al payload
{
  byte* a1 = (byte*) &var1;    //convertimos el dato a bytes
  String str1;
  //agregamos al comando AT$SF= nuestra informacion a enviar
  for(int i=0;i<4;i++)
  {
    str1=String(a1[i], HEX);    //convertimos el valor hex a string 
    if(str1.length()<2)
    {
      bufer+=0+str1;    //si no, se agrega un cero
    }
    else
    {
      bufer+=str1;    //si esta completo, se copia tal cual
    }
  }
}
void NXTIoT_dev::addint(int var2)    //funcion para agregar enteros al payload (hasta 255)
{
  byte* a2 = (byte*) &var2; //convertimos el dato a bytes
  String str2;
  str2=String(a2[0], HEX);  //convertimos el valor hex a string 
  //verificamos si nuestro byte esta completo
  if(str2.length()<2)
  {
    bufer+=0+str2;    //si no, se agrega un cero
  }
  else
  {
    bufer+=str2;     //si esta completo, se copia tal cual
  }
}