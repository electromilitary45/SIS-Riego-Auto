/*
Otras configuraciones para LCD
(0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2)
*/
//-------------------------------------------------------------------------------------------------------------------
//---LIBRERIA LCD---
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//pines LCD
// SDA = A4
// SDL = A5

//---LIBRERIA DHT11--
#include <DHT.h>
#include <DHT_U.h>


//--- PINES SENSOR DHT11 y variables
int pin_sensorDHT11=10;
int tempDh,humedadDh;
DHT dht(pin_sensorDHT11,DHT11);

//---PINES Sensor Humedad TIERRA y variables--
int valor_sensorHumedad;
int pin_sensorHumedad=A0;

//---Bomba Agua--
int pin_bombaAgua=9;

//---PINES LEDS COLORES--
int ledVerde = 13;
int ledAma =12;
int ledRojo =11;

//-------------PROGRAMA PRINCIPAL----------

void setup() {
  //CONFIGURACION LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  //configuracion SENSOR HUMEDAD SUELO
  
  //--Ini SENSOR DHT11 Sensor humedad temp ambiente
  dht.begin();


  //---SETUP PINES LED---
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAma, OUTPUT);

  //--Setup de rele
  pinMode(pin_bombaAgua, OUTPUT);
}

void loop() {
 
  //----CAPTURA DATOS SENSOR Humedad tierra---
  valor_sensorHumedad=map(analogRead(pin_sensorHumedad),0,1023,200,0); //datos SENSOR HUMEDAD TIERRA
  //---ambiente
  humedadDh = dht.readHumidity(); 
  tempDh = dht.readTemperature();


  if(valor_sensorHumedad < 10){
    //Se desactiva la bomba para que no riegue
    digitalWrite(pin_bombaAgua, LOW);
    
    //Se prenden todos los leds para decir que el modulo esta fuera de Tierra
    digitalWrite(ledRojo, HIGH); 
    digitalWrite(ledAma, HIGH);
    digitalWrite(ledVerde, HIGH);
    
    /*
    Se avisa por pantalla que el sensor esta fuera de tierra
    Mas el valor del agua
    */
    lcd.setCursor(0,0);
    lcd.print("Desconectado: ");
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    
    /*
    Se agregan los valores de Temperatura y humedad del DHT11
    */
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
    
  }else if(valor_sensorHumedad >10 && valor_sensorHumedad <60){ //tierra seca
    
    //Se activa la bomba para que riegue
    
    digitalWrite(pin_bombaAgua, HIGH);

     /*
    Se prende led verde para decir que la tierra esta seca
    */
    
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAma, LOW);
    digitalWrite(ledVerde, HIGH);
    /*
    Se avisa por pantalla que el sensor esta fuera de tierra
    Mas el valor del agua
    */
    lcd.setCursor(0,0);
    lcd.print("TIERRA SECA: ");
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    /*
    Se agregan los valores de Temperatura y humedad del DHT11
    */
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
    
  }else if(valor_sensorHumedad >60 && valor_sensorHumedad <85){
    /*
    Se prende el amarrillo decir que la tierra esta Humeda
    */
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAma, HIGH);
    digitalWrite(ledVerde, LOW);
    /*
    Se muestra por pantalla los datos del sensor de tierra
    */
    lcd.setCursor(0,0);
    lcd.print("Tierra Hum: ");
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    /*
    Se agregan los valores de Temperatura y humedad del DHT11
    */
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
  }else if(valor_sensorHumedad >85){
    /*
    Se desavtiva la bomba para que riegue
    */
    digitalWrite(pin_bombaAgua, LOW);
    
    /*
    Se prenden todos los leds para decir que la tierra esta Humeda
    */
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAma, LOW);
    digitalWrite(ledVerde, LOW);
    
    /*
    Se muestra en pantalla los datos del sensor de tierra
    */
    lcd.setCursor(0,0);
    lcd.print("EXCESO :");
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    
    /*
    Se agregan los valores de Temperatura y humedad del DHT11
    */
    lcd.setCursor(0,1);
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
  }

}//fin void
