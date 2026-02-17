#include "motor.h"

void Motor_Init(Motor_t *motor,
                TIM_HandleTypeDef *htim,
                uint32_t channel,
                GPIO_TypeDef *dir_port,
                uint16_t dir_pin,
                int16_t max_pwm)
{
    motor->htim_pwm = htim;
    motor->channel = channel;
    motor->dir_port = dir_port;
    motor->dir_pin = dir_pin;
    motor->max_pwm = max_pwm;
}

void Motor_SetSpeed(Motor_t *motor, int16_t speed)
{
    if (speed >= 0)
    {
        HAL_GPIO_WritePin(motor->dir_port, motor->dir_pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(motor->dir_port, motor->dir_pin, GPIO_PIN_RESET);
        speed = -speed;
    }

    if (speed > motor->max_pwm)
        speed = motor->max_pwm;

    __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel, speed);
}
