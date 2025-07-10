# Smart-Remote
Smart IR-Controlled Atomberg Fan with Alexa Integration via Sinric Pro

This project allows you to control your IR-based Atomberg fan using voice commands through Alexa or the Sinric Pro mobile app. The control is achieved using an ESP8266 NodeMCU, IR LED transmitter, and a few supporting components.

🚀 Features

Control Atomberg fan with Alexa voice commands

IR signal transmission using ESP8266 NodeMCU

Uses Sinric Pro cloud service for device integration

Supports 3 fan speeds: Low, Medium, High

Works with standard 5V USB power supply

🧰 Components Required

Component

Quantity

NodeMCU ESP8266 (LOLIN) 1

IR LED 1

2N2222 NPN Transistor 1

220 ohm resistor 1

Jumper wires As needed

Breadboard 1

USB power supply (5V/2A) 1

⚙️ Pin Configuration
Function     |   NodeMCU Pin
IR Transmit  |   D1 (GPIO5)
GND          |   G
VCC (3.3V)   |   3V

 
 ===================Wiring=============== 

IR LED anode → Collector of 2N2222

2N2222 base → 220Ω resistor → D1 (GPIO5)

2N2222 emitter → GND

IR LED cathode → GND

🛠️ Setup Instructions

Clone the repository:

git clone https://github.com/your-username/atomberg-alexa-ir.git
cd atomberg-alexa-ir

Open the .ino file in Arduino IDE

Install the required libraries:

IRremoteESP8266

SinricPro

Update the WiFi and Sinric Pro credentials in the code:

#define WIFI_SSID     "your_wifi"
#define WIFI_PASS     "your_password"
#define APP_KEY       "your_app_key"
#define APP_SECRET    "your_app_secret"
#define DEVICE_ID     "your_device_id"

Upload the code to your NodeMCU

Pair Sinric Pro skill with your Alexa app

Ask Alexa:

"Alexa, turn on the fan"

"Alexa, set fan speed to 1"

📱 Supported Alexa Commands

"Alexa, turn on/off the fan"

"Alexa, set the fan to speed 1" (Low)

"Alexa, set the fan to speed 2" (Medium)

"Alexa, set the fan to speed 3" (High)
