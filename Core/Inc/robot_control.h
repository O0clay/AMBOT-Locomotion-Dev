#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

#include "pid.h"
#include <stdint.h>

typedef enum {
    CMD_STOP = 0,
    CMD_FORWARD,
    CMD_BACKWARD,
    CMD_TURN_LEFT,
    CMD_TURN_RIGHT,
} RobotCommand_t;

void Robot_Init(void);
void Robot_SetCommand(RobotCommand_t cmd, uint8_t speed_percent);
void Robot_Update(void);  // Call every 10ms from your timer or main loop

#endif
