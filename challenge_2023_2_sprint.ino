// estabelece as entradas dos pinos no Arduino UNO
#define trigPin 3
#define echoPin 2
int buzzerPin = 5;
int ledPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  //aciona a leitura do sensor de proximidade
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
	
  //converte a leitura do sensor de proximidade em centímetros
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  //aciona os alertas do circuito ao detectar um objeto
  if (distance < 50) {
    Serial.println("Alerta! Bueiro entupido!");
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin,600);
  }
  //mantém os alertas do circuito desativados caso não haja nenhum objeto
  else{
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Serial.println("Bueiro desobstruido!");
  } 
}