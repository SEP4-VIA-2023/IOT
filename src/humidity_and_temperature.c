#include "humidity_and_temperature.h"
#include <hih8120.h>

/**
 * FreeRTOS includes
 */
#include <task.h>
#include <semphr.h>

/**
 * Declaring values
 * HUM = Humidity
 * TEM = Temperature
 */
uint16_t HUM;
int16_t TEM;

void TEMHUMReadingLoop(void *pvParameters);

void initialiseTEMHUM(UBaseType_t TEMHUMPriority){
    hih8120_initialise();
    hih8120_wakeup();
    
    /**
     * Initialize variables
     */
    HUM = 0;
    TEM = 0;

	/**
	 * TEM and HUM values from the reading loop
	 */
	xTaskCreate(
	TEMHUMReadingLoop
	, "TEMHUMReadingLoop"
	, configMINIMAL_STACK_SIZE
	, NULL
	, TEMHUMPriority
	, NULL
	);

}

void TEMHUMMeasure()
{
    hih8120_wakeup();
    vTaskDelay(pdMS_TO_TICKS(50)); // time to wake up
    hih8120_measure();
}

/**
 * Reads temperature and humidity data continuously
 * @param pvParameters
 */
void TEMHUMReadingLoop(void *pvParameters)
{
    TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; // 1000 ms
	/**
	 * Initialise the xLastWakeTime variable with the current time.
	 */
	xLastWakeTime = xTaskGetTickCount();

    for(;;){
    xTaskDelayUntil( &xLastWakeTime, xFrequency );
    TEMHUMMeasure();
    TEM =hih8120_getTemperature_x10();
    HUM = hih8120_getHumidityPercent_x10();
    }   
}

uint16_t ReadHumidity()
{
    return HUM;
}
int16_t ReadTemperature()
{
    return TEM;
}
