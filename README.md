<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



#  USELESS HOME 🎯

## Basic Details

Domain: IoT, Embedded Systems & Computer Vision

Main Platform: ESP32-WROOM + Python

Key Technologies: ESP32, Python, YOLO11, OpenCV, IoT Sensors, Computer Vision and Wi-Fi Communication.

Core Function: The phone camera and YOLO11 detect human presence, while the ESP32 collects temperature, light, motion and door activity. The Python-based House Brain combines these inputs to generate sarcastic observations, object conversations and a Human Behaviour Score.

Objective: To create a humorous IoT system where household objects monitor human activity, communicate their observations, and sarcastically judge the user's behaviour instead of serving a conventional useful purpose.


### Team Name: [WHY NOT?]


### Team Members
- Team Lead: Aldrin joseph - Muthoot Institute of Technology and Science 
- Member 2: Sain P Savin - Muthoot institute of Technology and Science 

### Project Description

HouseWithOpinions is a humorous IoT and computer vision project that turns a house into an overly opinionated observer. A phone camera and YOLO11 detect human presence, while an ESP32 collects information such as temperature, light conditions, motion and door activity. The Python-based House Brain combines these inputs and generates sarcastic observations, object conversations and judgments about the human.

Instead of helping the user, the house watches, gossips and judges them.

### The Problem (that doesn't exist)

Modern smart homes are designed to make life easier through automation, security and energy management.

But one important problem has been completely ignored:

**The house has no opinions about its owner.**

It cannot complain about unnecessary light usage, question repeated door openings, or wonder why someone is sitting around while the fan is running.

Clearly, this unacceptable lack of household criticism needed to be solved.

### The Solution (that nobody asked for)

HouseWithOpinions gives ordinary household objects completely unnecessary personalities.

- 🌀 **Fan:** Comments on the measured temperature and questions its purpose.
- 💡 **Light:** Complains about unnecessary usage.
- 🚪 **Door:** Counts how many times it is opened and judges the activity.
- 👤 **House:** Detects human presence and reacts sarcastically.
- 🧠 **House Brain:** Combines sensor and camera data to generate observations and a Human Behaviour Score.

The system does not try to save energy, improve security or make life easier.

**It simply watches, discusses and judges.**


## Technical Details

**Microcontroller:** ESP32-WROOM

**Programming Languages:** C/C++ for ESP32 and Python for computer vision and data processing

**Computer Vision:** YOLO11 with OpenCV

**Camera:** Smartphone camera used as the visual input through an IP camera stream

**Communication:** Wi-Fi communication between the ESP32 and Python-based House Brain using HTTP requests

**Processing:** Real-time human presence detection using YOLO11 combined with ESP32 sensor data

**Sensor Monitoring:** Temperature, light intensity, human motion and door activity

**Light Control:** ESP32 automatically controls the RGB LED based on LDR light-level readings

**Fan Monitoring:** DHT22 measures the surrounding temperature, which is used by the Fan personality for sarcastic commentary

**Development Environment:** Arduino IDE and Python environment

**System Type:** IoT-based embedded monitoring system with computer-vision-based human detection and humorous behavioural analysis


### Technologies/Components Used

#### For Software:

- **Languages used:** C/C++, Python
- **Frameworks used:** Arduino Framework
- **Computer Vision:** YOLO11, OpenCV
- **Python Libraries:** Ultralytics, OpenCV, Requests, NumPy, Pillow
- **Communication:** HTTP over Wi-Fi
- **Tools used:** Arduino IDE, Python, Smartphone IP Camera


#### For Hardware:

- ESP32-WROOM
- DHT22 Temperature Sensor
- LDR Sensor
- PIR Motion Sensor
- IR Door Sensor
- RGB LED
- Fan
- Breadboard
- Jumper Wires
- 220Ω Resistors


#### Hardware Specifications:

**ESP32-WROOM:** 3.3V logic, Wi-Fi and Bluetooth enabled

**DHT22:** Digital temperature sensing; temperature data is used for fan-related observations

**LDR:** Analog light-intensity sensing

**IR Sensor:** Digital door/opening detection

**PIR Sensor:** Human motion/presence detection

**RGB LED:** Visual light output controlled by the ESP32 according to room brightness

**Fan:** Household object monitored through temperature readings; not electronically controlled

**Breadboard:** Circuit prototyping and component connections

**Jumper Wires:** Electrical connections between components

**220Ω Resistors:** Current limiting for RGB LED connections


#### Tools Required:

- Arduino IDE
- Python
- Laptop/Computer
- Smartphone with IP Camera application
- USB Cable
- Wi-Fi Network

## Implementation

### Software Implementation

The system is implemented using two main programs:

1. **ESP32 Firmware** – Collects sensor data, controls the RGB LED based on room brightness, counts door openings, and provides sensor data through a Wi-Fi HTTP server.
2. **Python House Brain** – Receives ESP32 data, processes the smartphone camera stream using YOLO11, detects human presence, and generates the sarcastic House Group Chat and Human Behaviour Score.

### Installation

#### ESP32

1. Install Arduino IDE.
2. Install the ESP32 board package.
3. Install the required libraries:
   - WiFi
   - WebServer
   - DHT Sensor Library
4. Connect the sensors and RGB LED according to the pin configuration.
5. Enter your Wi-Fi credentials in the ESP32 program.
6. Upload the ESP32 firmware.
7. Note the IP address displayed in the Serial Monitor.

#### Python

Install the required Python libraries:

```bash
pip install ultralytics opencv-python requests numpy pillow

##Arduino Code 

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

##Python Code 

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

# Run

Start the smartphone IP camera application first.

Then run the Python House Brain:

```bash
python house_brain.py


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

Short description:
The smartphone camera provides visual input for YOLO11-based human detection, while the ESP32 collects temperature, light, motion and door activity data. The Python House Brain combines these inputs to generate sarcastic observations, object conversations and a Human Behaviour Score.
For Hardware:

# Schematic & Circuit
![Circuit]<img width="768" height="1024" alt="WhatsApp Image 2026-09-04 at 10 48 33 AM" src="https://github.com/user-attachments/assets/9e7f8bd1-b261-42a6-9e20-8b7fc6468d01" />


![Schematic]
<img width="1536" height="1024" alt="WhatsApp Image 2026-09-04 at 11 16 54 AM" src="https://github.com/user-attachments/assets/c4c6138a-1722-4f87-b6c2-f476af0fd5b5" />
The phone camera detects human presence using Python/OpenCV, while the ESP32 receives the result and sensor inputs to control the connected devices automatically.


# Build Photos
![Components]


![Build]
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/ea1531db-7d2c-4952-a0b6-77b86338d259" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/617fcc79-c0be-4180-a9ca-8daf7b84a8bc" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/01041ad1-367f-40d2-810a-780441fdf20e" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/9db76325-e23c-4fb1-81bc-a7ff10e9fdb6" />
<img width="1080" height="1440" alt="image" src="https://github.com/user-attachments/assets/fc87a7ef-8a7f-4584-9e57-f8da85db72be" />
Step-by-Step Build

1. Connect the sensors and RGB LED to the ESP32-WROOM.
2. Program the ESP32 using Arduino IDE to read the sensor inputs.
3. Set up the phone camera with Python and OpenCV.
4. Use Python to detect whether a human is present.
5. Send the detection result from Python to the ESP32.
6. The ESP32 processes the result and controls the connected devices automatically.
7. Test all components together and run the system continuously.


![Final]
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/8f48d561-0939-4757-a9ca-e4bc412ac411" />
<img width="899" height="987" alt="image" src="https://github.com/user-attachments/assets/9b61ac3e-cf4d-44b1-91d6-86143a36c7aa" />



### Project Demo
# Video
https://drive.google.com/drive/folders/1TKBacUugVNqEFkTk8R9H-I7IMc4b260b
Our project is a smart home automation system using ESP32 and Python. A phone camera captures live video. Python and OpenCV detect whether a human is present. The detection result is sent to the ESP32. The ESP32 also receives data from different sensors. It processes all the inputs together. Based on the conditions, it controls the connected devices. The system can monitor light, motion, door status, temperature, and humidity. This reduces unnecessary manual control. Overall, the project combines computer vision and embedded automation in one simple system.

# Additional Demos
https://drive.google.com/drive/folders/1oICfdNwpuUVN8U2ifv4jcr7-Zq_J_9uF

## Team Contributions
- [Aldrin Joseph]: [python code,phone camera and motion sensors]
- [Sain P Savin]: [arduino code,LR , PIR sensors]
- [Name 3]: [Specific contributions]

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



