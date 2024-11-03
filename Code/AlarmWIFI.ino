#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "LasloCalifornia";
const char* password = "laslocalifornia";

String phoneNumber = "+56926882465";
String apiKey = "2003346";

#define MOTION_SENSOR_PIN  D7
#define BUZZER_PIN         D1  

int motion_state  = LOW; // Estado actual del pin del sensor de movimiento
int prev_motion_state = LOW; // Estado anterior del pin del sensor de movimiento

void setup() {
  //PIR & BUZZER  
  Serial.begin(9600);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // API Mensajes
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Conectando");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a la red WiFi con dirección IP: ");
  Serial.println(WiFi.localIP());
}

void sendMessage(String message){
  // Datos para enviar con HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);
  // Especificar el contenido
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  // Enviar solicitud HTTP POST
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Mensaje enviado correctamente");
  }
  else{
    Serial.println("Error al enviar el mensaje");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void loop() {
  prev_motion_state = motion_state; // Almacena el estado anterior
  motion_state  = digitalRead(MOTION_SENSOR_PIN); // Lee el nuevo estado

  if (prev_motion_state == LOW && motion_state == HIGH) { // Cambio de estado del pin: LOW -> HIGH
    Serial.println("¡Movimiento detectado!, emitiendo sonido");
    sendMessage("Movimiento Sospechoso en tu propiedad");
    digitalWrite(BUZZER_PIN, HIGH); // Encendido
  } else if (prev_motion_state == HIGH && motion_state == LOW) { // Cambio de estado del pin: HIGH -> LOW
    Serial.println("¡Movimiento detenido!, deja de emitir sonido");
    digitalWrite(BUZZER_PIN, LOW); // Apagado
  }
}