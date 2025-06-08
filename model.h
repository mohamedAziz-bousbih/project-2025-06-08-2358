#ifndef MODEL_H
#define MODEL_H

#include "tensorflow/lite/micro/micro_interpreter.h"

tflite::MicroInterpreter* GetInterpreter();
bool RunInference(tflite::MicroInterpreter* interpreter);
void PrintInferenceResults(TfLiteTensor* output);

#endif
