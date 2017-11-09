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
  String bufer="AT$SF=";
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
  byte* a1 = (byte*) &distancia;
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
  bufer+=bufer2;
  digitalWrite(7, HIGH);
  delay(1000);
  Serial.print("AT$RC\n");
  Serial.print(bufer);
  delay(3000);
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

