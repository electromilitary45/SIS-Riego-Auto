
/* SISTEMA DE RIEGO AUTOMÁTICO CON SENSOR DE HUMEDAD DE SUELO, SENSOR
DE HUMEDAD DE AIRE Y SENSOR DE LUZ */
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <DHT.h>
 int ledVerde = 12;
int ledRojo = 11;
int ledAmarillo = 13;


 int lluvValue =0;
int lluvia;
int sensorLluvia = A3;
#include <SimpleDHT.h>
// Librería  <SimpleDHT.h> del sensor de temperatura y humedad relativa
#include <SPI.h>
//Librería <SPI.h> del motor DC compatible con la minibomba de agua DC

//Se define variable del sensor de humedad en el suelo en el pin A0
#define ldr_pin A5
//Defino variable del sensor de fotoresistencia LDR en el pin A5

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
// Se declara la variable pinDHT11 y lo asocio al pin 2
SimpleDHT11 dht11;
int ldr_value = 0;
//Se declara la variable ldr_value (fotoresistencia) y 

int VO = 4;
int RS = 5;
int E = 6;
int D4 = 7;
int D5 = 8;
int D6 = 9;
int D7 = 10;
int temperature;
int humidity_in_air;
int ground_humidity_value;
int humidity_sensor_pin = A0;
bool noche;
char momento;
DHT dht (pinDHT11, DHT11);
LiquidCrystal lcd (RS, E, D4, D5 ,D6, D7);

int water_pump_pin = 3;
//Se declara la variable mini bomba de agua y lo asocio al pin 3
int water_pump_speed = 255;
//Velocidad de la minibomba de agua oscila entre 100 como mínimo y 255 como máximo. Yo he //elegido 255 pero ustedes pueden elegir la que estimen conveniente. A más velocidad, mayor //bombeo de agua

void setup() {
   dht.begin();
 
  
  lcd.begin(16, 2); 
  analogWrite(VO, 50); //contraste
  Serial.begin(9600);
  pinMode( ledRojo, OUTPUT) ;
  pinMode( ledVerde, OUTPUT) ;
  pinMode( ledAmarillo, OUTPUT) ;
}

void loop() {
   // start working...
   // read with raw sample data.
 humidity_in_air = dht.readHumidity();
 temperature = dht.readTemperature();
 int ldr_value = map(analogRead(ldr_pin), 1023, 0, 50, 0);
 int ground_humidity_value = map(analogRead(humidity_sensor_pin), 0, 1023, 100, 0);
 int lluvValue =map (analogRead(sensorLluvia), 1023, 0,100, 0);
 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Regando");  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.print("C");
    lcd.print("Luz:");
    lcd.print(ldr_value);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Hum.suelo:");
    lcd.print(ground_humidity_value);
    lcd.print("%");

 
 

  // Ground humidity value in %
// Mide la humedad en el suelo en % y muestra el resultado
  
  
  Serial.print("Ground humidity: ");
  Serial.print(ground_humidity_value);
  Serial.println("%");
   if(ground_humidity_value < 50){
   digitalWrite( ledRojo, HIGH);
   
  }else{
    digitalWrite( ledRojo, LOW) ;  
  }

 
  // Light value in %
// Mide la luminosidad en % y muestra el resultado e indica si es de noche

  
  Serial.print("Light: ");
  Serial.print(ldr_value);
  Serial.println("%");
  Serial.println("*******************************");


  
  
Serial.print("lluvia:");
Serial.print(lluvValue);
Serial.println(" C");

   if(lluvValue > 15){
   digitalWrite( ledAmarillo, HIGH);
   
   }
  else{
    digitalWrite( ledAmarillo, LOW);
    Serial.println("NO Detectada lluvia");  
   }
    

   

//**************************************************************
// Condiciones de riego 
// Si la humedad en el suelo es igual o inferior al 50%, si la luminosidad es inferior al 15%,
// Si la temperatura es inferior al 30%, entonces el sistema de riego riega. 
// En caso de que no se  cumpla alguno o ninguno de los 3 requisitos anteriores,
// el sistema de riego no riega
//**************************************************************

      
      
{ if( ground_humidity_value <= 50 && ldr_value < 10 && temperature < 30 && lluvValue < 15  ) {
 digitalWrite(water_pump_pin, HIGH);
 if(water_pump_pin, HIGH){
   digitalWrite( ledVerde, HIGH);
   //digitalWrite (ledRojo, LOW);
  }else{
    digitalWrite( ledVerde, LOW) ; 
    
  }
 Serial.println("Irrigate");
 analogWrite(water_pump_pin, water_pump_speed);
//El motor de la bomba de agua arranca con la velocidad elegida anteriormente en el código
 }


 else{
 digitalWrite(water_pump_pin, LOW);
 Serial.println("Do not irrigate");
 {
    digitalWrite( ledVerde, LOW) ; }
//El motor de la bomba de agua se para y no riega
 }
}

delay (300);
}
