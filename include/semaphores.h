/*
 * semaphores.h
 *
 * Created: 29/05/2023 13:05:33
 *  Author: andrejs
 */ 


#pragma once
#include <stddef.h>
#include <avr/io.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

/*
 * Semaphore for accessing servo status
 */
SemaphoreHandle_t xServoStatusSemaphore;

/**
 * Semaphore for accessing servo configuration
 */
SemaphoreHandle_t xServoConfigurationSemaphore;

void initialiseSemaphores();

/**
 * wait to access a semaphore
 * @param semaphore
 */
void waitForSemaphore(SemaphoreHandle_t semaphore);