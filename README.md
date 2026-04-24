# 🚀 IoT-Based Boiler Monitoring System

## 📌 Overview
This project monitors temperature and pressure of **three horizontal pressure vessels** using ESP32 and sends data to the cloud (ThingSpeak).

---

## 🔧 Features
- 🌡️ Temperature monitoring (DS18B20)
- ⚙️ Pressure monitoring (4–20mA sensors)
- 📡 IoT cloud integration (ThingSpeak)
- 🚨 Alert system (Buzzer + LED)
- 🔁 Real-time data updates

---

## ⚙️ Tech Stack
- ESP32
- Arduino IDE
- ThingSpeak
- Embedded C++

---

## 🔌 Hardware Setup
- DS18B20 → GPIO 4
- Pressure Sensors → ADC Pins (GPIO 34, 35, 32)
- Buzzer → GPIO 26
- LED → GPIO 25

---

## 🚀 How to Run
1. Install required libraries
2. Upload code to ESP32
3. Connect WiFi
4. Monitor data on ThingSpeak

---

## 📊 Output
- Real-time sensor readings
- Cloud dashboard
- Alert system for high pressure

---

## 📌 Future Improvements
- Mobile app alerts
- AI-based prediction
- Advanced dashboard

---

## 👨‍💻 Author
**Dushyant Baroliya**
A real-time web dashboard simulating an IoT-based pressure vessel monitoring system using ESP32 microcontrollers, ThingSpeak, and Blynk.

Live demo → [iot-pressure-vessel-project.netlify.app](https://iot-pressure-vessel-project.netlify.app)

---

## Features

- Live simulation of temperature & pressure across 3 vessels
- Real-time line charts (Chart.js)
- Pressure threshold alerting with blinking indicators
- Adjustable heating speed (Slow / Fast)
- Configurable pressure threshold via slider
- Event log with timestamped alerts and sync messages
- Reset functionality

---

## Tech Stack

| Layer | Technology |
|---|---|
| Markup | HTML5 |
| Styling | CSS3 (CSS Variables, Grid, Flexbox) |
| Logic | Vanilla JavaScript (ES6+) |
| Charts | Chart.js v4.4.1 (CDN) |
| Hosting | Netlify (static) |
| IoT Platform (simulated) | ESP32 · ThingSpeak · Blynk |

> **Note:** The IoT hardware integration (ESP32, ThingSpeak, Blynk) is simulated in the frontend using exponential growth physics models. No real sensor data is used.

---

## Project Structure

```
iot-pressure-vessel/
├── index.html      # Complete single-file app (HTML + CSS + JS)
└── README.md
```

---

## Getting Started

### Run locally

Just open `index.html` in any browser — no build step, no dependencies, no server needed.

```bash
git clone https://github.com/YOUR_USERNAME/iot-pressure-vessel.git
cd iot-pressure-vessel
open index.html   # or double-click the file
```

### Deploy to Netlify

1. Push this repo to GitHub
2. Go to [netlify.com](https://netlify.com) → **Add new site** → **Import from Git**
3. Select your repo, leave build settings blank
4. Click **Deploy** — done

---

## How the Simulation Works

Temperature and pressure values are generated using exponential saturation models:

```js
// Temperature rises toward a max, offset per vessel
tempModel(t, v) = 25 + (t * 2.7 + offset[v]) * (1 - e^(-t/18))

// Pressure is derived from temperature
pressModel(t, v) = ((temp - 60) / 40) * 2.5 + offset[v]
```

Alerts fire when `pressure >= threshold` (default: 3.5 bar).

---

## Controls

| Control | Description |
|---|---|
| Slow / Fast | Sets tick interval (2000ms / 800ms) |
| Threshold slider | Adjusts alert trigger pressure (1.5–4.5 bar) |
| Reset | Clears all data and restarts simulation |

---

## License

MIT — free to use, modify, and distribute.

