#define AMARELO 25
#define PRETO 33
#define VERDE 32
#define LARANJA 15

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


void setup() {
  // put your setup code here, to run once:
  /*
   * Setando os pinos como saída
   */
  pinMode(AMARELO,OUTPUT);
  pinMode(PRETO,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(LARANJA,OUTPUT);
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 /*
  * Ligar a solenoide
  */
 direcaoUm();
 delay(30);
 direcaoUm();
 delay(30);
 
 off();
 delay(1000);
 
 direcaoDois();
 delay(30);
 direcaoDois();
 delay(30);
 off();
 delay(1000);
 /*
 Este trecho de código foi usado para Ligar o motor
 delay(5000);
 Off();
 delay(2000);
 direcaoDois();
 delay(5000);
 Off();
 */
}
