#pragma once
#include <ATMEGA_FreeRTOS.h>

/**
 * Initialises the humidity and temperature sensor
 * @param TEMHUMPriority task priority
 */
void initialiseTEMHUM(UBaseType_t TEMHUMPriority);

/**
 * Reads the humidity value of the sensor
 * @return humidity value
 */
uint16_t ReadHumidity();
/**
 * Reads the temperature value of the sensor
 * @return temperature value
 */
int16_t ReadTemperature();
