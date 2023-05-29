#pragma once
#include <ATMEGA_FreeRTOS.h>

/**
 * must be called before FreeRTOS vTaskStartScheduler()
 * @param CO2Priority task priority
 */
void initialiseCO2(UBaseType_t CO2Priority);

/**
 * reads the CO2 value of the sensor
 * @return the CO2 value
 */
uint16_t readCO2();