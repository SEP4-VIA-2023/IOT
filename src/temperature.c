#include "temperature.h"
#include <avr/delay.h>
#include <hih8120.h>

//FreeRTOS
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

// Temperature
uint16_t temperature;

// Event Group, Queue, Semaphore
SemaphoreHandle_t temperatureSemphr;
QueueHandle_t dataQueue;
EventGroupHandle_t dataEventGroup;

// Initializes the HIH8120 sensor and prints the status of the driver
void initialiseTemperature(UBaseType_t TaskPriority) {
    // Initial temperature value
    temperature = 0

    // Creates Event Group, Queue, Semaphore
    temperatureSemaphore = xSemaphoreCreateBinary();
    dataQueue = xQueueCreate(10, sizeof(uint16_t));
    dataEventGroup = xEventGroupCreate();

    // Calls the sensor's initialization function
    hih8120_driverReturnCode_t returnCode = hih8120_initialise();

    // Task handle
    TaskHandle_t temperatureTaskHandle = NULL;

    // Task creation
    xTaskCreate(temperatureTaskHandle,
                "HumiditySensorTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                TaskPriority,
                &temperatureTaskHandle);

    // Checks the initialization status
    if (returncode == HIH8120_OK)
    {
        printf("Temperature driver initialized successfully\n");
    }
    else
    {
        printf("Temperature driver unable to initialize");
    }
}

void measureTemperature() {

    // Waits for the measure event to be triggered
    xEventGroupWaitBits(dataEventGroup, BIT_MEASURE, pdTRUE, pdTRUE, portMAX_DELAY);

    hih8120_driverReturnCode_t status;

    // Wake up the sensor from standby
    status = hih8120_wakeup();

    // Checks for the status of hih8120_wakeup()
    if ( status == HIH8120_OK )
    {
        // The sensor requires at least 50ms after wakeup
        vTaskDelay(pdMS_TO_TICKS(100))

        // Performs a measurement
        status = hih8120_measure();
    }
    // Retries wakeup up to 10 times
    else
    {
        int count = 10;
        while (status == HIH8120_TWI_BUSY && count > 0)
        {
            status = hih8120_wakeup();
            vTaskDelay(pdMS_TO_TICKS(50));
            count--;
        }

        if (status == HIH8120_OK)
        {
            status = hih8120_measure();
        }
        
    }

    // After measure function is called, dealy of at least 1ms is required
    vTaskDelay(pdMS_TO_TICKS(20));
    
    // Checks if the measurement is ready
    if ( hih8120_isReady() )
    {
        temperature = hih8120_getTemperature_x10();
        xEventGroupSetBits(dataEventGroup, BIT_TEMPERATURE);
    }
    else
    {
        int count = 10;

        while (!hih8120_isReady() && count > 0)
        {
            vTaskDelay(pdMS_TO_TICKS(20));
            count--;
        }

        temperature = hih8120_getTemperature_x10();
        xEventGroupSetBits(dataEventGroup, BIT_TEMPERATURE);
    }
}

// Continuously calls measureTemperature()
void temperatureSensorTask(void *pvParameters)
{
    for (;;)
    {
        if (xSemaphoreTake(temperatureSemaphore, portMAX_DELAY) == pdTRUE)
        {
            measureTemperature();
            printf("Temperature: %d\n", temperature);
            xQueueSend(dataQueue, &temperature, portMAX_DELAY);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}