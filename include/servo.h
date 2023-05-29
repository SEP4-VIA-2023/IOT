/*
 * servo.h
 *
 * Created: 23/05/2023 11:21:13
 *  Author: andrejs
 */ 


#pragma once

#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>

/**
 * Configuration to run the servo, degreeRotation should be from -100 to 100
 */
struct Configuration {
	uint16_t minCO2_config;
	uint16_t maxCO2_config;
	int16_t minTemperature_config;
	int16_t maxTemperature_config;
	uint16_t minHumidity_config;
	uint16_t maxHumidity_config;
	int8_t degreeRotation;
};

/**
 * Status of the servo including what values it has read
 */
struct Status {
	int8_t servoDegrees;
	uint16_t CO2_value;
	uint16_t humidity_value;
	int16_t temperature_value;
};

/**
 * Initialises the servo
 * @param servoTaskPriority task priority
 * @param minCO2 minimum CO2 value
 * @param maxCO2 maximum CO2 value
 * @param minTemperature minimum temperature value
 * @param maxTemperature maximum temperature value
 * @param minHumidity minimum humidity value
 * @param maxHumidity maximum humidity value
 * @param degreeRotation servo rotation
 */
void initialiseServo(UBaseType_t servoTaskPriority,
					uint16_t minCO2, uint16_t maxCO2,
					int16_t minTemperature, int16_t maxTemperature,
					uint16_t minHumidity, uint16_t maxHumidity,
					int8_t degreeRotation
					);

/**
 * Returns a pointer to the status of the servo including CO2, Humidity and Temperature readings
 * @return pointer to the status of the servo
 */
struct Status* readStatus();

/**
 * Returns a pointer to the current configuration that the servo is using
 * @return pointer to the current configuration that the servo is using
 */
struct Configuration* readConfiguration();

/**
 * Set new configuration
 * @param minCO2 minimum CO2 value
 * @param maxCO2 maximum CO2 value
 * @param minTemperature minimum temperature value
 * @param maxTemperature maximum temperature value
 * @param minHumidity minimum humidity value
 * @param maxHumidity maximum humidity value
 * @param degreeRotation servo rotation
 */
void updateConfiguration(
	uint16_t minCO2, uint16_t maxCO2,
	int16_t minTemperature, int16_t maxTemperature,
	uint16_t minHumidity, uint16_t maxHumidity,
	int8_t degreeRotation
);
