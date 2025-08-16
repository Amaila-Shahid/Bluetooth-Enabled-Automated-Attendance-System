# 📡 Bluetooth-Enabled Automated Attendance System

A smart **IoT-based attendance system** using **ESP32**, **Bluetooth scanning**, and **Google Sheets integration** 📋.  
This project automatically marks students **present** when their registered Bluetooth devices are detected nearby — **no manual roll call needed!** 🎯  

---

## ✨ Features
- 🔍 **Bluetooth Scanning** – Detects nearby devices using ESP32’s built-in Bluetooth.
- 📄 **Google Sheets Integration** – Sends attendance data to a live Google Sheet via Google Apps Script.
- ⚡ **Fast & Automatic** – No human intervention required after setup.
- 📶 **WiFi Enabled** – Uses your WiFi to send data in real-time.
- 🛠 **Customizable Student List** – Easily add/remove students with their Bluetooth MAC addresses.

---

## 🖥 Hardware Requirements
- **ESP32 Development Board** (with Bluetooth & WiFi)
- USB Cable for programming
- Power source for ESP32
- Devices with **Bluetooth enabled** (phones, smartwatches, etc.)

---

## 📦 Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 Board Package installed in Arduino IDE
- [Google Apps Script](https://script.google.com/) for Google Sheets integration
- GitHub account (optional for sharing)

---

## 🛠 Wiring & Setup
No extra wiring needed! This project uses:
- **WiFi** for internet connectivity
- **Bluetooth** for device detection

---

## ⚙️ Configuration

### 1️⃣ Update WiFi Credentials
In the code, replace:
```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
