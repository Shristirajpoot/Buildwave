# 🚧 Buildwave – Real-Time Build Monitoring System 📟🌐  

> ⚙️ Embedded system that instantly visualizes software build statuses via TFT display, LEDs, and web interface.

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![License](https://img.shields.io/github/license/Shristirajpoot/thermotrack)
![Last Commit](https://img.shields.io/github/last-commit/Shristirajpoot/Buildwave?color=green)
![Repo Stars](https://img.shields.io/github/stars/Shristirajpoot/Buildwave?style=social)

---

## 🌟 Overview

**Buildwave** is a **real-time embedded build monitoring system** using an Arduino microcontroller.  
It combines **networking**, **visual feedback**, and **hardware interaction** to provide instant insights into software build statuses—both visually (LCD + LEDs) and via an HTTP-based web interface.

Ideal for **CI/CD pipelines, devops teams**, or **classroom demonstrations** of embedded system + software integration.

---

## 🚀 Features

- 📺 **TFT LCD Display** — Shows live build info: project, version, user, result, description  
- 🌐 **Web Interface** — Accepts HTTP POST requests with build status in JSON  
- 🔴🟢 **LED Indicators** — Red for failure, green for success  
- ⚠️ **Error Display** — Handles and displays malformed or missing data  
- 🧠 **Smart Feedback** — Displays human-readable messages and diagnostics  

---

## 🛠️ Technologies Used

| Component       | Description                                  |
|----------------|----------------------------------------------|
| 💻 Microcontroller | Arduino UNO (or compatible)              |
| 🌐 Networking   | Ethernet Shield + HTTP Server               |
| 📺 Display      | TFT LCD using Adafruit GFX + TFTLCD libs    |
| 🔄 JSON Parser  | ArduinoJson                                 |
| 🧵 Threading    | `Thread` library for timed tasks            |
| 🔌 LEDs         | For visual success/failure signal           |

---

## 📂 Project Structure

```plaintext
Buildwave/
├── BuildWave.ino       # Main Arduino sketch
├── README.md           # Project documentation
└── .gitattributes      # Line-ending normalization
```

## 🔧 Setup Instructions

### 🖥️ Hardware Setup
- Connect Arduino to your PC (via USB).

- Mount the Ethernet Shield onto Arduino.

- Wire the TFT LCD as per your screen model and pin mapping in code.

- Connect:

- 🟢 Green LED (success) to pin 3

- 🔴 Red LED (failure) to pin 10

## 💾 Software Setup
- Install Arduino IDE
➤ Download here

- Install Required Libraries

  - Adafruit GFX

  - Adafruit TFTLCD

  - ArduinoJson

  - Thread

(Use Library Manager inside Arduino IDE)

- Upload the Code

  - Open BuildWave.ino

  - Adjust IP address to match your network

  - Upload to board via USB

## ▶️ Running the Project
After uploading:

- The Arduino runs a web server on port 80

- LCD displays build status live

- Send HTTP POST requests to update status

- LEDs reflect build result (✅ green = success, ❌ red = failure)

## 📨 Example JSON Request
Send an HTTP POST to the Arduino's IP address with the following payload:

```json
{
  "stat": "s",
  "proj": "Project X",
  "build": "Build v1.2",
  "usu": "John Doe",
  "desc": "Build completed successfully."
}
```
- stat: "s" (success), "f" (failure), or "p" (in progress)

- proj: Project name

- build: Build version/label

- usu: User/owner of build

- desc: Optional description (esp. for failures)

## 🛣️ Roadmap / Ideas

- 📡 Add Wi-Fi support (ESP32 version)

- 💻 Web dashboard for history & analytics

- 🔐 Authenticated endpoints

- 🔊 Add buzzer for audio alert

## 🤝 Contributing
We welcome your ideas and PRs!

- Fork this repo

- Create a branch: git checkout -b feature/your-feature

- Commit & push

- Open a pull request with your changes

## 👩‍💻 Author
### Shristi Rajpoot
- 📧 shristirajpoot369@gmail.com
-  🔗 @Shristirajpoot

## 📄 License
Released under the MIT License – see LICENSE for details.

### ⭐ If this helped you streamline your embedded builds or inspired a project, consider starring the repo!
