/*
Mediante el servicio de Geolocalización de Sigfox se han obtenido las siguientes coordenadas:

  "time": {time},
  "deviceId": "{device}",
  "seqNumber":{seqNumber}


locate on Google Maps: http://maps.google.com/maps?z=12&t=m&q={lat}+{lng}

*/

/****************************************

lat::float:32:little-endian lng::float:32:little-endian temp::int:8 bat::int:8

https://api.thinger.io/v1/users/{user_id}/buckets/{bucket_id}/data

*/

/*
{
"device" : "{device}",
"longitud" : "{customData#lng}",
"latitud" : "{customData#lat}",
"temp" : "{customData#temp}",
"bateria" : "{customData#bat}"
}
*/
//Programa de ejemplo para enviar informacion por medio de Sigfox
//representacion en hexadecimal de un entero (1 byte) o de un 1 flotante a 32 bits en little-endian
//Al presionar el boton azul se envia un mensaje
const int boton=6;
const int enable=7;
int randNumber;
//*****************************************************
String bufer; //variable donde guardaremos nuestro payload
String bufer2="\n";   //agregamos un salto de linea al final de nuestro payload
//*****************************************************
void setup() 
{
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(enable, OUTPUT);   //enable modulo wisol
}

void loop() 
{
  //if (digitalRead(boton)==LOW)
  //{
    function();
    delay(120000);
  //} 
}
void function()
{
  //-----------------------------------------------------
  //tu codigo
  

  
  /*-----------------------------------------------------
  //inicializamos el payload cargando el comando para enviar
  //AT$SF= comando para mandar la informacion por sigfox Maximo 12 bytes*/
  bufer="AT$SF=";
  
  /**************************************************
  agregamos nuestra variable al payload a enviar*/

  //add_int(variable_int); //un entero ocupa 1 byte
  //add_float(variable_float); //un flotante ocupa 4 bytes
  

  //enviamos nuestro dato por Sigfox
  send_message(bufer);
}
void add_float(float var1) //funcion para agregar flotantes al payload en formato little-endian
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
void add_int(int var2)    //funcion para agregar enteros al payload (hasta 255)
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
void send_message(String payload)
{
  //agregamos el salto de linea "\n"
  bufer+=bufer2;
  //*******************
  //Habilitamos el modulo Sigfox
  digitalWrite(enable, HIGH);
  delay(1000);
  //Reset del canal para asegurar que manda en la frecuencia correcta
  Serial.print("AT$RC\n"); 
  //************************
  //Enviamos la informacion por sigfox
  Serial.print(bufer);
  delay(3000);
  //deshabilitamos el modulo Sigfox
  digitalWrite(enable, LOW);
}
