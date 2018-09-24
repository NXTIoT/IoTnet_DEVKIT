//Programa de ejemplo utilizando el sensor de temperatura LM35
//En este caso el dato en entero es transformado a su 
//representacion en hexadecimal en 1 flotante a 32 bits en little-endian
const int boton=6;
const int sensorPin = A0;
//*****************************************************
String bufer; //variable donde guardaremos nuestro payload
String bufer2="\n";   //agregamos un salto de linea al final de nuestro payload
//*****************************************************
void setup() 
{
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);   //enable modulo wisol
}

void leer_temperatura()
{
  int sensorVal=analogRead(sensorPin);
  float voltaje=((sensorVal/1024.0))*5;
  Serial.print("Voltaje: ");
  Serial.println(voltaje); 
  Serial.print("Grados Cº: ");
  float temp=((voltaje)*100);
  Serial.println(temp);
  
  //-----------------------------------------------------
  //AT$SF= comando para mandar la informacion por sigfox
  //Maximo 12 bytes
  bufer="AT$SF=";
  //-----------------------------------------------------
  //agregamos nuestro valor de la temperatura al payload a enviar
  add_float(temp); //un flotante ocupa 4 bytes

  //enviamos nuestro dato por Sigfox
  send_message(bufer);
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    leer_temperatura();
    delay(1000);
  } 
}
void add_float(float var1) //funcion para agregar flotantes al payload
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
  digitalWrite(7, HIGH);
  delay(1000);
  //Reset del canal para asegurar que manda en la frecuencia correcta
  Serial.print("AT$RC\n"); 
  //************************
  //Enviamos la informacion por sigfox
  Serial.print(bufer);
  delay(3000);
  //deshabilitamos el modulo Sigfox
  digitalWrite(7, LOW);
}
