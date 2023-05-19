//--------------------------------------------------------------
// Incluindo bibliotecas e definindo pinos
//--------------------------------------------------------------
#include <LiquidCrystal.h>

#define trigPin 3
#define echoPin 2

LiquidCrystal lcd (4, 5, 6, 7, 8, 9);

int buzzerPin = 10;

//--------------------------------------------------------------
// Estabalecendo variáveis utilizadas no código
//--------------------------------------------------------------
long duration, distance;
int alerta = 0;

int mensagemAtual = 0;
int mensagemAnterior = 0;

//--------------------------------------------------------------
// Definindo tipos dos pinos
//--------------------------------------------------------------
void setup() {
  
  Serial.begin(9600);
  
  lcd.begin(16, 2); 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  
  pinMode(buzzerPin, OUTPUT);
}

//--------------------------------------------------------------
// Estabelecendo o loop principal e suas funções
//--------------------------------------------------------------
void loop() {  
  lerDistancia();
  
  definirAlertas();
  
  acionarAlertas();
  
  controleLCD();
  
  Serial.println(String(mensagemAtual));
  
}

//--------------------------------------------------------------
// Relizando a leitura de distância e conversão para centímetros
//--------------------------------------------------------------
void lerDistancia(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
	
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}

//--------------------------------------------------------------
// Definindo os alertas de acordo com a leitura de distância
//--------------------------------------------------------------
void definirAlertas(){
  if (distance < 10) {
   alerta = 3;
  }
  else if (distance < 30) {
    alerta = 2;
  }
  else if (distance < 50) {
    alerta = 1;
  }
  else {
    alerta = 0;
  } 
}

//--------------------------------------------------------------
// Aciona buzzer e monitor serial de acordo com o alarme ativo
//--------------------------------------------------------------
void acionarAlertas(){
  if (alerta == 0) {
    noTone(buzzerPin);
    Serial.println();
    Serial.println("Bueiro desobstruido");
    }
  else if (alerta == 1) {
    tone(buzzerPin,600);
    Serial.println();
    Serial.println("Objeto a " + String(distance) + "cm");
  }
  else if (alerta == 2) {
    tone(buzzerPin,600);
    Serial.println();
    Serial.println("Objeto a " + String(distance) + "cm");
  }
  else if (alerta == 3) {
    tone(buzzerPin,600);
    Serial.println();
    Serial.println("Objeto a " + String(distance) + "cm");
  }
}

//--------------------------------------------------------------
// Imprimindo mensagens no LCD de acordo com o alerta ativo
//--------------------------------------------------------------
void controleLCD(){    
  if (alerta == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Bueiro");
    lcd.setCursor(0, 1);
    lcd.print("Desobstruido");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Bueiro Entupido");
    lcd.setCursor(0, 1);
    lcd.print("Objeto a " + String(distance) + "cm");
  }
  mensagemAtual = millis();
  if (mensagemAtual - mensagemAnterior >= 3000){
    lcd.clear();
    mensagemAnterior = mensagemAtual;
  }
}
  