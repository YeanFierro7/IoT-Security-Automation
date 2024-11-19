int buzzerPin = D6;  // Pin donde está conectado el buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Configurar el pin del buzzer como salida
}

void loop() {
  digitalWrite(buzzerPin, HIGH);  // Encender el buzzer
  delay(1000);  // Esperar 1 segundo (1000 ms)
  
  digitalWrite(buzzerPin, LOW);   // Apagar el buzzer
  delay(1000);  // Esperar 1 segundo (1000 ms)
}