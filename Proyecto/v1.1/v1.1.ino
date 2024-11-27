/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2L9FDv366"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "FTYckZKidHxw13PXKrmS7ZeWFJhay3ca"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Napophone";
char pass[] = "lmaoxdxd";

const int AirValue = 73;    // Valor máximo en aire seco
const int WaterValue = 61;  // Valor mínimo en agua
const int SensorPin = A0;//GPIO 2
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
   // Reading sensor from hardware analog pin A0
  soilMoistureValue = leerHumedad();
    Serial.println(soilMoistureValue);
    // Calcular porcentaje
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    soilmoisturepercent = constrain(soilmoisturepercent, 0, 100);

    Serial.print(soilmoisturepercent);
    Serial.println("%");
  Blynk.virtualWrite(V1, soilmoisturepercent);  
}

void setup()
{
  // Debug console
  Serial.begin(115200);
   pinMode(SensorPin, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  //pinMode(SensorPin, INPUT);
  timer.setInterval(10000L, myTimer);
}

void loop()
{
  // Runs all Blynk stuff
  Blynk.run(); 
  
  // runs BlynkTimer
  timer.run(); 
}
