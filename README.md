# 🌦️ IoT-Based Weather Monitoring System w/ Live Server

<p align="center">
  <img src="https://github.com/haider-sama/IoT-Based-Weather-Monitoring-System-w-a-Live-Server-/blob/main/screenshots/proteus.png" alt="IoT Weather Monitoring" width="600"/>
</p>

## 📖 Introduction
This project implements an **IoT-based Weather Monitoring System** capable of measuring and displaying real-time environmental parameters such as:  
- 🌡️ Temperature  
- 🌫️ Humidity  
- 🏔️ Altitude  
- 🌪️ Pressure  
- 🌧️ Rainfall Detection  

The system uses **Arduino Mega 2560** with sensors (**DHT11, BMP180, Rain Sensor**) and communicates data to the cloud via **ThingSpeak API** using a **NodeMCU ESP8266 WiFi Module**.  

Real-time readings are:  
- Displayed on the Arduino Serial Monitor  
- Logged to the cloud for live monitoring  
- Shown locally on a **16x2 LCD**  

This project fulfills the requirements of a **Complex Engineering Problem (CEP)** and **Complex Engineering Activity (CEA)** through sensor integration, signal conditioning, and full system-level design & testing.  

---

## 🎯 Objectives
- Measure atmospheric parameters (temperature, altitude, humidity, pressure, rainfall).  
- Perform **basic signal conditioning** for sensor inputs.  
- Simulate, implement, and test a complete weather monitoring system.  
- Send real-time data to a **cloud server** for live visualization.  

---

## 🛠️ Components Used
- Arduino Mega 2560  
- DHT11 Temperature & Humidity Sensor  
- BMP180 Pressure Sensor  
- Rain Sensor (YL-83 Module)  
- ESP8266 NodeMCU (for WiFi & ThingSpeak API)  
- 16x2 LCD with PCF8574 I2C Serial Interface Adapter  
- Breadboard, jumper wires, USB cable  

---

## 📂 Project Structure

📁 WebServer/
<br />
├── server.js # Node.js server implementation
<br />
└── other node files...

📁 iot_based_weather_monitoring/
<br />
├── proteus_simulation/ # Proteus design files for circuit simulation
<br />
└── sketch_iot_based_monitoring/
<br />
└── sketch.ino # Arduino implementation

## 🚀 How to Run
1. **Arduino Setup**  
   - Open `sketch_iot_based_monitoring/sketch.ino` in Arduino IDE.  
   - Connect your **Arduino Mega 2560** and upload the sketch.  
   - Ensure sensors are wired as per Proteus schematic.  

2. **Server Setup**  
   - Navigate to the `WebServer/` folder.  
   - Install dependencies:  
     ```bash
     npm install
     ```  
   - Run the Node.js server:  
     ```bash
     node server.js
     ```  

3. **ThingSpeak Integration (deprecated - now only using NodeJS)**
   - Configure your **ThingSpeak API key** in the Arduino code.  
   - Monitor real-time weather data on your ThingSpeak channel.  

---

## 📌 Reference
- Live weather monitoring system successfully implemented using **IoT + Arduino + NodeMCU**.  
- Full implementation details, objectives, and testing provided in the **report file**.  

---
