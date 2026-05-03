# Smoke Detector Using Arduino

> B.Tech Undergraduate Project — Embedded Systems / Safety Prototyping

## Project Overview
A low‑cost smoke detection prototype built with an Arduino Uno and an MQ‑2 gas/smoke sensor, housed in a small enclosure. When smoke concentration crosses a configurable threshold, the system triggers a buzzer and red LED alarm. A Python monitoring script reads sensor values over serial, logs them to CSV, and can raise desktop notifications.

## Objectives
- Design a basic smoke detection system using an MQ‑2 sensor and Arduino.
- Implement threshold‑based alarm logic with audio and visual feedback.
- Enclose the circuit in a compact box for a realistic prototype.
- Build a Python tool for live monitoring and data logging.

## Hardware Components
- Arduino Uno
- MQ‑2 gas / smoke sensor
- Buzzer
- Red LED (alarm indicator)
- Green LED (safe indicator)
- Resistors and jumper wires
- Enclosure box
- USB or 9V power supply

## Wiring (Summary)
- MQ‑2 analog output → Arduino A0  
- MQ‑2 digital output (optional) → Arduino D7  
- Buzzer → Arduino D8  
- Red LED → Arduino D9 (with series resistor)  
- Green LED → Arduino D10 (with series resistor)  

## How It Works
The MQ‑2 sensor’s resistance changes with smoke or gas concentration, producing a varying analog voltage. The Arduino reads this value on A0 and compares it against a threshold (for example 400 on a 0–1023 scale).  

- If the reading is below the threshold: the system is in **safe** state, green LED on, buzzer off.  
- If the reading exceeds the threshold: the system enters **alarm** state, red LED on and the buzzer beeps in a repeating pattern.  

The firmware also prints the smoke level and status to the serial port for monitoring on a PC.

## Repository Structure (suggested)
- `smoke_detector.ino` – Arduino firmware  
- `smoke_monitor.py` – Python serial monitor + optional desktop notifications  
- `log_analyser.py` – Python script to analyse logged sensor data  
- `README.md` – this documentation  

## Running the Project
1. Upload `smoke_detector.ino` to the Arduino Uno.
2. Power the circuit and allow around 20 seconds for the MQ‑2 sensor to warm up.
3. Run `smoke_monitor.py` on a connected PC to see readings and log them.
4. Expose the sensor briefly to smoke to test alarm behaviour.
5. Use `log_analyser.py` to review min, max, and average readings and how often the system was in alert state.

## Calibration and Safety Notes
- Adjust the threshold in code based on your environment and typical background readings.
- The enclosure should have a small ventilation opening near the sensor.
- This is an educational prototype only and must not be used as a replacement for certified smoke alarms.

## Skills Demonstrated
- Analog sensor interfacing and calibration
- Threshold‑based embedded control
- Serial communication and logging with Python
- Basic safety‑system prototyping and enclosure design
