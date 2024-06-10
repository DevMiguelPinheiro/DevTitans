#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 13     // Pino do sensor DHT
#define DHTTYPE DHT22 // Tipo de sensor DHT
#define LED1 2       // Pino do LED 1
#define LED2 15      // Pino do LED 2

// Credenciais WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Endereço do broker MQTT
const char* mqtt_server = "test.mosquitto.org";


const char* matricula = "202200";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Tratar as mensagens recebidas
  if ((char)payload[0] == '1' && (char)payload[1] == 'L') {
    digitalWrite(LED1, HIGH);  // Liga o LED 1
    Serial.println("LED 1 LIGADO");
  } else if ((char)payload[0] == '2' && (char)payload[1] == 'L') {
    digitalWrite(LED2, HIGH);  // Liga o LED 2
    Serial.println("LED 2 LIGADO");
  } else if ((char)payload[0] == '1' && (char)payload[1] == 'D') {
    digitalWrite(LED1, LOW);   // Desliga o LED 1
    Serial.println("LED 1 DESLIGADO");
  } else if ((char)payload[0] == '2' && (char)payload[1] == 'D') {
    digitalWrite(LED2, LOW);   // Desliga o LED 2
    Serial.println("LED 2 DESLIGADO");
  }
}

void reconnect() {
  // Loop até reconectar
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Inscrever-se no tópico
      String inTopic = "In" + String(matricula);
      client.subscribe(inTopic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    // Leitura do sensor DHT
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    // Checar se as leituras falharam
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    
    // Publicar a umidade e a temperatura
    String tempTopic = "Out" + String(matricula) + "/Temperatura";
    String humTopic = "Out" + String(matricula) + "/Umidade";
    String payload = "Umidade: " + String(h) + " % Temperatura: " + String(t) + " graus";
    
    // Publica nos tópicos
    client.publish(tempTopic.c_str(), String(t).c_str());
    client.publish(humTopic.c_str(), String(h).c_str());
    
    // Imprime na serial
    Serial.println(payload);
  }
}
