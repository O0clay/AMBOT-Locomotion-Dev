#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

void RobotControl_Init(void);
void RobotControl_Update(float dt);

void RobotControl_SetTarget(int16_t left, int16_t right);

#endif
