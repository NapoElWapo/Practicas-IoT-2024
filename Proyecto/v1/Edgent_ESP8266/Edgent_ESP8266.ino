/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL2MmkoOgqI"
#define BLYNK_TEMPLATE_NAME "Sensor Humedad"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

const int AirValue = 2540;    // Valor máximo en aire seco
const int WaterValue = 1620;  // Valor mínimo en agua
const int SensorPin = 2;//GPIO 2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

// Función para leer el sensor
int leerHumedad() {
    // Tomar promedio de lecturas
    int suma = 0;
    for(int i = 0; i < 5; i++) {
        suma += analogRead(SensorPin);
        delay(10);
    }
    return suma / 5;
}

BlynkTimer timer; 

void myTimer() 
{
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  Blynk.virtualWrite(V0, soilmoisturepercent);  
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(SensorPin, INPUT);
  delay(100);
  timer.setInterval(1000L, myTimer);
  BlynkEdgent.begin();
}

void loop() {
  // Reading sensor from hardware analog pin A0
  soilMoistureValue = leerHumedad();
    
    // Calcular porcentaje
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    soilmoisturepercent = constrain(soilmoisturepercent, 0, 100);

    Serial.print(soilmoisturepercent);
    Serial.println("%");
  
  // Runs all Blynk stuff
  Blynk.run(); 
  
  // runs BlynkTimer
  timer.run(); 
}
