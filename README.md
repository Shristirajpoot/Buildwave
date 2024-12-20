Buildwave

Buildwave is an innovative project designed to monitor and manage build statuses in real-time. Using an embedded system with an Ethernet connection, this project tracks the success, failure, and progress of builds, providing real-time feedback on a display and via a web interface. This system integrates an Arduino-based microcontroller, an Adafruit TFT LCD display, and a web server to communicate build statuses effectively.

Key Features
Real-time Build Monitoring: Tracks build status (Success, Failure, In Progress) and displays it on a TFT LCD.
Web Interface: A simple HTTP server is embedded, allowing users to send build status updates and view the results in JSON format.
LED Indicators: Visual feedback via LEDs indicating the current build status.
Error Handling: Clear error messages for invalid data or connection issues.
Technologies Used
Embedded System: Arduino microcontroller for the hardware setup.
Libraries:
Adafruit GFX
Adafruit TFTLCD
ArduinoJson
Thread (for periodic task execution)
Ethernet
Networking: Utilizes Ethernet to communicate over the network and provides build status updates.
C/C++: Code is written using the Arduino framework in C/C++.
Hardware Components
Microcontroller: Arduino-based board (compatible with Ethernet shield)
TFT LCD: Adafruit TFT LCD screen for status display
Ethernet Shield: To provide Ethernet connectivity
LEDs: Used for success and failure indication
Setup Instructions
Hardware Setup
Microcontroller: Connect the Arduino board to your computer.
Ethernet Shield: Attach the Ethernet shield to the Arduino to enable networking.
TFT LCD Display: Connect the Adafruit TFT LCD screen to the appropriate pins of the Arduino. Refer to the schematic for detailed connections.
LEDs: Connect the success and failure LEDs to the specified pins in the code.
Software Setup
Install Libraries: Install the required libraries in your Arduino IDE:
Adafruit GFX
Adafruit TFTLCD
ArduinoJson
Thread
Upload Code: Upload the provided code to your Arduino using the Arduino IDE.
Connect to Network: Ensure the Arduino is connected to the network via Ethernet. Update the IP address in the code if necessary.
Running the Project
Once the setup is complete, the device will start running:

The TFT LCD will display the current build status.
LEDs will show the build progress (green for success, red for failure).
The device will serve a web interface on port 80, where it will accept build status updates in JSON format.
Example JSON Request
To update the build status, send the following JSON structure via a POST request:

json
{
  "stat": "s",
  "proj": "Project Name",
  "build": "Build123",
  "usu": "User123",
  "desc": "Build completed successfully."
}
Where:

stat: One of the status codes ('s' for success, 'f' for failure, 'c' for constructing, etc.)
proj: Project name
build: Build identifier
usu: Username of the person triggering the build
desc: A description of the build or failure

Contributing
Feel free to fork this project, submit issues, or create pull requests. Any improvements or bug fixes are welcome!

License
This project is licensed under the MIT License - see the LICENSE file for details.
