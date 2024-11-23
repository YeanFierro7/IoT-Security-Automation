const int TRIG = 8;
const int ECHO = 9;
const int DISTANCIA_UMBRAL = 30;  Distancia en cm para activar el servo

long tiempo;
int distancia;
bool puertaAbierta = false;  Estado de la puerta
unsigned long tiempoInicioDeteccion = 0;  Tiempo desde que dejó de detectar

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  distancia = leerDistancia();
  Serial.print(Distancia );
  Serial.println(distancia);

  if (distancia  DISTANCIA_UMBRAL) {
    if (!puertaAbierta) {
      abrirPuertaLento();
      puertaAbierta = true;  Marcar la puerta como abierta
    }
     Reiniciar el temporizador porque detecta un objeto
    tiempoInicioDeteccion = millis();
  } else if (puertaAbierta) {
     Comprobar si han pasado 5 segundos desde que dejó de detectar
    if (millis() - tiempoInicioDeteccion = 5000) {
      cerrarPuertaLento();
      puertaAbierta = false;  Marcar la puerta como cerrada
    }
  }

  delay(100);  Pequeña pausa para evitar lecturas constantes
}

int leerDistancia() {
   Enviar pulso de disparo
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

   Calcular duración del pulso
  tiempo = pulseIn(ECHO, HIGH);
  int distancia = tiempo  0.034  2;  Convertir a cm
  return distancia;
}
