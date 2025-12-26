# 💉 Smart Infusion Pump Controller

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![Sensors](https://img.shields.io/badge/Sensors-Flow%20%7C%20FSR%20%7C%20Thermistor-orange)
![Domain](https://img.shields.io/badge/Domain-Biomedical%20Engineering-red)

## 📌 Project Overview
This project is a safety-critical **Infusion Pump Control System** based on **Arduino**. It is designed to regulate fluid delivery while actively monitoring for common hazards like occlusions (blockages) and hypothermia risks due to cold fluids.

The system features a closed-loop feedback mechanism using a flow sensor and provides real-time data visualization via an LCD interface.

## ⚙️ Key Features
* **Real-time Flow Monitoring:** Uses a **YF-S201 Hall Effect Sensor** to calculate and display the infusion rate in Liters/Hour.
* **Occlusion Detection:** Integrated **Force Sensitive Resistor (FSR)** to detect high pressure in the tube (indicating blockage) and trigger a visual alarm (Yellow LED).
* **Temperature Safety:** Monitors fluid temperature using an **NTC Thermistor**. If the temp drops below 35°C (Hypothermia risk), it triggers a safety alert (White LED).
* **Pump Control:** Automates the pumping mechanism via a Relay module with precise timing intervals.
* **User Interface:** Displays vital metrics (Flow Rate, Status) on a **16x2 LCD**.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Uno / Nano.
* **Sensors:**
    * YF-S201 Water Flow Sensor.
    * FSR (Force Sensitive Resistor) for pressure.
    * NTC Thermistor (10k) for temperature.
* **Actuators:** DC Water Pump (via Relay).
* **Display:** LiquidCrystal Display (16x2).

## 🔌 Circuit Logic
* **Flow Rate:** Calculated via interrupt on Pin 2 (Rising Edge).
* **Pressure Threshold:** FSR readings > 400 trigger the occlusion alarm.
* **Temp Threshold:** Readings < 35°C trigger the low-temp warning.

## 🚀 How to Run
1.  Connect the components according to the pinout defined in `src/infusion_pump.ino`.
2.  Open the project in **Arduino IDE**.
3.  Install required libraries (`LiquidCrystal`).
4.  Upload the code and open the Serial Monitor (Baud Rate: 9600).