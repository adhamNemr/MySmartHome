#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

// ====== WiFi Credentials ======
const char* ssid = "FBI";
const char* password = "Genv911@#$";

// ====== WebSocket ======
WebSocketsClient webSocket;

// ====== DHT22 Sensor ======
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ====== Other Sensors ======
#define GAS_SENSOR_PIN 35
#define FLAME_SENSOR_PIN 34
#define PIR_SENSOR_PIN 33
#define DOOR_SENSOR_PIN 26  
#define LDR_SENSOR_PIN 32

// ====== LED Pin (simulate devices) ======
#define LED_PIN 2

// ====== Variables ======
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 2000;  // 2 seconds

// ====== Functions ======
void restartLED() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
  }
  digitalWrite(LED_PIN, LOW);  // Leave LED OFF at the end
}

void blinkTwice() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
  }
  digitalWrite(LED_PIN, LOW); // مطفي في النهاية
}

void handleCommand(const String& cmd, const String& action) {
  if (action == "open" || action == "true") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("💡 Command ON");
  } else if (action == "close" || action == "false") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("💡 Command OFF");
  } else if (action == "restart") {
    Serial.println("🔄 Command RESTART");
    restartLED();
  } else if (action == "closeAll") {
    Serial.println("🔒 Close All - Blinking twice!");
    blinkTwice();
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("❌ WebSocket Disconnected!");
      break;

    case WStype_CONNECTED:
      Serial.println("✅ WebSocket Connected!");
      break;

    case WStype_TEXT: {
      Serial.printf("📥 Received: %s\n", payload);

      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        // التعامل مع light و AC
        if (doc.containsKey("light")) {
          handleCommand("light", doc["light"].as<String>());
        }
        if (doc.containsKey("ac")) {
          handleCommand("ac", doc["ac"].as<String>());
        }

        // التعامل مع بقية الأجهزة
        const char* devices[] = {
          "fire", "rain", "gas", "door",
          "window", "motion", "last_time"
        };

        for (const char* device : devices) {
          if (doc.containsKey(device)) {
            handleCommand(device, doc[device].as<String>());
          }
        }
      } else {
        Serial.println("❌ Error parsing JSON");
      }
      break;
    }

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LDR_SENSOR_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("🔌 Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");

  // WebSocket
  // 172.20.10.4 For My Phone Hotspot 
  // 192.168.1.15 For My WIFI 
  webSocket.begin("192.168.1.15", 8080, "/");
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - lastSendTime >= sendInterval) {
    lastSendTime = currentMillis;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gasValue = analogRead(GAS_SENSOR_PIN);
    int flameValue = analogRead(FLAME_SENSOR_PIN);
    int motionDetected = digitalRead(PIR_SENSOR_PIN);
    int doorStatus = digitalRead(DOOR_SENSOR_PIN);
    int lightLevel = analogRead(LDR_SENSOR_PIN);

    StaticJsonDocument<256> doc;
    doc["device_id"] = 1;
    JsonObject readings = doc.createNestedObject("readings");
    readings["temperature"] = temperature;
    readings["humidity"] = humidity;
    readings["light"] = lightLevel;
    readings["gas"] = gasValue;
    readings["flame"] = flameValue;
    readings["motion"] = motionDetected;  
    readings["isDoorClosed"] = doorStatus;
    readings["isWindowClosed"] = doorStatus;

    String jsonString;
    serializeJson(doc, jsonString);
    webSocket.sendTXT(jsonString);

    Serial.print("📤 Sent: ");
    Serial.println(jsonString);
  }
}
