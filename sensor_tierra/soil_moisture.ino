const int sensorPin = A0;
const int boton=6;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if (digitalRead(boton)==LOW)
  { 
    leer_sensor();
    delay(1000);
  }
}

void leer_sensor()
{
  String bufer="AT$SF=";
  String bufer2="\n";
  float voltaje=((analogRead(sensorPin)/1023.0)*5.0)-0.2;
  Serial.print("Voltaje: ");
  Serial.println(voltaje);
  float hum=(50-((50*(voltaje-1.27))/1.28));
  Serial.print("Humedad: ");
  Serial.println(hum);
  byte* a1 = (byte*) &hum;  
  String str1;
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
  bufer+=bufer2;
  digitalWrite(7, HIGH);
  delay(1000);
  Serial.print("AT$RC\n");
  Serial.print(bufer);
  delay(3000);
  digitalWrite(7, LOW);
  delay(500);
}
