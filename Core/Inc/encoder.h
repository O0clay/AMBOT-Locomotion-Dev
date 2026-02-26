#ifndef ENCODER_H
#define ENCODER_H

#include "stm32g4xx_hal.h"
#include <stdint.h>

// Pulses per revolution of your encoder — check your motor's datasheet
#define ENCODER_PPR 1024

void Encoder_Init(void);

// Raw counter values (resets on overflow — handle with delta reading)
int32_t Encoder1_GetCount(void);
int32_t Encoder2_GetCount(void);

// Call this at a fixed interval (e.g. every 10ms) to get velocity in RPM
float Encoder1_GetRPM(void);
float Encoder2_GetRPM(void);

#endif
