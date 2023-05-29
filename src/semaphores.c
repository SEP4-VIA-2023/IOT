/*
 * semaphores.c
 *
 * Created: 29/05/2023 13:08:10
 *  Author: andrejs
 */ 

#include "semaphores.h"

void initialiseSemaphores() {
    /**
     * Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
     * because it is sharing a resource, such as the Serial port.
     * Semaphores should only be used whilst the scheduler is running, but we can set it up here.
     */
	if ( xServoStatusSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xServoStatusSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xServoStatusSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xServoStatusSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

    /**
     * Do the same for Servo Configuration semaphore
     */
	if ( xServoConfigurationSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xServoConfigurationSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xServoConfigurationSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xServoConfigurationSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}
}

void waitForSemaphore(SemaphoreHandle_t semaphore) {
	TickType_t xLastWakeTime;
	const TickType_t xWaitingFrequency = 50/portTICK_PERIOD_MS; // 50 ms
    /**
     * Initialise the xLastWakeTime variable with the current time.
     */
	xLastWakeTime = xTaskGetTickCount();

    /**
     * Wait for semaphore to be free
     */
	while (xSemaphoreTake( semaphore, ( xWaitingFrequency ) ) != pdTRUE)
	{
	}
    /**
     * Semaphore is free
     */
}