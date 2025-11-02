#include "stm32f10x.h"

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 8000; i++) {
        __NOP();
    }
}

void GPIO_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio);
}

int main(void) {
    GPIO_Config();

    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        delay_ms(500);
    }
}
