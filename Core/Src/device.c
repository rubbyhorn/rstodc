
#include "main.h"
#include "device.h"
#include <stdint.h>
#include <stdlib.h>

#define DEVICE_MAX 352
#define PWM_NEUTRAL 480
#define DEVICE_MIN 608

extern TIM_HandleTypeDef htim3;

void UpdateDeviceSettings(device_settings *device_struct)
{
    if (device_struct->velocity > 0) {
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, device_struct->velocity);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

    } else if (device_struct->velocity < 0) {
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, -1 * device_struct->velocity);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    } else {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
    }
}

