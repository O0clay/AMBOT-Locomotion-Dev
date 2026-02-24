#include <stdint.h>
#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H


void RobotControl_Init(void);
void RobotControl_Update(float dt);

void RobotControl_SetTarget(uint16_t left, uint16_t right);

#endif
