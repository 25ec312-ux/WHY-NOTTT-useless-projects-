//arduino code
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// ================= WIFI =================

const char* ssid = "Sain P's A54";
const char* password = "Sain2024";

WebServer server(80);


// ================= PINS =================

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define IR_PIN 23
#define LDR_PIN 34
#define PIR_PIN 17

#define RED_PIN 25
#define GREEN_PIN 32
#define BLUE_PIN 33


// ================= SENSOR =================

DHT dht(DHT_PIN, DHT_TYPE);


// LDR threshold
const int LDR_THRESHOLD = 2000;


// ================= DOOR COUNT =================

int doorOpenings = 0;
bool previousDoorState = false;


// ================= DATA =================

void handleData() {

  // ----- Temperature -----

  float temperature = dht.readTemperature();


  // ----- LDR -----

  int ldrValue = analogRead(LDR_PIN);

  // LDR > threshold = DARK
  bool roomDark = (ldrValue > LDR_THRESHOLD);


  // ----- IR Door -----

  int irValue = digitalRead(IR_PIN);

  // Most IR modules are active LOW
  bool doorOpen = (irValue == LOW);


  // Count door opening
  if (doorOpen && !previousDoorState) {

    doorOpenings++;

    Serial.print("DOOR OPENED | Count: ");
    Serial.println(doorOpenings);
  }

  previousDoorState = doorOpen;


  // ----- PIR Human -----

  int pirValue = digitalRead(PIR_PIN);

  bool humanPresent = (pirValue == HIGH);


  // ----- RGB Light -----

  bool lightOn =
    digitalRead(RED_PIN) ||
    digitalRead(GREEN_PIN) ||
    digitalRead(BLUE_PIN);


  // ================= JSON =================

  String json = "{";

  // Temperature
  json += "\"temperature\":";

  if (isnan(temperature)) {
    json += "null";
  } else {
    json += String(temperature, 1);
  }


  // LDR
  json += ",\"ldr\":";
  json += String(ldrValue);


  // Room dark
  json += ",\"room_dark\":";
  json += roomDark ? "true" : "false";


  // Door
  json += ",\"door_open\":";
  json += doorOpen ? "true" : "false";


  // Door count
  json += ",\"door_openings\":";
  json += String(doorOpenings);


  // Human
  json += ",\"human_present\":";
  json += humanPresent ? "true" : "false";


  // Light
  json += ",\"light_on\":";
  json += lightOn ? "true" : "false";


  json += "}";


  server.send(200, "application/json", json);
}


// ================= SETUP =================

void setup() {

  Serial.begin(115200);


  // Sensor pins
  pinMode(IR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);


  // RGB pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);


  // RGB OFF
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);


  // DHT
  dht.begin();


  // ================= WIFI =================

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.println("WIFI CONNECTED!");

  Serial.print("ESP32 IP ADDRESS: ");
  Serial.println(WiFi.localIP());


  // ================= SERVER =================

  server.on("/data", handleData);

  server.begin();

  Serial.println("HOUSE BRAIN SENSOR SERVER READY");
}


// ================= LOOP =================

void loop() {

  server.handleClient();

}


             
