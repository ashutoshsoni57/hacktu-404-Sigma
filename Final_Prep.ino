#define SS_PIN 2  //D4
#define RST_PIN 3  //D3
#define buzzer 15  //
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h> 
#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo Servo1;
char auth[] = "1fFDr-HO9vn-IMnQhFQcdnctGVrRXckw";
char ssid[] = "Coco Buffy";
char pass[] = "Deepak0987";
const byte pin5 = 5;
int servoPin = 16;
int statuss = 0;
int out = 0;

void ICACHE_RAM_ATTR ISRoutine ();

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  Blynk.begin(auth, ssid, pass);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Servo1.attach(servoPin); 
  pinMode(buzzer, OUTPUT);
  Servo1.write(0);
  Blynk.virtualWrite(V1,1);
   pinMode(pin5,INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(pin5),ISRoutine,FALLING);
}
void loop() 
{
  Blynk.run();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "2B 3A BB 1C") //change UID of the card that you want to give access
  {
    Blynk.virtualWrite(V1,2);
    Serial.println(" Plant A - Two Sprays ");
        for (int j=0;j<2;j++)
    {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    }
    Servo1.write(90);
    delay(1000);
    Servo1.write(0);
    delay(1000);
    Servo1.write(90);
    delay(1000);
    Servo1.write(0);
    delay(1000);
    statuss = 1;
  }
  else if (content.substring(1) == "0B 97 09 1B")
  {
    Blynk.virtualWrite(V1,3);
    Serial.println(" Plant B - Three Sprays");
        for (int k=0;k<3;k++)
    {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    }
    Servo1.write(90);
    delay(1000);
    Servo1.write(0);
    delay(1000);
    Servo1.write(90);
    delay(1000);
    Servo1.write(0);
    delay(1000);
    Servo1.write(90);
    delay(1000);
    Servo1.write(0);
    delay(1000);
    statuss = 1;
  }
  else   {
    Serial.println("No RFID");
    delay(3000);
  }
}
void ISRoutine () {
   int value;
   Serial.println("I am in ISR");
   digitalWrite(buzzer, HIGH);
    delayMicroseconds(100000);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(100000);
    Servo1.write(90);
    delayMicroseconds(1000000);
    Servo1.write(0);
    delayMicroseconds(1000000);
    statuss = 1;
   return;
}
