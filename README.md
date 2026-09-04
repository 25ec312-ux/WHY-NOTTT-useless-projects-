<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# [Project Name] 🎯
  USELESS HOME

## Basic Detail

Domain: IoT, Embedded Systems & Computer Vision

Main Platform: ESP32-WROOM + Python

Key Technologies: Python, OpenCV, phone camera, ESP32, sensors and actuators.

Core Function: The phone camera and Python-based computer vision detect whether a human is present. Based on the detected condition, the ESP32 controls the connected smart-home components automatically.

Objective: To combine computer vision with ESP32-based automation to create a simple and intelligent smart-home system.

### Team Name: [WHY NOT?]


### Team Members
- Team Lead: [Aldrin joseph] - [Muthoot institute of science and technology ]
- Member 2: [Sain P Savin] - [Muthoot institute of science and technology]
- Member 3: [Name] - [College]

### Project Description
This project is a smart home automation system that combines an ESP32 with Python-based computer vision using a phone camera. It detects human presence and uses sensor inputs to intelligently control connected devices, making the system simple, responsive, and automated.

### The Problem (that doesn't exist)

In everyday situations, people often forget to switch lights or other devices on/off depending on whether someone is actually present in the room. This fun project explores a simple solution using human detection through a phone camera and Python, combined with ESP32-based automation, to make the system respond automatically to the presence of a person.

### The Solution (that nobody asked for)

The system uses a phone camera and Python-based computer vision to detect whether a person is present. The detection result is sent to the ESP32, which processes it along with sensor inputs and automatically controls the connected devices based on the person's presence.

## Technical Details

Microcontroller: ESP32-WROOM

Programming Language: C/C++ for ESP32 and Python for computer vision

Computer Vision: Python with OpenCV

Camera: Smartphone camera used as the visual input

Communication: Python sends the human-detection result to the ESP32

Processing: Real-time human presence detection followed by automated device control

Development Environment: Arduino IDE and Python environment

System Type: Embedded automation with computer-vision-based control
### Technologies/Components Used
For Software:
- [Languages used:c,c++,python]
- [Frameworks used:Arduino Framework,Opencv]
- [Libraries used:ESP32 Arduino core,Opencv,pyserial]
- [Tools used:Arduino IDE,python IDE,Smartphone camera]

For Hardware:
- [List main components]
ESP32-WROOM ,LDR sensor,IR sensor,PIR sensor,DHT sensor,RGB LED,Breadboard
- [List specifications]

ESP32-WROOM: 3.3 V logic, Wi-Fi and Bluetooth enabled

Smartphone Camera: Used for real-time video input

LDR: Analog light-intensity sensing

IR Sensor: Digital object/door detection

PIR Sensor: Human motion detection

DHT Sensor: Temperature and humidity measurement

RGB LED: Red, green and blue light output

Breadboard: Circuit prototyping

Jumper Wires: Component connections

Resistors: Current limiting and circuit protection
- [List tools required]

Arduino IDE

Python

OpenCV

VS Code

USB cable

Computer/Laptop

Smartphone

### Implementation
For Software:
# Installation
[commands]
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// ================= WIFI =================

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);


// ================= PINS =================

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define IR_PIN 23
#define LDR_PIN 34
#define PIR_PIN 27

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
arduino code

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

python code

# Run
[commands]

### Project Documentation


# Diagrams
![Workflow]
Project Workflow

Phone Camera
↓
Python + OpenCV
↓
Human Detection
↓
Human Present / Not Present
↓
Send Result to ESP32
↓
ESP32 Processes the Result + Sensor Inputs
↓
Automatic Control of Connected Devices
↓
Continuous Monitoring

Very short description:
The phone camera detects human presence using Python, and the result is sent to the ESP32 for automatic device control.

For Hardware:

# Schematic & Circuit
![Circuit]



![Schematic](Add your schematic diagram here)
*Add caption explaining the schematic*

# Build Photos
![Components](Add photo of your components here)
*List out all components shown*

![Build](Add photos of build process here)
*Explain the build steps*

![Final](Add photo of final product here)
*Explain the final build*

### Project Demo
# Video
[Add your demo video link here]
*Explain what the video demonstrates*

# Additional Demos
[Add any extra demo materials/links]

## Team Contributions
- [Name 1]: [Specific contributions]
- [Name 2]: [Specific contributions]
- [Name 3]: [Specific contributions]

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



