#include <SPI.h>
#include <LoRa.h> 

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    18   // GPIO27 -- SX1278's MOSI
#define SS      21   // GPIO18 -- SX1278's CS
#define RST     4   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6

int flag = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() {
 
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  LoRa.setSpreadingFactor(12);
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  delay(5000);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("init ok");

  delay(1500);
}

void loop() {
  Serial.println(flag);
  
  // Ligado o LoRa
  LoRa.beginPacket();
  LoRa.print(flag);
  LoRa.endPacket();
  delay(3000);

  flag++;
 
               
}
