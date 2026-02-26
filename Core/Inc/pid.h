#ifndef PID_H
#define PID_H

typedef struct {
    float kp;
    float ki;
    float kd;

    float setpoint;
    float integral;
    float prev_error;

    float output_min;
    float output_max;
} PID_t;

void PID_Init(PID_t *pid, float kp, float ki, float kd,
              float out_min, float out_max);
void PID_SetTarget(PID_t *pid, float setpoint);
float PID_Update(PID_t *pid, float measured, float dt);
void PID_Reset(PID_t *pid);

#endif
