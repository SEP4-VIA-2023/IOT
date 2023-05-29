#include "co2.h"
#include <mh_z19.h>

/**
 * FreeRTOS includes
 */
#include <task.h>
#include <semphr.h>

/**
 * Declaring values
 */
uint16_t CO2;
void CO2ReadingCallBack(uint16_t ppm);
void CO2ReadingLoop();

void initialiseCO2(UBaseType_t CO2Priority) {
    /**
     * The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
     */
    mh_z19_initialise(ser_USART3);
    mh_z19_injectCallBack(CO2ReadingCallBack); // Injecting the callback for continuous updates
    CO2 = 0; // setting initial value


    /**
     * CO2 value reading loop
     */
    xTaskCreate(
	CO2ReadingLoop
	,  "CO2ReadingLoop"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  CO2Priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/**
 * Continuously reads the CO2 value
 * @param pvParameters
 */
void CO2ReadingLoop(void *pvParameters) {
    TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; // 1000 ms
	/**
	 * Initialise the xLastWakeTime variable with the current time.
	 */
	xLastWakeTime = xTaskGetTickCount();
 
	for(;;) {
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		mh_z19_takeMeassuring();
	}
}

/**
 * Called from outside to read the latest CO2 value
 * @return returns the latest CO2 value
 */
uint16_t readCO2() {
    return CO2;
}

/**
 * Called whenever a new CO2 value is read
 * @param ppm the read value
 */
void CO2ReadingCallBack(uint16_t ppm)
{
    /**
     * Here you can use the CO2 ppm value
     */
    CO2 = ppm;
}