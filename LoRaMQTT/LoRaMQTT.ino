#include <ssl_client.h>

#include <WiFi.h> //Library usar WIFI
#include <PubSubClient.h> //Library usada para publicar informações via MQTT

#define sensorUmidade 35 // Porta do sensor
#define idMQTT "ANS#1010" //Identificador do nosso cliente
#define topico "sensorLdr" //Tópico usado no broker, publicares os dados do sensor de luz neste tópico



int valorUmidade = 0; // Valor do sensor

/* 
  Credencias da rede wifi
*/
const char* ssid = "OK.INT250";
const char* password =  "9307151515";

WiFiClient myClient; //Criar um objeto da classe WiFiClient, ou seja um client

/*
 * Credencias MQTT
 * Neste código está sendo usado o broker gratuito do eclipse
 */
const char* brokerMQTT = "mqtt.eclipse.org";
int brokerPort = 1883; 

PubSubClient MQTT(myClient);

/*
 * Funções
 */

 void conectaWifi() { //Usada para começar uma conexão com a rede WIFI
   if (WiFi.status() == WL_CONNECTED) {
     return;
  }
  WiFi.begin(ssid, password); //Inicia conexão com a rede WIFI
   delay(3000);
   while (WiFi.status() != WL_CONNECTED) { //Enquanto não estiver conectada fica presa no loop
    delay(500);
    Serial.println("TRY : Tentando conectar a rede WIFI");
   }
   Serial.println("SUCESS : Conectado com a rede WIFI "); //Conectada com sucesso.
 }

 void conectaMQTT() { //Conecta a esp32 ao broker MQTT
   while (!MQTT.connected()) {
        Serial.print("TRY: Tentando conectar ao Broker MQTT: ");
        Serial.println(brokerMQTT);
        if (MQTT.connect(idMQTT)) {
            Serial.println("SUCESS: Conectado ao Broker com sucesso!");
        } 
        else {
            Serial.println("FAIL : Não foi possivel se conectar.");
            Serial.println("Nova tentatica de conexao em 6s");
            delay(6000);
        }
    }
 }


void setup() {
    // put your setup code here, to run once:
   pinMode(sensorUmidade, INPUT); //A porta do Sensor é um input
   Serial.begin(9600); //Inicia a porta Serial
   conectaWifi(); //Função usada para começar uma conexão com a rede
   MQTT.setServer(brokerMQTT, brokerPort); //
   
 }

void loop() {
  
  conectaWifi(); //Se a conexão com a wifi foi perdida ela é reiniciada
  if (!MQTT.connected()) { //Se a conexão com o mqtt foi perdida reconecta
       conectaMQTT();
   } else {
    
     valorUmidade = analogRead(sensorUmidade);
     delay(1000);

    
     //Convertendo valorSensor em um array de char
     char sensorUmidadeString[8];
     dtostrf(valorUmidade, 1, 2, sensorUmidade);
    
     MQTT.publish(topico,sensorUmidadeString); //Envia dados para o topico
     Serial.print("Enviado: ");
     Serial.println(valorUmidade);
     MQTT.loop(); 
    
   }
   
  
}
