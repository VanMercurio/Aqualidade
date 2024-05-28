// Bibliotecas ------------------------------------------
#include <DHT.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ArduinoJson.h>
//#include <TimeLib.h>
 
// DHT --------------------------------------------------
#define DHTPIN 13  // Pino de dados do sensor DHT
#define DHTTYPE DHT11  // Tipo do sensor (DHT11)
 
// Firebase -- ------------------------------------------
#define FIREBASE_HOST "https://aqualidade-6b97c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "TcywgDjex13MhULWkDowc4s17D61sQMnWR1IHsbb"
 
// Wi-Fi ------------------------------------------------
#define ssid     "Vanessa S22"
#define password "wddt9946"
 
DHT dht(DHTPIN, DHTTYPE);
 
// Setup ------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  dht.begin();
  delay(2000);
 
  Serial.begin(115200);
 
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.println("--------------------------- WIFI CONNECTION ----------------------------");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
      delay(5000);
      Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //server.begin();
 
  Serial.println("-------------------------- FIREBASE CONNECTION -------------------------");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   
  if (Firebase.failed()) {
    Serial.print("Falha na conexão com o Firebase. Código de erro: ");
    Serial.println(Firebase.error());
  } else {
    Serial.println("Conexão com o Firebase bem-sucedida...");
    Serial.println();
  }
 
  Serial.println("----------------- TEMPERATURE AMD HUMIDITY INFORMATION -----------------");
  Serial.println();
 
}
 
int n = 0;
 
void loop() {
 
  // Realizar a leitura do sensor
  float temp = 24.6 //dht.readTemperature();
  float humid = 50.5 //dht.readHumidity();
 
  if (isnan(temp) || isnan(humid)) {
    Serial.println("Falha na leitura do sensor DHT");
    delay(2000);
    return;
  }
 
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | ");
  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print(" % ");
 
  Serial.println();
 
  String data = "{\"temperature\": " + String(temp) + ", \"humidity\": " +
                                       String(humid) + ", \"timestamp\": \"" "\"}";
 
  Firebase.pushString("/data", data);
 
  delay(15000);
 
}
 