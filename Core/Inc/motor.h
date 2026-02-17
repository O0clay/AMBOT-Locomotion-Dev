#ifndef MOTOR_H
#define MOTOR_H

#include "stm32g4xx_hal.h"
#include <stdint.h>

typedef struct
{
    TIM_HandleTypeDef *htim_pwm;
    uint32_t channel;

    GPIO_TypeDef *dir_port;
    uint16_t dir_pin;

    int16_t max_pwm;

} Motor_t;

void Motor_Init(Motor_t *motor,
                TIM_HandleTypeDef *htim,
                uint32_t channel,
                GPIO_TypeDef *dir_port,
                uint16_t dir_pin,
                int16_t max_pwm);

void Motor_SetSpeed(Motor_t *motor, int16_t speed);

#endif
