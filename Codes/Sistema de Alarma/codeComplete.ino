#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "POCO M6 Pro";      // Nombre de la red WiFi
const char* password = "s2ggm4pk68vxrir";  // Contraseña de la red WiFi

String phoneNumber = "+56926882465";   // Número de teléfono (con código de país)
String apiKey = "2003346";             // Clave de API para el servicio de WhatsApp

int inputPin = 13;                    // Pin de entrada del sensor PIR (D7)
int pirState = LOW;                   // Estado inicial (sin movimiento)
int val = 0;                           // Variable para leer el valor del sensor PIR
int buzzerPin = D6;                   // Pin del buzzer (D6)
unsigned long lastMotionTime = 0;     // Tiempo del último movimiento detectado
unsigned long debounceDelay = 3000;   // Tiempo de retardo de 3 segundos (3000 ms)

void sendMessage(String message) {
  // Datos a enviar con la solicitud HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Especificar el encabezado Content-Type
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Enviar la solicitud HTTP POST
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.println("Mensaje enviado con éxito");
  }
  else{
    Serial.println("Error al enviar el mensaje");
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }

  // Liberar recursos
  http.end();
}

void setup() {
  pinMode(inputPin, INPUT);          // Configurar el pin del PIR como entrada
  pinMode(buzzerPin, OUTPUT);        // Configurar el pin del buzzer como salida
  Serial.begin(9600);                // Iniciar la comunicación serial

  WiFi.begin(ssid, password);        // Conectar a la red WiFi
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a la red WiFi con IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  val = digitalRead(inputPin);  // Leer el estado del sensor PIR

  // Si el sensor PIR detecta movimiento y el estado anterior era sin movimiento
  if (val == HIGH && pirState == LOW) {
    Serial.println("Movimiento detectado!");  // Notificar movimiento
    digitalWrite(buzzerPin, HIGH);            // Encender el buzzer
    pirState = HIGH;                          // Cambiar el estado a "con movimiento"
    lastMotionTime = millis();                // Registrar el tiempo en que se detectó el movimiento
    
    // Enviar mensaje de WhatsApp cuando se detecta movimiento
    sendMessage("¡Alerta! Movimiento detectado en tu hogar.");
  }
  // Si el sensor PIR deja de detectar movimiento y el estado anterior era con movimiento
  else if (val == LOW && pirState == HIGH) {
    Serial.println("Sin movimiento!");  // Notificar que ya no hay movimiento
    digitalWrite(buzzerPin, LOW);       // Apagar el buzzer
    pirState = LOW;                     // Cambiar el estado a "sin movimiento"
  }
  
  // Añadir un pequeño retardo para evitar lecturas demasiado rápidas
  delay(100);  // 100 ms de retardo (ajustable según tus necesidades)
}