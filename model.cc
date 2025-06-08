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
