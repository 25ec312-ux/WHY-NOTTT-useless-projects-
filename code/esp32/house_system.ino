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

//python code

import requests
import cv2
import numpy as np
from PIL import Image
from io import BytesIO
from ultralytics import YOLO
import time


# ==================================================
# SETTINGS
# ==================================================

ESP32_URL = "http://10.94.80.59/data"
PHONE_URL = "http://10.94.80.236:8080/video"


# ==================================================
# LOAD YOLO
# ==================================================

print("Loading YOLO...")

model = YOLO("yolo11n.pt")

print("YOLO ready!")


# ==================================================
# CONNECT TO PHONE CAMERA
# ==================================================

print("Connecting to phone camera...")

response = requests.get(
    PHONE_URL,
    stream=True,
    timeout=10
)

if response.status_code != 200:
    print("ERROR: Phone camera connection failed")
    exit()

print("Phone camera connected!")


# ==================================================
# HOUSE BRAIN
# ==================================================

print()
print("==============================================")
print("        🏠 HOUSE BRAIN v5")
print("==============================================")
print("ESP32 + CAMERA + YOLO")
print("==============================================")


buffer = b""
frame_count = 0

camera_human = False
last_camera_human = False

last_report_time = 0


# ==================================================
# MAIN LOOP
# ==================================================

for chunk in response.iter_content(chunk_size=8192):

    buffer += chunk

    start = buffer.find(b"\xff\xd8")
    end = buffer.find(b"\xff\xd9")

    if start == -1 or end == -1:
        continue

    jpg = buffer[start:end + 2]
    buffer = buffer[end + 2:]


    # ==================================================
    # DECODE IMAGE
    # ==================================================

    try:

        image = Image.open(
            BytesIO(jpg)
        ).convert("RGB")

        frame = cv2.cvtColor(
            np.array(image),
            cv2.COLOR_RGB2BGR
        )

    except:

        continue


    frame_count += 1

    frame = cv2.resize(
        frame,
        (640, 480)
    )


    # ==================================================
    # YOLO HUMAN DETECTION
    # ==================================================

    if frame_count % 3 == 0:

        results = model(
            frame,
            imgsz=320,
            conf=0.4,
            verbose=False
        )

        camera_human = False


        for result in results:

            for box in result.boxes:

                class_id = int(
                    box.cls[0]
                )

                confidence = float(
                    box.conf[0]
                )


                # YOLO class 0 = PERSON

                if class_id == 0:

                    camera_human = True

                    x1, y1, x2, y2 = map(
                        int,
                        box.xyxy[0]
                    )


                    cv2.rectangle(
                        frame,
                        (x1, y1),
                        (x2, y2),
                        (0, 255, 0),
                        3
                    )


                    cv2.putText(
                        frame,
                        f"PERSON {confidence:.2f}",
                        (x1, y1 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.7,
                        (0, 255, 0),
                        2
                    )


    # ==================================================
    # GET ESP32 SENSOR DATA
    # ==================================================

    try:

        esp_response = requests.get(
            ESP32_URL,
            timeout=1
        )

        data = esp_response.json()


        temperature = data["temperature"]
        room_dark = data["room_dark"]
        door_open = data["door_open"]
        door_openings = data["door_openings"]
        pir_human = data["human_present"]
        light_on = data["light_on"]


    except Exception:

        temperature = None
        room_dark = False
        door_open = False
        door_openings = 0
        pir_human = False
        light_on = False


    # ==================================================
    # COMBINE HUMAN DETECTION
    # ==================================================

    # Camera OR PIR

    human_present = (
        camera_human or pir_human
    )


    # ==================================================
    # DISPLAY
    # ==================================================

    if human_present:

        status = "HUMAN DETECTED"

    else:

        status = "NO HUMAN"


    cv2.putText(
        frame,
        status,
        (20, 40),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (0, 255, 0) if human_present
        else (0, 0, 255),
        2
    )


    cv2.imshow(
        "HOUSE BRAIN - CAMERA",
        frame
    )


    # ==================================================
    # HOUSE REPORT
    # ==================================================

    current_time = time.time()


    # Print report every 5 seconds

    if current_time - last_report_time >= 5:

        last_report_time = current_time


        print()
        print("----------------------------------------------")
        print("🏠 HOUSE BRAIN REPORT")
        print("----------------------------------------------")


        print(
            "👤 Human:",
            "PRESENT" if human_present else "ABSENT"
        )


        if temperature is not None:

            print(
                "🌡️ Temperature:",
                temperature,
                "°C"
            )

        else:

            print(
                "🌡️ Temperature: ERROR"
            )


        print(
            "💡 Light:",
            "ON" if light_on else "OFF"
        )


        print(
            "☀️ Room:",
            "DARK" if room_dark else "BRIGHT"
        )


        print(
            "🚪 Door:",
            "OPEN" if door_open else "CLOSED"
        )


        print(
            "🚪 Door openings:",
            door_openings
        )


        print(
            "👁️ Camera:",
            "HUMAN" if camera_human
            else "NO HUMAN"
        )


        print(
            "📡 PIR:",
            "HUMAN" if pir_human
            else "NO HUMAN"
        )


        # ==================================================
        # GROUP CHAT
        # ==================================================

        print()
        print("💬 HOUSE GROUP CHAT")
        print("----------------------------------------------")


        # FAN

        if temperature is not None:

            if temperature < 20:

                print(
                    "🌀 FAN: It's",
                    temperature,
                    "°C. Why am I even ON?"
                )

            elif temperature > 28:

                print(
                    "🌀 FAN: Finally!",
                    temperature,
                    "°C. I have a purpose."
                )

            else:

                print(
                    "🌀 FAN: Temperature is",
                    temperature,
                    "°C. I'm just watching."
                )


        # LIGHT

        if light_on and not room_dark:

            print(
                "💡 LIGHT: It's already bright."
            )

            print(
                "💡 LIGHT: Apparently sunlight isn't enough."
            )

        elif light_on and room_dark:

            print(
                "💡 LIGHT: Finally! Someone needs me."
            )

        else:

            print(
                "💡 LIGHT: I'm OFF. Peace."
            )


        # DOOR

        if door_open:

            print(
                "🚪 DOOR: OPEN again."
            )

        elif door_openings > 10:

            print(
                "🚪 DOOR:",
                door_openings,
                "openings."
            )

            print(
                "🚪 DOOR: Make up your mind."
            )

        else:

            print(
                "🚪 DOOR:",
                door_openings,
                "openings."
            )


        # HOUSE

        if human_present:

            print(
                "🏠 HOUSE: Human detected."
            )

            print(
                "🏠 HOUSE: Unfortunately."
            )

        else:

            print(
                "🏠 HOUSE: No human detected."
            )

            print(
                "🏠 HOUSE: Peace has been restored."
            )


        # ==================================================
        # BEHAVIOUR SCORE
        # ==================================================

        score = 100


        if (
            light_on
            and not room_dark
        ):

            score -= 20

            print(
                "⚠️ Unnecessary light usage!"
            )


        if (
            temperature is not None
            and temperature < 20
        ):

            score -= 20

            print(
                "⚠️ Questionable temperature behaviour!"
            )


        if door_openings > 10:

            score -= 20

            print(
                "⚠️ Excessive door activity!"
            )


        score = max(
            0,
            score
        )


        print()
        print("📊 HUMAN BEHAVIOUR REPORT")
        print("----------------------------------------------")

        print(
            "🎯 HUMAN SCORE:",
            score,
            "/100"
        )


        if score >= 80:

            print(
                "🏆 VERDICT: Surprisingly reasonable."
            )

        elif score >= 50:

            print(
                "⚠️ VERDICT: Questionable decisions."
            )

        else:

            print(
                "💀 VERDICT: We have concerns."
            )


        print("----------------------------------------------")


    # ==================================================
    # QUIT
    # ==================================================

    if cv2.waitKey(1) & 0xFF == ord("q"):

        break


# ==================================================
# CLEANUP
# ==================================================

response.close()

cv2.destroyAllWindows()

print()
print("HOUSE BRAIN STOPPED.")
