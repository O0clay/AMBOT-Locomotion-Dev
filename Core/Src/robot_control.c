#include "robot_control.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"

// dt in seconds matching your SAMPLE_INTERVAL_MS
#define DT 0.01f

static PID_t pid_motor1;
static PID_t pid_motor2;
static RobotCommand_t current_cmd = CMD_STOP;
static uint8_t current_speed = 0;

void Robot_Init(void) {
    Motor_Init();
    Encoder_Init();

    // Tune these KP/KI/KD values experimentally — start with just Kp
    PID_Init(&pid_motor1, 1.0f, 0.1f, 0.01f, 0.0f, 100.0f);
    PID_Init(&pid_motor2, 1.0f, 0.1f, 0.01f, 0.0f, 100.0f);
}

void Robot_SetCommand(RobotCommand_t cmd, uint8_t speed_percent) {
    current_cmd = cmd;
    current_speed = speed_percent;

    float target = (float)speed_percent;  // target in % — maps to RPM once tuned

    switch (cmd) {
        case CMD_FORWARD:
            PID_SetTarget(&pid_motor1, target);
            PID_SetTarget(&pid_motor2, target);
            break;
        case CMD_BACKWARD:
            PID_SetTarget(&pid_motor1, -target);
            PID_SetTarget(&pid_motor2, -target);
            break;
        case CMD_TURN_LEFT:
            PID_SetTarget(&pid_motor1, -target);
            PID_SetTarget(&pid_motor2,  target);
            break;
        case CMD_TURN_RIGHT:
            PID_SetTarget(&pid_motor1,  target);
            PID_SetTarget(&pid_motor2, -target);
            break;
        case CMD_STOP:
        default:
            PID_SetTarget(&pid_motor1, 0.0f);
            PID_SetTarget(&pid_motor2, 0.0f);
            PID_Reset(&pid_motor1);
            PID_Reset(&pid_motor2);
            Motor_StopAll();
            break;
    }
}

void Robot_Update(void) {
    if (current_cmd == CMD_STOP) return;

    float rpm1 = Encoder1_GetRPM();
    float rpm2 = Encoder2_GetRPM();

    float out1 = PID_Update(&pid_motor1, rpm1, DT);
    float out2 = PID_Update(&pid_motor2, rpm2, DT);

    // out is signed: positive = forward, negative = backward
    uint8_t dir1 = (out1 >= 0) ? 1 : 0;
    uint8_t dir2 = (out2 >= 0) ? 1 : 0;
    uint8_t spd1 = (uint8_t)(out1 < 0 ? -out1 : out1);
    uint8_t spd2 = (uint8_t)(out2 < 0 ? -out2 : out2);

    Motor1_Set(dir1, spd1);
    Motor2_Set(dir2, spd2);
}
