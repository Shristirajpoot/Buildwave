# Buildwave: Real-Time Build Monitoring and Management System

## Overview
**Buildwave** is a **real-time build monitoring system** built on an embedded platform, designed to streamline the management and visualization of software build statuses. The system uses an Arduino-based microcontroller with Ethernet connectivity to provide instant feedback on build processes through both a **visual TFT LCD display** and a **web interface**. Buildwave helps to detect build issues immediately, allowing developers to address issues faster, improving overall productivity.

This project combines **real-time embedded system design**, **networking**, and **UI development**. It is ideal for applications where efficient build monitoring, status reporting, and hardware interaction are crucial.

---

## Key Features

- <span style="color:green;">**Real-Time Monitoring**</span>: Displays current build status (**Success**, **Failure**, **In Progress**) on a TFT LCD display.
- <span style="color:blue;">**Web Interface**</span>: A simple, self-hosted HTTP server that receives and processes build status updates in **JSON** format.
- <span style="color:red;">**LED Indicators**</span>: Success and failure statuses are indicated using **LEDs**, providing a quick visual signal for the current build status.
- <span style="color:orange;">**Error Handling**</span>: Displays error messages on the LCD screen for invalid or missing data, providing immediate feedback to the user.
- <span style="color:purple;">**User-Friendly Interface**</span>: The project includes an easy-to-read display of project information such as **project name**, **build number**, **user**, and **description** of failure if any.

---

## Technologies Used

- **Embedded System Platform**: Built using **Arduino** for microcontroller functionality.
- **Libraries**:
  - **Adafruit GFX** and **Adafruit TFTLCD** for handling the graphical LCD display.
  - **ArduinoJson** for parsing and managing JSON data from web requests.
  - **Thread** for handling timed tasks such as LED blink patterns.
  - **Ethernet** for networking and communication between the embedded system and the client machine.
- **Programming Languages**: **C/C++** (Arduino IDE)
- **Networking**: **HTTP** web server that allows interaction via a browser or HTTP client.
- **Hardware Components**: **Arduino**-based microcontroller, **Ethernet shield**, **TFT LCD screen**, **LEDs**, and various resistors/cables.

---

## Setup Instructions

### Hardware Setup
1. **Connect the Arduino to your PC** using a **USB cable** for programming.
2. **Attach the Ethernet Shield** to the Arduino to provide networking capabilities.
3. **Connect the TFT LCD Screen** to the designated pins on the Arduino as per the schematic.
4. **Connect LEDs**: Connect the success and failure LEDs to the pins specified in the code (e.g., pin 3 for success, pin 10 for failure).

### Software Setup
1. **Install Arduino IDE**: Ensure that you have the Arduino IDE installed on your machine. You can download it from [here](https://www.arduino.cc/en/software).
2. **Install Libraries**:
   - Install **Adafruit GFX** and **Adafruit TFTLCD** libraries from the Library Manager in the Arduino IDE.
   - Install **ArduinoJson** via the Library Manager.
   - Install **Thread** library if needed.
3. **Upload Code**: Open the `Buildwave.ino` file in the Arduino IDE and upload the code to your Arduino board.
4. **Network Configuration**: Ensure that your Arduino is connected to the local network via Ethernet. You may need to modify the IP address in the code to match your network configuration.

### Running the Project
Once uploaded, the system will:
- Start the embedded HTTP server on port **80**.
- Display the status of the build process on the **TFT LCD**.
- Update the status in **real-time** based on incoming HTTP requests with build information.
- Visual feedback will be shown via **LEDs** (green for success, red for failure).
- Display detailed information on a failure including project name, user, and description of the failure.

###Contributing
We welcome contributions to improve this project! If you find a bug or have an idea for a new feature, feel free to open an issue or submit a pull request.

To contribute:

Fork the repository.
Clone your fork to your local machine.
Make changes and push them to your fork.
Create a pull request to the original repository.


### Example JSON Request to Update Build Status
To send build status updates to the system, use a **POST** request with the following **JSON** structure:
```json
{
  "stat": "s",        
  "proj": "Project X", 
  "build": "Build v1.2", 
  "usu": "John Doe",
  "desc": "Build completed successfully." 
}

