#ifndef ENCODER_H
#define ENCODER_H

#include "stm32g4xx_hal.h"
#include <stdint.h>

typedef struct
{
    TIM_HandleTypeDef *htim;

    int32_t position;
    int32_t velocity;

    int32_t last_count;

} Encoder_t;

void Encoder_Init(Encoder_t *enc, TIM_HandleTypeDef *htim);
void Encoder_Update(Encoder_t *enc);

#endif
