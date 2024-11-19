#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "POCO M6 Pro";
const char* password = "s2ggm4pk68vxrir";

String phoneNumber = "+56926882465";
String apiKey = "2003346";

void sendMessage(String message){

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
    Serial.print("Mensaje enviado con éxito");
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

  // Enviar mensaje a WhatsApp
  sendMessage("¡Hola desde ESP8266!");
}

void loop() {
  
}