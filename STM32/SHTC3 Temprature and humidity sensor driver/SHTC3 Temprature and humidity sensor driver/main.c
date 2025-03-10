/**
 * @file main.c
 * @date October 13,2024
 * @author Shiva Moghtaderi 
 */


#include <stdio.h>  
//#include <unistd.h>
#include "sensor.h"
#include "helperFunc.h"
#include <time.h>

#define  DeviceAddr           ((uint8_t) 0x70) // Device ddress(Table 8)


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main(void) 
{
   int wakeup_flag = SHTC3_Wakeup();

   int I2C_connection = SHTC3_GetId(DeviceAddr);

    if (I2C_connection == 0)
    {
     printf ("Successful communication with the sensor\n");
     }

    else 
    {
        printf ("Failed communication with the sensor\n");
    }

     while (1)
    {
        
    float temperature, humidity;
    
      
    uint8_t error =  SHTC3_Measurement(&temperature, &humidity);
    
      if (error == 0) {
        
      printf ("Temperature = %.1fC\n", temperature);
      printf ("Humidity = %.1f %\n", humidity);
      printf ("waiting for 10 seconds...\n");  
   }
 
   else {
    // Error reading measurement
    printf("Error reading measurement\n");
      }
 
    int sleep_flag = SHTC3_Sleep();
    delay (10000);
    
    }
}
