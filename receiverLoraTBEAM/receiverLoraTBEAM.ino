#include <SPI.h>
#include <LoRa.h>
#include <Wire.h> 
#include <string> 

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    915E6

#define AMARELO 22
#define PRETO 13
#define VERDE 14
#define LARANJA 21

String rssi = "RSSI --";
String packSize = "--";
String packet ;

void direcaoUm() {
  /*
   * Amarelo - H
   * Preto - L
   * Verde - L
   * Laranja - H
   */
  digitalWrite(AMARELO,HIGH);
  digitalWrite(PRETO,LOW);
  digitalWrite(VERDE,LOW);
  digitalWrite(LARANJA,HIGH);
}
void direcaoDois() {
  /*
   * Amarelo - L
   * Preto - H
   * Verde - H
   * Laranja - L
   */
  digitalWrite(AMARELO,LOW);
  digitalWrite(PRETO,HIGH);
  digitalWrite(VERDE,HIGH);
  digitalWrite(LARANJA,LOW);
}

void off() {
   /*
   * Amarelo - L
   * Preto - H
   * Verde - L
   * Laranja - H
   */
   digitalWrite(AMARELO,LOW);
  digitalWrite(PRETO,HIGH);
  digitalWrite(VERDE,LOW);
  digitalWrite(LARANJA,HIGH);
}

void loraData(){
  
  Serial.println("Received " + packSize + " bytes");
  Serial.println(packet);
  Serial.println(rssi);
  
}

void cbk(int packetSize) {
  
  packet ="";
  packSize = String(packetSize,DEC);
  
  for (int i = 0; i < packetSize; i++)
    packet += (char) LoRa.read();

  if(packet.toInt() < 800)
    digitalWrite(13,HIGH);
  else
    digitalWrite(13,LOW);
    
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC);
  loraData();
  
}

void setup() {
  pinMode(AMARELO, OUTPUT);
  pinMode(PRETO, OUTPUT);
  pinMode(LARANJA, OUTPUT);
  pinMode(VERDE, OUTPUT);
  off();
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  delay(5000);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  LoRa.receive();
  Serial.println("init ok");
   
  delay(1500);
}

void loop() {
  
  int packetSize = LoRa.parsePacket();

  if (packetSize)
    cbk(packetSize);

  delay(10);
  
}
