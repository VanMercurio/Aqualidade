#include <NewPing.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ArduinoJson.h>  // Certifique-se de que a versão 5 está instalada

#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 200

#define FIREBASE_HOST "https://projetoiot-7c021-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xxxxxxx"

#define ssid     "moto g(7)"
#define password "Ro6205184"

float distancia;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed()) {
    Serial.println("Firebase connection failed");
    Serial.println(Firebase.error());
    return;
  }

  Serial.println("Firebase connection successful");
}

void loop() {
  delay(5000);
  unsigned int distance = sonar.ping_cm();
  if (distance != 0 && distance != NO_ECHO) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Criação do JSON usando ArduinoJson versão 5
    DynamicJsonBuffer jsonBuffer;
    JsonObject& jsonDoc = jsonBuffer.createObject();
    jsonDoc["distance"] = distance;
    jsonDoc["timestamp"] = "";  // Adicione o timestamp se necessário

    String jsonData;
    jsonDoc.printTo(jsonData);

    Firebase.pushString("/data", jsonData);
  } else {
    Serial.println("Error reading distance");
  }

  delay(15000);  // Delay de 15 segundos entre as leituras
}