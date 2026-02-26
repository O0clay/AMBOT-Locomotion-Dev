#include "encoder.h"
#include "main.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// Milliseconds between velocity samples — must match how often you call GetRPM
#define SAMPLE_INTERVAL_MS 10

static int32_t last_count1 = 0;
static int32_t last_count2 = 0;

void Encoder_Init(void) {
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

int32_t Encoder1_GetCount(void) {
    return (int32_t)(int16_t)__HAL_TIM_GET_COUNTER(&htim2);
}

int32_t Encoder2_GetCount(void) {
    return (int32_t)(int16_t)__HAL_TIM_GET_COUNTER(&htim3);
}

// Call this every SAMPLE_INTERVAL_MS milliseconds — e.g. from a 10ms timer ISR
float Encoder1_GetRPM(void) {
    int32_t current = Encoder1_GetCount();
    int32_t delta = current - last_count1;
    last_count1 = current;

    // delta pulses / PPR / time(min) = RPM
    // time in minutes = SAMPLE_INTERVAL_MS / 60000
    float rpm = ((float)delta / ENCODER_PPR) * (60000.0f / SAMPLE_INTERVAL_MS);
    return rpm;
}

float Encoder2_GetRPM(void) {
    int32_t current = Encoder2_GetCount();
    int32_t delta = current - last_count2;
    last_count2 = current;

    float rpm = ((float)delta / ENCODER_PPR) * (60000.0f / SAMPLE_INTERVAL_MS);
    return rpm;
}
