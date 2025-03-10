/**
 * @file Sensor.h
 * @date October 13,2024
 * @author Shiva Moghtaderi 
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdint.h>
#include <unistd.h>
#include "helperFunc.h"


typedef struct sensor_command_t {
	uint8_t ID;
	uint8_t paramLength;
} sensor_command_t;


/*!
 * \brief Read-out of ID Register
 * \param [IN] deviceAddr       device address
 */
uint8_t SHTC3_GetId(uint8_t deviceAddr);


/*!
 * \brief Put the sensor in sleep mode
 *
 */

 int SHTC3_Sleep();


/*!
 * \brief Put the sensor in wake up mode
 *
 */
 int SHTC3_Wakeup();


/*!
 * \brief Measuring and Reading the Signals
 * \param [IN] temperature       final temperature
 * \param [IN] humidity       final humidity
 */
uint8_t   SHTC3_Measurement(float *temperature, float *humidity);

#endif