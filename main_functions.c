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
