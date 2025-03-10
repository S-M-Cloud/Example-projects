/**
 * @file Sensor.c
 * @date October 12,2024
 * @author Shiva Moghtaderi 
 */

#include "sensor.h"
#include "helperFunc.h"
#include <stdint.h>
#include <unistd.h>

#define  DeviceAddr           ((uint8_t) 0x70) // Device ddress(Table 8)


#define READ_REGISTER_ID     ((uint8_t) 0xEFC8) // Read ID register(Table 14)
#define SLEEP_MODE_ID        ((uint8_t) 0xB098) // sleep mode command(Table 9)
#define WAKEUP_MODE_ID       ((uint8_t) 0x3517) // wakeup mode command(Table 10)
#define T_RH_MEASURE_ID      ((uint8_t) 0x7CA2) // read T first + clock stretching enabled + normal mode(Table 11)

#define REGISTER_ID_SIZE     ((uint8_t) 4)
#define SENSOR_DATA_SIZE     ((uint8_t) 6)


/***************************************************************************************************
                                             PRIVATE API
***************************************************************************************************/

/***********************Read-out of ID Register**************** */
 uint8_t SHTC3_GetId(uint8_t deviceAddr){
    
uint8_t commandBuffer[2] = {READ_REGISTER_ID >> 8, READ_REGISTER_ID & 0xFF};

//Send to I2C
uint8_t error = I2cWriteBuffer(DeviceAddr, commandBuffer, sizeof(commandBuffer));


//Receive from I2C
int IdBufferSize=2;
uint8_t buffer[IdBufferSize];

error = I2cReadBuffer(DeviceAddr, buffer, IdBufferSize );
if (error == 0) {
    
uint16_t IdRegister = (buffer[0] << 8) | buffer[1];
   
   return 0;
}
else {
        // Error reading ID
             return 1;
    }
 }

/************************Sleep command of the sensor**************** */
 int SHTC3_Sleep(void){
    
uint8_t commandBuffer[2] = {SLEEP_MODE_ID >> 8, SLEEP_MODE_ID & 0xFF};

//Send to I2C
int error = I2cWriteBuffer(DeviceAddr, commandBuffer, sizeof(commandBuffer));
  
  if (error == 0) {
   return 0;
}
else {
        // Error sleep mode
             return 1;
    }
 }

/************************Wake-up command of the sensor**************** */
 int SHTC3_Wakeup(void){
    
uint8_t commandBuffer[2] = {T_RH_MEASURE_ID >> 8, T_RH_MEASURE_ID & 0xFF};

int error = I2cWriteBuffer(DeviceAddr, commandBuffer, sizeof(commandBuffer));
if (error == 0) {
   return 0;
}
else {
        // Error wake up mode
             return 1;
    }
 }


/************************Readout of Measurement Results**************** */

uint8_t SHTC3_Measurement(float *temperature, float *humidity) {

    uint8_t commandBuffer[2] = {READ_REGISTER_ID >> 8, READ_REGISTER_ID & 0xFF};

    // Send to I2C
    uint8_t error = I2cWriteBuffer(DeviceAddr, commandBuffer, sizeof(commandBuffer));

    //sleep(300);

    if (error == 0) {
        // Receive from I2C
        int measurebuffersize = 4;
        uint8_t buffer[measurebuffersize];

        error = I2cReadBuffer(DeviceAddr, buffer, measurebuffersize );

        if (error == 0) {
            uint16_t raw_temp = buffer[0] << 8 | buffer[1];
            uint16_t raw_hum = buffer[2] << 8 | buffer[3];

            // Temperature Calculate [°C]
            // T = -45 + 175 * rawValue / 2^16
            *temperature = 175 * (float)raw_temp / 65536.0f - 45.0f;

            // Humidity Calculate[%RH]
            // RH = rawValue / 2^16 * 100
            *humidity = 100 * (float)raw_hum / 65536.0f;

            return 0; // Measurement successful
        } else {
            // Error reading measurement
            return 1;
        }
    } else {
        // Error sending command
        return 1;
    }
}


