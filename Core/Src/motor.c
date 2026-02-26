#include "motor.h"
#include "main.h"  // gives access to htim1, GPIO defines

extern TIM_HandleTypeDef htim1;

// Adjust these GPIO port/pin defines to match your CubeMX config
#define MOTOR1_DIR_PORT   GPIOA
#define MOTOR1_DIR_PIN    GPIO_PIN_9
#define MOTOR2_DIR_PORT   GPIOB
#define MOTOR2_DIR_PIN    GPIO_PIN_0

void Motor_Init(void) {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    Motor_StopAll();
}

void Motor1_Set(uint8_t dir, uint8_t speed) {
    HAL_GPIO_WritePin(MOTOR1_DIR_PORT, MOTOR1_DIR_PIN,
                      dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
    uint32_t pulse = ((uint32_t)speed * PWM_MAX) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
}

void Motor2_Set(uint8_t dir, uint8_t speed) {
    HAL_GPIO_WritePin(MOTOR2_DIR_PORT, MOTOR2_DIR_PIN,
                      dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
    uint32_t pulse = ((uint32_t)speed * PWM_MAX) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse);
}

void Motor_StopAll(void) {
    Motor1_Set(0, 0);
    Motor2_Set(0, 0);
}
