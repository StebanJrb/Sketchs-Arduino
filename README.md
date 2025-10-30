 🌡️ Arduino Web Server with DHT22, PIR Sensor, and Raspberry Pi Communication

## 📘 Project Description
This project implements an **Arduino-based web server** that monitors **temperature**, **humidity**, **motion detection**, and **voltage levels**, displaying the results both on a **web page** and a **16x2 LCD display**.  
Additionally, it sends the collected sensor data to a **Raspberry Pi** over Ethernet for further processing or storage.

The system combines **sensor monitoring**, **Ethernet communication**, and **data visualization** to demonstrate the integration of hardware and networked IoT systems.

## ⚙️ Features
- 🌡️ Temperature and Humidity Monitoring using a DHT22 sensor.  
- 🕵️ Motion Detection through a PIR sensor.  
- ⚡ Analog Voltage Measurement using the Arduino’s ADC input.  
- 🌐 Web Interface served from the Arduino via Ethernet.  
- 🤝 Data Transmission to a Raspberry Pi through a socket connection.  
- 🖥️ Real-Time Display on a 16x2 LCD module.  

## 🧰 Components Used
- Arduino UNO / MEGA  
- DHT22 (AM2302) Sensor  
- PIR Motion Sensor  
- Ethernet Shield (W5100 / W5500)  
- 16x2 LCD Display  
- Raspberry Pi (as receiving server)  
- Jumper wires and breadboard

## 🔌 Pin Configuration
Component | Pin | Description
-----------|-----|-------------
DHT22 | 2 | Data pin
PIR Sensor | 2 | Digital input
LCD RS | 12 | LCD control
LCD EN | 11 | LCD enable
LCD D4 | 5 | Data
LCD D5 | 4 | Data
LCD D6 | 3 | Data
LCD D7 | 2 | Data
Analog Sensor | A0 | Voltage reading

## 🚀 How It Works
1. The Arduino reads temperature, humidity, PIR state, and voltage values.  
2. These readings are displayed on a web page hosted by the Arduino.  
3. The same data is sent to a Raspberry Pi via Ethernet using TCP sockets.  
4. The LCD display shows the voltage readings in real time.  

## 🖥️ Web Server
The Arduino hosts a small web page on port 125 showing:
- Temperature (°C)  
- Humidity (%)  
- Motion detection (0/1)  
- Voltage (V)  

The page refreshes automatically every second.

## 🧩 Communication with Raspberry Pi
The Arduino sends the following data string to the Raspberry Pi:
temperature,humidity,motion,voltage

Example:
24.5,60.2,1,3.4

The Raspberry Pi must be configured to listen on IP 192.168.10.2 and port 65432.

## 🪛 Setup Instructions
1. Connect all components according to the pin configuration.  
2. Update the IP addresses in the Arduino code to match your network.  
3. Upload the sketch to your Arduino.  
4. Run a TCP server on your Raspberry Pi to receive the data.  
5. Open a browser and navigate to your Arduino’s IP (e.g., 192.168.10.1:125) to view the live readings.  

## 🧠 Notes
- Ensure your Ethernet Shield is properly configured and connected.  
- The port 125 must be open if you want to access the page from outside your LAN.  
- If the DHT22 readings return NaN, check wiring and sensor power.  
- The serial monitor can be used for debugging communication with the Raspberry Pi.

## 📜 License
This project is for educational and experimental use.  
Feel free to modify and adapt it for your own IoT or embedded systems projects.
