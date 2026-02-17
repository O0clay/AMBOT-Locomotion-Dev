#include "pid.h"

void PID_Init(PID_t *pid,
              float kp,
              float ki,
              float kd,
              float outMin,
              float outMax)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;

    pid->integrator = 0.0f;
    pid->prevError = 0.0f;

    pid->outMin = outMin;
    pid->outMax = outMax;
}

float PID_Compute(PID_t *pid,
                  float setpoint,
                  float measurement,
                  float dt)
{
    float error = setpoint - measurement;

    float proportional = pid->Kp * error;

    float newIntegrator = pid->integrator + error * dt;
    float integral = pid->Ki * newIntegrator;

    float derivative = pid->Kd * (error - pid->prevError) / dt;

    float output = proportional + integral + derivative;

    // Anti-windup clamp
    if (output > pid->outMax)
    {
        output = pid->outMax;
    }
    else if (output < pid->outMin)
    {
        output = pid->outMin;
    }
    else
    {
        pid->integrator = newIntegrator;
    }

    pid->prevError = error;

    return output;
}

void PID_Reset(PID_t *pid)
{
    pid->integrator = 0.0f;
    pid->prevError = 0.0f;
}
