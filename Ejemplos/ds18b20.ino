#include <DallasTemperature.h>
 
// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 2;
const int boton=6; 
// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    pinMode(boton, INPUT);
    pinMode(7, OUTPUT);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin(); 
}

void leer_temp()
{
  String bufer="AT$SF=";
  String bufer2="\n";
  // Mandamos comandos para toma de temperatura a los sensores
    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura sensor: ");
    float temp=sensorDS18B20.getTempCByIndex(0);
    Serial.print(temp);
    Serial.println(" C");
    byte* a3 = (byte*) &temp;
  String str3;
  //agregamos al comando AT$SF nuestra informacion a enviar
  for(int i=0;i<4;i++)
  {
    str3=String(a3[i], HEX);
    if(str3.length()<2)
    {
      bufer+=0+str3;
    }
    else
    {
      bufer+=str3;
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
    delay(1000); 
}
 
void loop() {
    if (digitalRead(boton)==LOW)
  {
    leer_temp();
    delay(2000);
  }
}
