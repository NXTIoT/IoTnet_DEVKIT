//Programa de ejemplo utilizando el sensor ultrasonico HC-SR04
//En este caso el dato en flotante es transformado a su representacion en hexadecimal en formato float 32 little-endian
#define trigPin 3
#define echoPin 2
const int boton=6;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);
}

void leer_distancia()
{
  //AT$SF= comando para mandar la informacion por sigfox
  //Maximo 12 bytes
  String bufer="AT$SF=";
  //*************************
  String bufer2="\n";
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
  //Conversion de nuestro dato a bytes
  //Un dato en flotante ocupa 4 bytes
  byte* a1 = (byte*) &distancia;
  String str1;
  //agregamos al comando AT$SF nuestra informacion a enviar
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
  delay(500);
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  { 
    leer_distancia();
    delay(1000);
  } 
}
