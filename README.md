# ESP32 – Object Classification from Camera Feed (TinyML)

## Project Overview

This project demonstrates object classification on an ESP32 using a live camera feed and an embedded machine learning model. It implements TinyML workflows for real-time inference under constrained hardware, showing how vision-based AI can be deployed on edge microcontrollers.

## Hardware Requirements

- ESP32 development board (e.g., ESP32-WROOM or ESP32-CAM)
- OV2640 camera module
- Micro-USB cable
- Jumper wires
- Breadboard (optional)

## Software Requirements

- Arduino IDE or ESP-IDF
- ESP32 board support
- TensorFlow Lite for Microcontrollers
- Python (for training + model conversion)
- `xxd` or similar to convert TFLite model into a C array

## Features

- Capture real-time camera frames
- Run inference using a quantized TFLite model
- Display classification results over serial output
- Modular design separating camera, inference, and preprocessing logic

## Getting Started

### 1. Hardware Setup

- Wire OV2640 camera to ESP32:
  - `VCC → 3.3V`
  - `GND → GND`
  - `SDA/SCL`, `PWDN`, `XCLK`, etc. → according to ESP32 pinout
- Use ESP32-CAM for plug-and-play setup

### 2. Software Setup

- Install Arduino IDE
- Add ESP32 board URL:
  `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
- Install necessary libraries (Wire, SPI, etc.)
- Clone and install TensorFlow Lite for Microcontrollers if needed

### 3. Model Training & Conversion

- Train your CNN model with TensorFlow (small MobileNet or custom CNN)
- Quantize and convert to `.tflite`
- Convert `.tflite` model to a C array:
  ```bash
  xxd -i model.tflite > model_data.h
