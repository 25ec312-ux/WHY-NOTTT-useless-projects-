# 🏠 The House Has a Group Chat

## Useful Technology. Useless Purpose.

> What if your house could talk about you behind your back?

**The House Has a Group Chat** is an IoT-based smart-home project where everyday household objects observe human activity and communicate with each other.

Instead of performing useful automation, the system watches the human, detects what is happening, and allows the objects to **gossip, comment and judge the user's behaviour.**

### We didn't build a smart home.

### We built a home that thinks you're stupid. 😂

---

# 💡 Concept

The project combines physical sensors, an ESP32 and Python-based computer vision to create a fictional communication system between household objects.

The system currently includes:

- 💡 Smart Light
- 🚪 Smart Door
- 📷 Human Detection Camera
- 🧠 ESP32 Controller
- 💻 Python Computer Vision

The objects don't actually solve a real-world problem.

They simply observe what the human is doing and talk about it.

---

# 🎯 Objective

The objective is to demonstrate technically useful technologies through an intentionally useless and entertaining application.

The project demonstrates:

- IoT
- Embedded Systems
- ESP32 Programming
- Sensor Interfacing
- Computer Vision
- Python Programming
- Human Detection
- Data Processing
- Human-Computer Interaction
- Object-to-Object Communication

---

# 🤡 Why Is It Useless?

A normal smart-home system might:

- Save energy
- Improve security
- Automate appliances
- Monitor useful information
- Make decisions for the user

Our system does none of that.

Instead, it:

- Watches the human
- Counts events
- Comments on behaviour
- Lets objects gossip with each other
- Produces unnecessary observations

### The technology is useful.

### The purpose is completely useless.

---

# 🧩 System Components

## 💡 Light Object

The light system uses an **LDR (Light Dependent Resistor)** to detect the surrounding light level.

The ESP32 reads the LDR value and determines whether the environment is relatively bright or dark.

An RGB LED represents the smart light.

Example:

> 💡 Light: "It's bright outside and I'm still being used."

---

## 🚪 Door Object

The door system uses an **IR sensor** to detect the door/activity state.

The ESP32 continuously reads the IR sensor and identifies changes in its state.

Example:

> 🚪 Door: "He opened me again."

> 🚪 Door: "That's the 14th time today."

---

## 📷 Camera Object

A webcam is connected to a computer running a Python program.

The Python computer-vision system analyzes the camera feed and determines whether a human is present.

The system produces two basic states:

```text
👤 HUMAN DETECTED

or

🚫 NO HUMAN DETECTED
