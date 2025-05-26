#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "SEU_IP";
const int mqtt_port = 1883;
const char* mqtt_topic = "monitoramento/veiculos";

WiFiClient espClient;
PubSubClient client(espClient);

struct VeiculoBLE {
  String identificador;
  String tipo;
  String ultimaZona;
  bool emMovimento;
  int intensidadeSinal;
};

VeiculoBLE veiculo = {
  "BLE-ABC123",
  "Elétrico",
  "Setor-C3",
  true,
  -70
};

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado. IP: " + WiFi.localIP().toString());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("SimuladorUnico")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falhou, código: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

float calcularDistancia(int rssi, int txPower = -50, float fatorPerda = 2.0) {
  return pow(10.0, ((float)(txPower - rssi)) / (10.0 * fatorPerda));
}

void simularSinalBLE() {
  float distancia = calcularDistancia(veiculo.intensidadeSinal);

  StaticJsonDocument<256> doc;
  doc["identificador"] = veiculo.identificador;
  doc["tipo"] = veiculo.tipo;
  doc["zona"] = veiculo.ultimaZona;
  doc["movimento"] = veiculo.emMovimento;
  doc["rssi"] = veiculo.intensidadeSinal;
  doc["distancia"] = distancia;

  char buffer[256];
  serializeJson(doc, buffer);

  Serial.println("Enviando MQTT: ");
  Serial.println(buffer);

  client.publish(mqtt_topic, buffer);
}

void setup() {
  Serial.begin(115200);
  conectarWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) conectarMQTT();
  client.loop();

  simularSinalBLE();
  delay(5000);
}