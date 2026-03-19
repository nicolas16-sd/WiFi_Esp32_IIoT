#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "duro";
const char* password = "08.durinho";

const char* url = "https://jsonplaceholder.typicode.com/todos/1";

#define LED_VERDE 18
#define LED_VERMELHO 19

void setup() {
  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado com sucesso!");
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure *client = new WiFiClientSecure;

    if (client) {
      client->setInsecure();

      HTTPClient https;

      Serial.println("[HTTPS] Iniciando requisição...");

      if (https.begin(*client, url)) {

        int httpCode = https.GET();

        if (httpCode == 200) {
          Serial.println("Servidor OK");

          digitalWrite(LED_VERDE, HIGH);
          digitalWrite(LED_VERMELHO, LOW);

        } else {
          Serial.printf("Erro HTTP: %d\n", httpCode);

          digitalWrite(LED_VERDE, LOW);
          digitalWrite(LED_VERMELHO, HIGH);
        }

        https.end();

      } else {
        Serial.println("Erro ao conectar no servidor");

        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_VERMELHO, HIGH);
      }

      delete client;
    }

  } else {
    Serial.println("Wi-Fi desconectado!");

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }

  delay(10000);
}