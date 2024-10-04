#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  15     //reset
#define SS_PIN   21     //SDA

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);    
  SPI.begin();          
  mfrc522.PCD_Init();    
  Serial.println("Sistema iniciado. Esperando una tarjeta RFID...");
}

void loop() {
  delay(500); 
  
  // Revisar si hay una tarjeta RFID presente
  if (mfrc522.PICC_IsNewCardPresent()) {
    delay(50); // Pausa adicional para asegurar la lectura
    
    // Leer la tarjeta detectada
    if (mfrc522.PICC_ReadCardSerial()) {
      
      Serial.println();
      Serial.println("***************************");
      Serial.println("Tarjeta leída. El número de UID (identificador) es:");

      // Verificar si el UID tiene un tamaño válido antes de imprimir
      if (mfrc522.uid.size > 0) {
        // Imprimir el UID de la tarjeta en formato hexadecimal
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println();
      } else {
        Serial.println("No se pudo leer el UID.");
      }

      Serial.println("***************************");
      Serial.println("Esperando 5 segundos para leer la siguiente tarjeta...");
      Serial.println();
  
      mfrc522.PICC_HaltA();
      delay(5000);
    }
  } else {
    Serial.println("No se detecta ninguna tarjeta... esperando una.");
  }
}
