<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



#  USELESS HOME 🎯

## Basic Details

Domain: IoT, Embedded Systems & Computer Vision

Main Platform: ESP32-WROOM + Python

Key Technologies: ESP32, Python, YOLO11, OpenCV, IoT Sensors, Computer Vision and Wi-Fi Communication.

Core Function: The phone camera and YOLO11 detect human presence, while the ESP32 collects temperature, light, motion and door activity. The Python-based House Brain combines these inputs to generate sarcastic observations, object conversations and a Human Behaviour Score.

Objective: To create a humorous IoT system where household objects monitor human activity, communicate their observations, and sarcastically judge the user's behaviour instead of serving a conventional useful purpose.


### Team Name: WHY NOT?


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

Install the required Python libraries using python command pip install ultralytics opencv-python requests numpy pillow in the terminal.


# Run

Start the smartphone IP camera application first.

Then run the Python House Brain:

```bash
python house_brain.py


##Project Documentation


# Diagrams

System Workflow


📱 Smartphone Camera
        ↓
💻 Python + YOLO11
        ↓
👤 Human Detection

        +

📡 ESP32
   ├── 🌡️ DHT22 → Temperature of fan 
   ├── 💡 LDR → Light Level
   ├── 👤 PIR → Motion
   ├── 🚪 IR Sensor → Door Activity
   └── 💡 RGB LED → Light Output

        ↓
   Wi-Fi / HTTP
        ↓
🧠 Python House Brain
        ↓
💬 House Group Chat
        ↓
📊 Human Behaviour Score
        ↓
🏠 Sarcastic House Verdict

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

### Step-by-Step Build

1. Connect the DHT22, LDR, PIR sensor, IR sensor and RGB LED to the ESP32-WROOM.
2. Connect the RGB LED through appropriate current-limiting resistors.
3. Set up the fan as one of the household objects represented in the system.
4. Program the ESP32 using Arduino IDE to collect temperature, light, motion and door activity data.
5. Configure the LDR threshold so the ESP32 automatically controls the RGB LED based on room brightness.
6. Set up the smartphone as an IP camera and connect it to the Python program.
7. Use YOLO11 to detect human presence from the camera stream.
8. Connect the Python House Brain to the ESP32 through Wi-Fi and retrieve the sensor data.
9. Combine the camera and ESP32 sensor data in the Python House Brain.
10. Generate sarcastic observations, the House Group Chat and the Human Behaviour Score.
11. Test the complete system with the fan, light, door and human presence detection.
12. Run the system continuously and observe the house's opinions about the user.


![Final]
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/8f48d561-0939-4757-a9ca-e4bc412ac411" />
<img width="899" height="987" alt="image" src="https://github.com/user-attachments/assets/9b61ac3e-cf4d-44b1-91d6-86143a36c7aa" />



### Project Demo
# Video
https://drive.google.com/drive/folders/1TKBacUugVNqEFkTk8R9H-I7IMc4b260b

The project demo showcases **HouseWithOpinions**, a humorous IoT and computer vision system where household objects monitor and judge human behaviour.

A smartphone camera provides the visual input for YOLO11-based human detection, while the ESP32 collects temperature, light, motion and door activity data. The Python-based House Brain combines these inputs and generates sarcastic conversations between the household objects.

The system also produces a **Human Behaviour Score** and a humorous final verdict based on the observed behaviour.

Instead of automating the home to make life easier, the system simply **watches, discusses and judges.**

# Additional Demos
https://drive.google.com/drive/folders/1oICfdNwpuUVN8U2ifv4jcr7-Zq_J_9uF

## Team Contributions
- [Aldrin Joseph]: [python code,phone camera and motion sensors]
- [Sain P Savin]: [arduino code,LR , PIR sensors]

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



