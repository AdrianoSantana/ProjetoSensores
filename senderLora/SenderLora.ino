#include <SPI.h>
#include <LoRa.h> 

#define SCK     5    
#define MISO    19   
#define MOSI    18   
#define SS      21   
#define RST     4
#define DI0     26
#define BAND  915E6

#define sensorUmidade 35

int valorUmidade = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() {
  pinMode(sensorUmidade, INPUT);
  Serial.begin(115200);
  while (!Serial);
  //Serial.println();
  Serial.println("LoRa Sender Test");
  //LoRa.setSpreadingFactor(12);
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  //delay(5000);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("init ok");

  delay(1500);
}

void loop() {
  valorUmidade = analogRead(sensorUmidade);
  Serial.print("Valor sensor não enviado pela loRa :");
  Serial.println(valorUmidade);
 
  
  // Ligado o LoRa
  LoRa.beginPacket();
  LoRa.print(valorUmidade);
  LoRa.endPacket();

  Serial.print("Valor sensor enviado pela loRa : ");
  Serial.println(valorUmidade);
  delay(2000);
       
}
