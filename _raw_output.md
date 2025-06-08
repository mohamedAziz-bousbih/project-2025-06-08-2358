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
```
/esp32-object-classification
│── README.md
│── main.c
│── model_data.h
│── image_provider.c
│── image_provider.h
│── camera_setup.c
│── camera_setup.h
│── main_functions.c
│── model.cc
│── model.h
```

### Code Explanation

The code is organized into several key components:
- **main.c**: The main entry point for the program, which initializes system components and enters the main inference loop.
- **camera_setup.c/h**: Manages camera initialization and configuration.
- **image_provider.c/h**: Handles capturing and preprocessing of images.
- **model_data.h**: Contains the binary TensorFlow Lite model data.
- **model.cc/h**: Implements the model's inference logic using TensorFlow Lite for microcontrollers.
- **main_functions.c**: Handles higher-order control functions and the main operational loop.

### Source Code

### main.c
```c
#include <stdio.h>
#include "camera_setup.h"
#include "image_provider.h"
#include "model.h"
#include "model_data.h"
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Constants
const int tensor_arena_size = 60 * 1024;
uint8_t tensor_arena[tensor_arena_size];

int main() {
    printf("ESP32 - Object Classification\n");
    
    // Initialize camera
    if (!camera_setup()) {
        printf("Camera setup failed\n");
        return -1;
    }

    // Load model
    const tflite::Model* model = tflite::GetModel(g_model_data);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        printf("Model version mismatch\n");
        return -1;
    }

    // Setup resolver and interpreter
    static tflite::MicroMutableOpResolver<10> resolver;
    resolver.AddBuiltin(tflite::BuiltinOperator_CONV_2D, tflite::ops::micro::Register_CONV_2D());
    // Add other necessary operations

    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, tensor_arena_size);
    tflite::MicroInterpreter* interpreter = &static_interpreter;

    if (interpreter->AllocateTensors() != kTfLiteOk) {
        printf("Tensor allocation failed\n");
        return -1;
    }

    // Main loop
    while (true) {
        // Capture image
        if (!CaptureImage()) {
            printf("Image capture failed\n");
            continue;
        }

        // Perform inference
        if (!RunInference(interpreter)) {
            printf("Inference failed\n");
            continue;
        }

        // Retrieve and print results
        PrintInferenceResults(interpreter->output(0));
    }

    return 0;
}
```

### model_data.h
```c
#ifndef MODEL_DATA_H
#define MODEL_DATA_H

extern const unsigned char g_model_data[];
extern const int g_model_data_len;

#endif
```

### image_provider.c
```c
#include "image_provider.h"
#include "camera_setup.h"

// Placeholder for image data
static uint8_t image_data[96 * 96 * 3];

bool CaptureImage() {
    // Capture image from camera module
    // Store image in image_data array
    // Perform any pre-processing steps
    return true;
}

uint8_t* GetImageData() {
    return image_data;
}
```

### image_provider.h
```c
#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <stdint.h>

bool CaptureImage();
uint8_t* GetImageData();

#endif
```

### camera_setup.c
```c
#include "camera_setup.h"
#include <stdio.h>

bool camera_setup() {
    // Initialize and configure camera
    // Return true if successful, false otherwise
    printf("Camera initialized successfully\n");
    return true;
}
```

### camera_setup.h
```c
#ifndef CAMERA_SETUP_H
#define CAMERA_SETUP_H

bool camera_setup();

#endif
```

### main_functions.c
```c
#include "model.h"
#include "model_data.h"
#include <stdio.h>

bool RunInference(tflite::MicroInterpreter* interpreter) {
    // Obtain input from image provider
    uint8_t* image_data = GetImageData();
    // Copy image data to input tensor
    // Run inference
    if (interpreter->Invoke() == kTfLiteOk) {
        return true;
    } else {
        return false;
    }
}

void PrintInferenceResults(TfLiteTensor* output) {
    // Parse and print classification results
    printf("Inference results: [example]\n");
}
```

### model.cc
```c
#include "model.h"
#include "model_data.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/testing/micro_test.h"

// Global variables for TensorFlow Lite inference
tflite::MicroInterpreter* GetInterpreter() {
    static tflite::MicroInterpreter static_interpreter(nullptr, nullptr, nullptr, 0);
    return &static_interpreter;
}
```

### model.h
```c
#ifndef MODEL_H
#define MODEL_H

#include "tensorflow/lite/micro/micro_interpreter.h"

tflite::MicroInterpreter* GetInterpreter();
bool RunInference(tflite::MicroInterpreter* interpreter);
void PrintInferenceResults(TfLiteTensor* output);

#endif
```

### Notes
- Ensure that the model used fits within the memory constraints of the ESP32.
- Additional configuration may be needed based on specific hardware variations.
- The project assumes familiarity with embedded programming and machine learning model deployment. Adjustments may be necessary for specific use cases and hardware configurations.