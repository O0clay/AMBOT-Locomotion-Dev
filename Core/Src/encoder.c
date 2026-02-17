#include "encoder.h"

void Encoder_Init(Encoder_t *enc, TIM_HandleTypeDef *htim)
{
    enc->htim = htim;
    enc->position = 0;
    enc->velocity = 0;
    enc->last_count = __HAL_TIM_GET_COUNTER(htim);
}

void Encoder_Update(Encoder_t *enc)
{
    int32_t current = __HAL_TIM_GET_COUNTER(enc->htim);

    int32_t delta = current - enc->last_count;

    // Handle 16-bit timer overflow
    if (delta > 32767)
        delta -= 65536;
    else if (delta < -32768)
        delta += 65536;

    enc->velocity = delta;
    enc->position += delta;

    enc->last_count = current;
}
