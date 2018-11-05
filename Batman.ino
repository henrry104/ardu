
#include <LiquidCrystal.h>    //Incluimos libreria lcd
#include "DHT.h"              

#define DHTTYPE DHT22   
const int DHTPin = A1;   // El pin al que estara conectado el sensor

DHT dht(DHTPin, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int boton1 = 4;   // boton 1 conectado al pin4
int boton2 = 3;   // boton 2 conectado al pin3
int boton3 = 2;   // boton 3 conectado al pin2
int opcion = 0;   //para seleccionar la opcion del menu
int estadoboton1 = 0;
int estadoboton2 = 0;

void setup()
{
  lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas
  dht.begin();                //Se inicia el sensor
  pinMode(2, INPUT);          //definimos el pin como entrada
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(DHTPin, INPUT);
}

void loop()
{
  if (digitalRead(boton1) == LOW and estadoboton1 == 0) {   //comprobamos si el boton1 esta pulsado
    opcion = 1;
    estadoboton2 = 1; //bloqueado
    while (digitalRead(boton1) == LOW);
  }

  if (digitalRead(boton2) == LOW and estadoboton2 == 0 ) { // si el boton2 esta pulsado
    opcion = 2;
    estadoboton1 = 1; //bloqueado
    while (digitalRead(boton2) == LOW);
  }
  
  if (opcion == 1) {
    float  t = dht.readTemperature(); //lee la temperatura
    lcd.setCursor(0, 0);    //
    lcd.print("TEMP: ");
    lcd.print(t);
    lcd.print((char)223);   //SIMBOLO º
    lcd.print("C");
    lcd.setCursor(0, 1);    // linea 2, posicion 0
    lcd.print("      3.Volver      ");
    if (digitalRead(boton3) == LOW) {   //verificamos si el boton2 esta pulsado
      opcion = 0;
      estadoboton2 = 0; //desbloqueado
      while (digitalRead(boton3) == LOW);
    }
  } else if (opcion == 2) {
    float h = dht.readHumidity(); //Se lee la humedad
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(h);
    lcd.print(" %");
    lcd.setCursor(0, 1);    //
    lcd.print("      3.Volver      ");
    if (digitalRead(boton3) == LOW) {
      opcion = 0;
      estadoboton1 = 0; //desbloqueado
      while (digitalRead(boton3) == LOW);
    }
  } else {
    lcd.setCursor(0, 0);    // Ponte en la line 1, posicion 3
    lcd.print("  SELECCIONE  ");
    lcd.setCursor(0, 1);    // Ponte en la line 2, posicion 0
    lcd.print("1.TEMPER 2.HUMED");
  }
}
