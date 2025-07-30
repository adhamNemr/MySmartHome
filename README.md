# 🏠 Smart Home with IoT

## 📌 Overview
The **Smart Home Project** is an IoT-based system that enables remote monitoring and control of home devices using sensors and microcontrollers.  
The system is designed to provide **automation, security, and energy efficiency** with real-time data collection.

---

## 🚀 Features
- 🌡️ **Temperature & Humidity Monitoring** (DHT22 Sensor)
- 💡 **Smart Lighting Control** (Photoresistor LDR)
- 🚪 **Door/Window Security** (Magnetic Reed Switch)
- 🔥 **Fire & Gas Detection** (Flame Sensor + MQ-2 Gas Sensor)
- 🌧️ **Rain Detection**
- 👀 **Motion Detection** (PIR Sensor)
- 📊 Real-time data logging and dashboard for analytics

---

## 🛠️ Tech Stack
### **Hardware:**
- ESP32-S Development Board (WiFi + Bluetooth)
- Multiple IoT sensors: DHT22, PIR, MQ-2, Reed Switch, LDR, Rain Sensor, Flame Sensor

### **Software:**
- **Arduino IDE** (C/C++ for ESP32)
- **Node.js Backend** (for API & dashboard)
- **MySQL Database** (for data storage)

---

## 🖼️ System Architecture
![Smart Home Architecture](./Presentation/Smart%20Home%20Presentaion.pdf)

---

## ⚡ How It Works
1. **Sensors** collect environmental data (temperature, motion, fire detection, etc.).
2. **ESP32 Controller** processes data and sends it via Wi-Fi to the backend.
3. **Node.js Server** stores data and triggers alerts or device actions.
4. **Dashboard** displays real-time status and analytics.

---

## 📂 Project Structure

📦 Smart Home
┣ 📂 Arduino iDE           # ESP32 firmware
┣ 📂 DOCUMENTATION         # PDF documentation
┣ 📂 Presentation          # Project presentation
┣ 📂 screenshots           # UI and dashboard screenshots
┗ 📜 README.md


---

## 📸 Screenshots
*(Add screenshots if you have them from the dashboard or devices)*

---

## 🔮 Future Enhancements
- Mobile App for real-time notifications
- Voice Assistant Integration (Alexa / Google Home)
- AI-based automation (predictive behavior)

---

## 👤 Author
**Adham Nemr**  
[LinkedIn](https://www.linkedin.com/in/adham-nemr) | [GitHub](https://github.com/adhamNemr)
