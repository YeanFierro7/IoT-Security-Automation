int inputPin = 13;  // Pin de entrada del sensor PIR (D7)
int pirState = LOW; // Estado inicial (sin movimiento)
int val = 0;        // Variable para leer el valor
unsigned long lastMotionTime = 0;  // Tiempo del último movimiento detectado
unsigned long debounceDelay = 3000; // Tiempo de retardo de 3 segundos (3000 ms)

void setup() {
  pinMode(inputPin, INPUT);  // Configurar el pin del PIR como entrada
  Serial.begin(9600);        // Iniciar la comunicación serial
}

void loop() {
  val = digitalRead(inputPin);  // Leer el estado del sensor PIR

  // Si el sensor PIR detecta movimiento y han pasado más de 3 segundos desde el último movimiento
  if (val == HIGH && pirState == LOW && (millis() - lastMotionTime > debounceDelay)) {
    Serial.println("Movimiento detectado!");  // Notificar movimiento
    pirState = HIGH;  // Cambiar el estado a "con movimiento"
    lastMotionTime = millis();  // Registrar el tiempo en que se detectó el movimiento
  }

  // Si el sensor PIR ya no detecta movimiento
  else if (val == LOW && pirState == HIGH) {
    Serial.println("Sin movimiento!");  // Notificar que ya no hay movimiento
    pirState = LOW;  // Cambiar el estado a "sin movimiento"
  }

  // Añadir un pequeño retardo para evitar lecturas demasiado rápidas
  delay(100);  // 100 ms de retardo (ajustable según tus necesidades)
}