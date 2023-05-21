#pragma once

// Must be called before FreeRTOS vTaskStartScheduler()
void initializeTemperature();

// Returns the value from the temperature sensor
int measureTemperature();