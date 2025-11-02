#include "stm32f10x.h"
#include <string.h>

void UART1_Init(void);
void UART1_SendString(char *str);
void Enter_Standby_Mode(void);
void RTC_Config(void);

int main(void) {
    // Bật HSE, cấu hình hệ thống
    SystemInit();
    UART1_Init();
    RTC_Config();

    // Gửi dữ liệu UART
    UART1_SendString("Wake up and send data...\r\n");

    // Delay nhỏ cho UART gửi xong
    for (volatile int i = 0; i < 800000; i++);

    // Vào chế độ Standby
    Enter_Standby_Mode();

    while (1);
}

void UART1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    // TX (PA9)
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    // RX (PA10)
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    USART_InitTypeDef uart;
    uart.USART_BaudRate = 9600;
    uart.USART_WordLength = USART_WordLength_8b;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &uart);
    USART_Cmd(USART1, ENABLE);
}

void UART1_SendString(char *str) {
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void RTC_Config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    RTC_SetPrescaler(32767);  // 1Hz
    RTC_WaitForLastTask();
    RTC_SetAlarm(RTC_GetCounter() + 5); // Báo thức sau 5 giây
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
}

void Enter_Standby_Mode(void) {
    PWR_ClearFlag(PWR_FLAG_WU);     // Xóa cờ Wake-up
    PWR_EnterSTANDBYMode();         // Vào chế độ Standby
}
