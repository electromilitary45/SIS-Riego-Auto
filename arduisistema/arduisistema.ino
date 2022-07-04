
 
/*
Otras configuraciones para LCD
(0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2)
--Palabras Reservadas--
lcd.print("");
lcd.setCursor(0,0);
lcd.display();
lcd.noDisplay();
---
*/

//-------------------------------------------------------------------------------------------------------------------
//---LIBRERIA LCD---
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

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
  
  //--Ini SENSOR DHT11
  dht.begin();


  //---configuracion PINES LED---
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAma, OUTPUT);

}

void loop() {
 
  //----CAPTURA DATOS SENSORES---
  valor_sensorHumedad=map(analogRead(pin_sensorHumedad),0,1023,200,0); //datos SENSOR HUMEDAD TIERRA
  humedadDh = dht.readHumidity();
  tempDh = dht.readTemperature();


  if(valor_sensorHumedad < 10){
    /*
    Se prenden todos los leds para decir que el modulo esta fuera de Tierra
    */
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
    lcd.print("temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
    
  }else if(valor_sensorHumedad >10 && valor_sensorHumedad <40){
     /*
    Se prenden todos los leds para decir que la tierra esta seca
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
    lcd.print("temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
    
  }else if(valor_sensorHumedad >40 && valor_sensorHumedad <85){
    /*
    Se prenden todos los leds para decir que la tierra esta Humeda
    */
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAma, HIGH);
    digitalWrite(ledVerde, LOW);
    /*
    Se muestra por pantalla los datos del sensor de tierra
    */
    lcd.setCursor(0,0);
    lcd.print("Tierra hum: ");
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    /*
    Se agregan los valores de Temperatura y humedad del DHT11
    */
    lcd.setCursor(0,1);
    lcd.print("temp:");
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
    lcd.print("temp:");
    lcd.print(tempDh);
    lcd.print(" Humd:");
    lcd.print(humedadDh);
    
    /*
    Se recarga la pantalla
    */
    delay(500);
    lcd.clear();
  }
  
  
  
  
  
  //delay(500);
  
}//fin void
