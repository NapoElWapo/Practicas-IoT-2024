#include <splash.h>

#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ANCHO 128
#define OLED_ALTO 64

#define OLED_RESET -1

#define DIRECCION_PANTALLA 0X3C
Adafruit_SSD1306 display = Adafruit_SSD1306(OLED_ANCHO,OLED_ALTO, &Wire, OLED_RESET);

#define TRIG 25
#define ECHO 26

#define VEL_SONIDO 0.034
long duracion;
float distanciaCm;

void setup()
{
  //HUMEDAD Y TEMPERATURA
  Serial.begin(115200);

  dht.begin();//inicializar el sensor de humedad y temperatura

  //OLED
  Wire.begin(21,22);
  display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_PANTALLA);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
  display.print("NapOled");
  display.display();

  //ULTRASONICO
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
}

void loop()
{
  
  delay(2000); //Es un sensor lento, por lo que hay que darle tiempo.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }

  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("% Temperatura: "));
  Serial.print(t);
  Serial.println(F("°C "));

  // Clears the trigPin
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duracion = pulseIn(ECHO, HIGH);
  
  // Calculate the distance
  distanciaCm = duracion * VEL_SONIDO/2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distancia (cm): ");
  Serial.println(distanciaCm);


  
  display.setCursor(0, 0);
  display.print("Humedad: ");
  display.print(h);
  display.println("%");
  display.print("Temperatura: ");
  display.print(t);
  display.write(0xF8);
  display.println("C");
  display.print("Distancia (cm): ");
  display.println(distanciaCm);

  display.display();
  display.clearDisplay();



  
}
