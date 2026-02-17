#include "robot_control.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "main.h"

extern TIM_HandleTypeDef htim1; // PWM
extern TIM_HandleTypeDef htim2; // Left encoder
extern TIM_HandleTypeDef htim3; // Right encoder

static Motor_t leftMotor;
static Motor_t rightMotor;

static Encoder_t leftEnc;
static Encoder_t rightEnc;

static PID_t leftPID;
static PID_t rightPID;

static int16_t targetLeft = 0;
static int16_t targetRight = 0;

void RobotControl_Init(void)
{
    Motor_Init(&leftMotor, &htim1, TIM_CHANNEL_1, GPIOA, GPIO_PIN_0, 3599);
    Motor_Init(&rightMotor, &htim1, TIM_CHANNEL_2, GPIOA, GPIO_PIN_1, 3599);

    Encoder_Init(&leftEnc, &htim2);
    Encoder_Init(&rightEnc, &htim3);

    PID_Init(&leftPID, 1.0f, 0.5f, 0.01f, -3599, 3599);
    PID_Init(&rightPID, 1.0f, 0.5f, 0.01f, -3599, 3599);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

void RobotControl_SetTarget(int16_t left, int16_t right)
{
    targetLeft = left;
    targetRight = right;
}

void RobotControl_Update(float dt)
{
    Encoder_Update(&leftEnc);
    Encoder_Update(&rightEnc);

    float leftOutput = PID_Compute(&leftPID,
                                   targetLeft,
                                   leftEnc.velocity,
                                   dt);

    float rightOutput = PID_Compute(&rightPID,
                                    targetRight,
                                    rightEnc.velocity,
                                    dt);

    Motor_SetSpeed(&leftMotor, (int16_t)leftOutput);
    Motor_SetSpeed(&rightMotor, (int16_t)rightOutput);
}
