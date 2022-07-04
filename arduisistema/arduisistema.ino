 
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

//

//---PINES Sensor Humedad--
int valor_sensorHumedad;
int pin_sensorHumedad=A0;

//---Bomba Agua--

//---PINES LEDS--
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
  
  //---configuracion PINES LED---
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAma, OUTPUT);

}

void loop() {
  /*
  lcd.setCursor(0,0);
  lcd.print("HOLA");
  delay(600);
  lcd.clear();
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("MAMI");
  delay(600);
  lcd.clear();
  */
  valor_sensorHumedad=map(analogRead(pin_sensorHumedad),0,1023,200,0);

  if(valor_sensorHumedad < 10){
    /*
    Se prenden todos los leds para decir que el modulo esta fuera de Tierra
    */
    digitalWrite(ledRojo, HIGH); 
    digitalWrite(ledAma, HIGH);
    digitalWrite(ledVerde, HIGH);
    /*
    Se avisa por pantalla que el sensor esta fuera de tierra
    */
    lcd.setCursor(0,0);
    lcd.print("Sensor Desconectado");
    lcd.setCursor(0,1);
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    delay(500);
    lcd.clear();
    
  }else if(valor_sensorHumedad >10 && valor_sensorHumedad <40){
    
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAma, LOW);
    digitalWrite(ledVerde, HIGH);
    lcd.setCursor(0,0);
    lcd.print("TIERRA MUY SECA");
    lcd.setCursor(0,1);
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    delay(500);
    lcd.clear();
    /*
    lcd.setCursor(0, 0);
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    delay(500);
    lcd.clear();*/
  }else if(valor_sensorHumedad >40 && valor_sensorHumedad <85){
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAma, HIGH);
    digitalWrite(ledVerde, LOW);
    lcd.setCursor(0,0);
    lcd.print("TIERRA HUMEDA");
    lcd.setCursor(0,1);
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    delay(500);
    lcd.clear();
  }else if(valor_sensorHumedad >85 && valor_sensorHumedad <=100){
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAma, LOW);
    digitalWrite(ledVerde, LOW);
    lcd.setCursor(0,0);
    lcd.print("EXCESO DE AGUA");
    lcd.setCursor(0,1);
    lcd.print(valor_sensorHumedad);
    lcd.print("%");
    delay(500);
  }
  
  
  
  
  
  //delay(500);
  
}//fin void
