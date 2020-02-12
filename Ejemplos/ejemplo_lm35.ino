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
  if (digitalRead(boton)==LOW)
  {
    function();
    delay(2000);
  } 
}
void function()
{
  //-----------------------------------------------------
  //tu codigo
  float sum=0.0;
  float promedio=0.0;
  int muestras=30;
  for (int i=0;i<muestras;i++)
  {
    sum=sum+((analogRead(A0)/1023.0)*5.0);
    delay(100);
  }
  promedio=sum/muestras;
  Serial.print("promedio: ");
  Serial.println(promedio);
  float temp=promedio*100.0;
  Serial.print("Temp: ");
  Serial.println(temp);

  
  /*-----------------------------------------------------
  //inicializamos el payload cargando el comando para enviar
  //AT$SF= comando para mandar la informacion por sigfox Maximo 12 bytes*/
  bufer="AT$SF=";
  
  /**************************************************
  agregamos nuestra variable al payload a enviar*/
  add_float(temp);

  //enviamos nuestro dato por Sigfox
  //send_message(bufer);
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
