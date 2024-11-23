#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(5);
  myServo.write(90); // Comenzar con la puerta cerrada
}

void abrirPuertaLento() {
  // Mover el servo gradualmente de 90° a 0°
  for (int angulo = 90; angulo >= 0; angulo--) {
    myServo.write(angulo);
    delay(15); // Ajusta este valor para controlar la velocidad del movimiento
  }
}

void cerrarPuertaLento() {
  // Mover el servo gradualmente de 0° a 90°
  for (int angulo = 0; angulo <= 90; angulo++) {
    myServo.write(angulo);
    delay(15); // Ajusta este valor para controlar la velocidad del movimiento
  }
}
