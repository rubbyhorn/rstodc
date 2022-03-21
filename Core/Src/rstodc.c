#include <stdint.h>
#include "rstodc.h"
#include "stm32f1xx_hal.h"
#include <string.h>
#include "messages.h"
#include <stdbool.h>
#include "communication.h"

static uint8_t RxBuff[MAX_BUFFER_LENGTH]; // received frame
static uint8_t buff; // last received byte
static size_t RxCounter = 0; //number of already received bytes
static uint32_t prevTick =  0; //tick of last Rx callback
static uint8_t frameSize = MAX_BUFFER_LENGTH;
static bool frameReady, frameError = false;

device_settings deviceSettings;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;

void processFrame();
void newFrame();

void rstodc_init(){
  deviceSettings.velocity = 0;
  deviceSettings.device_adress = 0x01;
  UpdateDeviceSettings(&deviceSettings);
  newFrame();
}

void rstodc_loop(){
    if (frameReady) {
        processFrame();
    }
    if (frameError) {
        newFrame();
    }
    __disable_irq();
    if (HAL_GetTick() - prevTick  >=  RECEIVE_TIMEOUT)  {
        HAL_UART_AbortReceive(&huart1);
//        const char *message = "\nUART timeout error.\n";
//        HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message),1000);
        prevTick = HAL_GetTick();
        newFrame();
    }
    __enable_irq();
}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart){
    if (huart == &huart1) {
        prevTick = HAL_GetTick();
        RxBuff[RxCounter] = buff;
        RxCounter++;
        if (RxCounter == 1 && buff != MAGIC){
            frameError = true;
            return;
        }
        else if (RxCounter == 2){
            switch (buff) {
                case MAGIC:
                    frameSize = VELOCITY_REQUEST_LENGTH;
                    break;
                default:
                    frameError = true;
                    return;
            }
            HAL_UART_Receive_IT(&huart1, &buff, 1); // continue receiving
        }
        else if (RxCounter == frameSize) {
            frameReady = true;
        }
        else {
            HAL_UART_Receive_IT(&huart1, &buff, 1); // continue receiving
        }

    }
}

void newFrame(){
    RxCounter = 0;
    frameSize = MAX_BUFFER_LENGTH;
    frameReady = frameError = false;
    HAL_UART_Receive_IT(&huart1, &buff, 1);
}

void processFrame(){
    switch (RxBuff[1]) {
        case MAGIC:
            if(parse_velocity_package(&deviceSettings, RxBuff));
            break;
    }
    newFrame();
}