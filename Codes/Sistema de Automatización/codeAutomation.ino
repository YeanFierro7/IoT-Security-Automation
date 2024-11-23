#include<Servo.h>
Servo myServo;
int TRIG = 8;
int ECO = 9;
int tiempo;
int distancia;
void setup() {
   pinMode(TRIG,OUTPUT);
   pinMode(ECO,INPUT);
   myServo.attach(5);
   Serial.begin(9600);
}
void loop() {
 leerDistancia();
 if(distancia<10){
  abrirPuerta();
  delay(2000);
  cerrarPuerta();
  delay(2000);
  }
}
void leerDistancia(){
  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  tiempo = pulseIn(ECO,HIGH);
  distancia = tiempo / 58.2;  
  } 
void cerrarPuerta(){
  int angulo=0;
  do{
    angulo=angulo+1;
    myServo.write(angulo);
    delay(50);
    }while(angulo<90);   
}
void abrirPuerta(){
  int angulo =90;
  do{
    angulo=angulo-1;
    myServo.write(angulo);
    delay(50);
    }while(angulo>0);
  }