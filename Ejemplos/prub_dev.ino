
const int boton=6;

void setup() 
{
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(1000);
}
void leer_info()
{
  Serial.print("AT$RC\n");
  Serial.print("AT$SF=1122\n");
}

void loop() 
{
  if (digitalRead(boton)==LOW)
  {
    leer_info();
    delay(1000);
  }
}

