// Librerías
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>


// MQTT Setup
#define mqttUser "" //Agregar aquí el token generado por Ubidots
#define mqttPass ""
#define mqttPort 1883
// MQTT Led test
#define Led 2

// Sensor DHT11 Config
#define DHTPIN 27
#define DHTTYPE DHT11

// Configuración Temperatura con DHT11
DHT dht(DHTPIN, DHTTYPE);

// Configuración WiFi. Agregar credenciales de conexión.
const char* ssid = "";
const char* password = "";

// Configuración broker
char mqttBroker[] = "industrial.api.ubidots.com";  //ip del servidor donde se encuentra el broker
char mqttClientId[] = "espdavv";                   //cualquier nombre
// Topic de Ubidots (pub)
char inTopic1[] = "/v1.6/devices/device1"; //Cambiar "device1" por el nombre del dispositivo de Ubidots al que se desea publicar. 
// Sub
char inTopic2[] = "proyecto/topico2";

// Config WiFi client
WiFiClient BClient;
PubSubClient client(BClient);

void setup() {
  Serial.begin(9600);

  // Pins config
  pinMode(Led, OUTPUT);

  // Función WiFi. Comentar / Descomentar para no conectarse o conectarse.
  setup_wifi();

  // Configuración mqtt Comentar / Descomentar para no conectarse o conectarse.
  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback);
  Serial.println("Setup done");
  delay(1500);

  // Config DHT11
  dht.begin();
}

void loop() {
  // Comentar / Descomentar para MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // USAR ESTE DELAY
  delay(10000);

  // Temperatura
  float celsius = dht.readTemperature();

  // Humedad
  float humedad = dht.readHumidity();

  // Creación e inicialización del JSON que se enviará por MQTT a Ubidots
  String json;
  DynamicJsonDocument doc(1024);
  doc["temperatura"] = celsius;
  doc["humedad"] = humedad;
  doc["idnodo"] = 1;
  serializeJson(doc, json);

  //MQTT
  int lon = json.length() + 1;
  char datojson[lon];
  json.toCharArray(datojson, lon);
  // Comentar / Descomentar para MQTT
  client.publish(inTopic1, datojson);

  // Impresión de JSON.
  Serial.println(json);
}

// Función de conexión WiFi ESP32
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Función Callback MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String json = String((char*)payload);
  Serial.println(json);
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) { return; }
  int estado = doc["estado"];
  Serial.println(estado);
  if (estado == 1) {
    digitalWrite(Led, HIGH);
  } else {
    digitalWrite(Led, LOW);
  }
}

// Función conexión MQTT
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqttClientId, mqttUser, mqttPass)) {
      Serial.println("connected");
      client.subscribe(inTopic2);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}