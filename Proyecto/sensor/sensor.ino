#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>

WiFiServer server(80);
WiFiClient client;

const int AirValue = 2540;    // Valor máximo en aire seco
const int WaterValue = 1620;  // Valor mínimo en agua
const int SensorPin = 34;
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

void setup() {
    Serial.begin(115200);
    pinMode(SensorPin, INPUT);
    
    WiFi.disconnect();
    delay(3000);
    Serial.println("Iniciando");
    WiFi.begin("Napophone", "lmaoxdxd");
    
    while (!(WiFi.status() == WL_CONNECTED)) {
        Serial.print("......");
        delay(300);
    }
    
    Serial.println("Conexion establecida con el SSID!");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop() {
    // Leer sensor antes de cualquier operación web
    soilMoistureValue = leerHumedad();
    
    // Calcular porcentaje
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    soilmoisturepercent = constrain(soilmoisturepercent, 0, 100);
    
    // Debug por Serial
    Serial.print("Valor crudo: ");
    Serial.print(soilMoistureValue);
    Serial.print(" | Humedad: ");
    Serial.print(soilmoisturepercent);
    Serial.println("%");
    
    // Atender cliente web
    client = server.available();
    if (client) {  // Solo si hay un cliente conectado
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // Enviar respuesta HTTP
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        // Página HTML
                        client.println("<!DOCTYPE HTML>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>MiESP32</title>");
                        client.println("<meta http-equiv='refresh' content='5'/>");
                        client.println("<style>");
                        client.println("body { font-family: Arial, sans-serif; margin: 20px; background-color: #f0f0f0; }");
                        client.println(".container { background-color: white; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }");
                        client.println(".humidity { font-size: 24px; color: #0066cc; margin: 20px 0; }");
                        client.println(".sensor { color: #666; margin: 10px 0; }");
                        client.println(".time { color: #666; }");
                        client.println("</style>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<div class='container'>");
                        
                        client.println("<h1>Monitor de Humedad del Suelo</h1>");
                        
                        client.println("<div class='humidity'>");
                        client.print("Humedad actual: ");
                        client.print(soilmoisturepercent);
                        client.println("%</div>");
                        
                        client.println("<div class='sensor'>");
                        client.print("Valor del sensor: ");
                        client.print(soilMoistureValue);
                        client.println("</div>");
                        
                        client.println("<div class='time'>");
                        client.print("Tiempo activo: ");
                        client.print(millis() / 1000);
                        client.println(" segundos</div>");
                        
                        client.println("</div>");
                        client.println("</body>");
                        client.println("</html>");
                        
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        client.stop();
    }
    
    delay(100);  // Pequeña pausa para estabilidad
}
