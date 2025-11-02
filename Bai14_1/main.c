#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#define BIT_TASK1   (1 << 0)
#define BIT_TASK2   (1 << 1)


EventGroupHandle_t xEventGroup;


void GPIO_Config(void);
void TaskMain(void *pvParameters);
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);

int main(void)
{
    SystemInit();
    GPIO_Config();


    xEventGroup = xEventGroupCreate();


    xTaskCreate(TaskMain, "TaskMain", 128, NULL, 3, NULL);
    xTaskCreate(Task1, "Task1", 128, NULL, 2, NULL);
    xTaskCreate(Task2, "Task2", 128, NULL, 2, NULL);
    xTaskCreate(Task3, "Task3", 128, NULL, 2, NULL);

 
    vTaskStartScheduler();

    while (1);
}

void GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4;
    GPIO_Init(GPIOA, &gpio);
}

void TaskMain(void *pvParameters)
{
    while (1)
    {

        xEventGroupSetBits(xEventGroup, BIT_TASK1);
        vTaskDelay(pdMS_TO_TICKS(2000));


        xEventGroupSetBits(xEventGroup, BIT_TASK2);
        vTaskDelay(pdMS_TO_TICKS(2000));


        xEventGroupSetBits(xEventGroup, BIT_TASK1 | BIT_TASK2);
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

void Task1(void *pvParameters)
{
    while (1)
    {

        xEventGroupWaitBits(
            xEventGroup,
            BIT_TASK1,
            pdTRUE,    
            pdFALSE,   
            portMAX_DELAY
        );
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        xEventGroupWaitBits(
            xEventGroup,
            BIT_TASK2,
            pdTRUE,
            pdFALSE,
            portMAX_DELAY
        );
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
}


void Task3(void *pvParameters)
{
    while (1)
    {
        xEventGroupWaitBits(
            xEventGroup,
            BIT_TASK1 | BIT_TASK2,
            pdTRUE,
            pdTRUE,   
            portMAX_DELAY
        );
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        vTaskDelay(pdMS_TO_TICKS(1000));
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    }
}
