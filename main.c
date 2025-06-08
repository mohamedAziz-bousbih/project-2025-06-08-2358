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
