#ifndef MOTOR_H
#define MOTOR_H

#include "stm32g4xx_hal.h"
#include <stdint.h>

#define PWM_MAX 8499  // ARR value — adjust if you change timer config

// Call once in main after HAL init
void Motor_Init(void);

// dir: 1 = forward, 0 = backward | speed: 0–100%
void Motor1_Set(uint8_t dir, uint8_t speed);
void Motor2_Set(uint8_t dir, uint8_t speed);
void Motor_StopAll(void);

#endif
