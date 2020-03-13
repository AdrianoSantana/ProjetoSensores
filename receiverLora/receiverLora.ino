#include <SPI.h>
#include <LoRa.h>
#include <Wire.h> 
#include <string> 

// Pinos de controle da LoRa
#define SCK     5    
#define MISO    19 //-   
#define MOSI    15 //-   
#define SS      23 //-  
#define RST     4  
#define DI0     27   //-
#define BAND  915E6

// Pinos de controle do motor
#define AMARELO 25
#define PRETO 33
#define VERDE 32
#define LARANJA 2

int packetSize = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

// Funções de acionamento do motor
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

// Funcoes ler dados da LoRa
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
    
  if(packet.toInt() < 4000) {
    Serial.println("Ligando valvula!");
    direcaoUm();
    delay(30);
    off();
    delay(1500);
    direcaoDois();
    delay(30);
    off();
    delay(5000);
  }
    
  else
    off();
  
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC);
  loraData();
  
}

void setup() {
  pinMode(AMARELO,OUTPUT);
  pinMode(PRETO,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(LARANJA,OUTPUT);
  off(); //Motor inicia desligado
  
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
   
}

void loop() {
  
  packetSize = LoRa.parsePacket();

  if (packetSize)
    cbk(packetSize);

  
}
