#include "pid.h"

void PID_Init(PID_t *pid, float kp, float ki, float kd,
              float out_min, float out_max) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->output_min = out_min;
    pid->output_max = out_max;
    PID_Reset(pid);
}

void PID_SetTarget(PID_t *pid, float setpoint) {
    pid->setpoint = setpoint;
}

float PID_Update(PID_t *pid, float measured, float dt) {
    float error = pid->setpoint - measured;

    pid->integral += error * dt;

    // Anti-windup: clamp integral contribution
    float integral_clamp = pid->output_max / (pid->ki > 0 ? pid->ki : 1.0f);
    if (pid->integral >  integral_clamp) pid->integral =  integral_clamp;
    if (pid->integral < -integral_clamp) pid->integral = -integral_clamp;

    float derivative = (error - pid->prev_error) / dt;
    pid->prev_error = error;

    float output = (pid->kp * error)
                 + (pid->ki * pid->integral)
                 + (pid->kd * derivative);

    // Clamp output
    if (output >  pid->output_max) output =  pid->output_max;
    if (output < -pid->output_min) output = -pid->output_min;  // note: min is positive, represents magnitude

    return output;
}

void PID_Reset(PID_t *pid) {
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    pid->setpoint = 0.0f;
}
