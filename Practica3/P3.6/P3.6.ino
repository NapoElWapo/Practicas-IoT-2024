//D6 05 71 33 Tarjeta iteso
//C3 C6 B7 13 llavero

#include <SPI.h>    
#include <MFRC522.h>

#define RST_PIN  15           // reset
#define SS_PIN  21            // SDA
#define greenLed 12           
#define redLed 14             

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);          
  Serial.println("Inicializando el sistema...");
  SPI.begin();                 
  mfrc522.PCD_Init();         
  pinMode(greenLed, OUTPUT);  
  pinMode(redLed, OUTPUT);    
  Serial.println("Control de acceso:");
}

byte ActualUID[4];             

byte Usuario1[4] = {0xD6, 0x05, 0x71, 0x33}; 
byte Usuario2[4] = {0xCE, 0x50, 0xDF, 0xA9}; 

void loop() {


  Serial.println("a");
  
  if (mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("b");
   
    if (mfrc522.PICC_ReadCardSerial()) {
    
      Serial.print(F("Card UID:"));
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        ActualUID[i] = mfrc522.uid.uidByte[i]; 
      }
      Serial.print("     ");
      
      
      if (compareArray(ActualUID, Usuario1)) {
        Serial.println("Acceso concedido...");
        digitalWrite(greenLed, HIGH); 
        delay(1500);                  
        digitalWrite(greenLed, LOW);  
      } else if (compareArray(ActualUID, Usuario2)) {
        Serial.println("Acceso concedido...");
        digitalWrite(greenLed, HIGH); 
        delay(1500);                  
        digitalWrite(greenLed, LOW);  
      } else {
        Serial.println("Acceso denegado...");
        digitalWrite(redLed, HIGH);   
        delay(1500);                  
        digitalWrite(redLed, LOW);    
      }
      
      // Finaliza la lectura de la tarjeta actual
      mfrc522.PICC_HaltA();
    }
  }
}


boolean compareArray(byte array1[], byte array2[]) {

  if (array1[0] != array2[0]) return false;
  if (array1[1] != array2[1]) return false;
  if (array1[2] != array2[2]) return false;
  if (array1[3] != array2[3]) return false;
  return true;
}
