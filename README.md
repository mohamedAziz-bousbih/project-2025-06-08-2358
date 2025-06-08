# README.md

## ESP32 – Object Classification from Camera Feed (TinyML)

### Project Overview

This project demonstrates how to implement object classification on an ESP32 microcontroller using a camera feed. It leverages TinyML concepts to deploy a machine learning model capable of classifying objects captured in real-time by the camera connected to the ESP32. The project shows how embedded systems can be enhanced with AI capabilities to perform complex tasks within resource-constrained environments.

### Components Required
- ESP32 development board
- OV2640 Camera Module (or compatible)
- USB Cable for programming and power
- Jumper wires
- Breadboard (optional)

### Software Requirements
- Arduino IDE or ESP-IDF
- TensorFlow Lite for Microcontrollers
- ESP32 Board Manager
- Python (for model training and conversion)

### Features
- Capture live images from the camera.
- Classify objects using a pre-trained machine learning model.
- Output classification results via serial monitor or connected display.

### Getting Started

1. **Hardware Setup:**
   - Connect the OV2640 camera module to the ESP32 using jumper wires.
   - Ensure proper VCC, GND, SCL, SDA, and other necessary connections are made as per the camera and ESP32 pinout requirements.

2. **Software Setup:**
   - Install Arduino IDE and add the ESP32 board through the board manager.
   - Install the necessary libraries including ESP32 board support, and TensorFlow Lite for Microcontrollers.
   - Prepare the dataset and train a small object classification model using TensorFlow, then convert it to TensorFlow Lite format optimized for microcontrollers.

3. **Model Deployment:**
   - Load the model onto the ESP32 by integrating it into the codebase and flashing the program.
   - Use the serial monitor to view the classification output.

4. **Run the Program:**
   - Power the ESP32 using a USB cable.
   - Open the serial monitor to see real-time object classification results.

### Directory Structure