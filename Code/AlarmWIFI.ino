#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "LasloCalifornia";
const char* password = "laslocalifornia";

String phoneNumber = "+56926882465";
String apiKey = "2003346";

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Mensaje enviado correctamente");
  }
  else{
    Serial.println("Error al enviar el mensaje");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup()
{
  Serial.begin(9600);
  pinMode(5, INPUT);// pin D1(GPIO5) como entrada
  pinMode(4,OUTPUT);// pin D2(GPIO4) como Salida

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

void Alarma()
{
  // si la alarma se activa este envia un mensaje mediante WhatsApp y espera 15 segundos.

  int Sensor = digitalRead(5); // variable para almacenar los estados del PIR
  if (Sensor == 1) // si el sensor detecta movimiento
  {
    Serial.println("Alarma Activada"); //Imprime por el monitor serial
    sendMessage("Movimiento Sospechoso en tu propiedad");
    delay(200);
  }
}
void loop()
{
  Alarma();// llama a ejecutar la funcion
}

