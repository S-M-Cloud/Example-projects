/** 
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

/***************************************************************************************************
                                            DEFINITIONS
***************************************************************************************************/
#define SerialNumber_size 16
#define HWrevision_size   20
#define SWversion_size    32
#define Location_size     100
#define DaysDeployed_size 7000
#define NumberOfFailures_size 100

#define NumOfFields        6
#define SizeOfField        100

#define MAX_Size_HW        30
#define MAX_Size_SW        30
#define MAX_Size_LOC       30

const int SERIAL_NUM_INDEX  = 0;
const int HW_REVISION_INDEX = 1;
const int SW_VERSION_INDEX  = 2;
const int LOCATION_INDEX    = 3;
const int DAYS_INDEX        = 4;
const int FAILURES_INDEX    = 5;
    
// Struct to structurize the input data
typedef struct {
  char SERIAL_NUMBER[SerialNumber_size];
  char HW_REVISION[HWrevision_size];
  char SW_VERSION[SWversion_size];
  char LOCATION[Location_size];
  int  DAYS_DEPLOYED;
  int  NUMBER_FAILUERS;
}DeviceStructure;

/***************************************************************************************************
                                        FUNCTION DECLARATIONS
***************************************************************************************************/
void CalculateHWAvgFailures (DeviceStructure devices[], int NumberOfDevices,float *Average_HW_Failure, char *HWVersion);
void CalculateSWAvgFailures (DeviceStructure devices[], int NumberOfDevices,float *Average_SW_Failure, char *SWVersion);
void CalculateLOCAvgFailures(DeviceStructure devices[], int NumberOfDevices,float *Average_Location_Failure, char *Location);

/***************************************************************************************************
                                        FUNCTION STUBS
***************************************************************************************************/
 
// This function checks if two float values are equal
int compare_float_equal(float f1, float f2)
 {
  float precision = 0.01;
  if (fabs (f1 - f2) < precision)
   {
    return 1;
   }
  else
   {
    return 0;
   }
 }

// ******************************************************************************  
// This function calculates the average of failures per day for hardware revision:
void CalculateHWAvgFailures (DeviceStructure devices[], int NumberOfDevices,float *Average_HW_Failure, char *HWVersion)
{                               
    // Find unique HW versions
    int  num_unique_revision = 0;
    char unique_HW_revision[NumberOfDevices][MAX_Size_HW]; 
  
    for (int i = 0; i < NumberOfDevices; i++) {
        int FLAG_HW = 0;
        for (int j = 0; j < num_unique_revision; j++) {
            if (strcmp(devices[i].HW_REVISION, unique_HW_revision[j]) == 0) {
                FLAG_HW = 1;
                break;
            }
        }
        if (!FLAG_HW) {
            strcpy(unique_HW_revision[num_unique_revision++], devices[i].HW_REVISION);
        }
    }

    // Calculate total failures and days employed for each unique HW version
    int HW_failures[num_unique_revision];
    int HW_days[num_unique_revision];
    memset(HW_failures, 0, sizeof(HW_failures));
    memset(HW_days, 0, sizeof(HW_days)); 
    for (int i = 0; i < NumberOfDevices; i++) {
        for (int j = 0; j < num_unique_revision; j++) {
            if (strcmp(devices[i].HW_REVISION, unique_HW_revision[j]) == 0) {
                HW_failures[j] += devices[i].NUMBER_FAILUERS;
                HW_days[j] += devices[i].DAYS_DEPLOYED;
                break; 
            }
        }
    }

    // Calculate and store average failures per day for each unique HW version
    float HW_avg_failures_per_day[num_unique_revision];
    for (int i = 0; i < num_unique_revision; i++) {
     if (HW_failures[i] == 0 ) {
       
         HW_avg_failures_per_day[i] = 0; 
      } 
      else
      {
        HW_avg_failures_per_day[i] = (float)HW_failures[i] / (float)HW_days[i];
      }
    }
             
    // Find the index of the HW version with the highest average failures
    int highest_HW_avg_index = 0;
    for (int i = 1; i < num_unique_revision; i++) {
        if (HW_avg_failures_per_day[i] > HW_avg_failures_per_day[highest_HW_avg_index])
        {
            highest_HW_avg_index = i;
        }
        }

   *Average_HW_Failure= HW_avg_failures_per_day[highest_HW_avg_index];
   strcpy(HWVersion, unique_HW_revision[highest_HW_avg_index]); 
}


// ******************************************************************************
// This function calculates the average of failures per day for software version:
void CalculateSWAvgFailures (DeviceStructure devices[], int NumberOfDevices,float *Average_SW_Failure, char *SWVersion)
{
      // Find unique SW versions
    int  num_unique_SWversion = 0;
    char unique_SW_version[NumberOfDevices][MAX_Size_SW]; 
   
    for (int i = 0; i < NumberOfDevices; i++) {
        int FLAG_SW = 0;
        for (int j = 0; j < num_unique_SWversion; j++) {
            if (strcmp(devices[i].SW_VERSION, unique_SW_version[j]) == 0) {
                FLAG_SW = 1;
                break;
            }
        }
        if (!FLAG_SW) {
            strcpy(unique_SW_version[num_unique_SWversion++], devices[i].SW_VERSION);
        }
    }

    // Calculate total failures and days employed for each unique SW revision
    int SW_failures[num_unique_SWversion];
    int SW_days[num_unique_SWversion];
    memset(SW_failures, 0, sizeof(SW_failures));
    memset(SW_days, 0, sizeof(SW_days)); 
    for (int i = 0; i < NumberOfDevices; i++) {
        for (int j = 0; j < num_unique_SWversion; j++) {
            if (strcmp(devices[i].SW_VERSION, unique_SW_version[j]) == 0) {
                SW_failures[j] += devices[i].NUMBER_FAILUERS;
                SW_days[j] += devices[i].DAYS_DEPLOYED;
                break; 
            }
        }
    }

    // Calculate and store average failures per day for each unique SW version
    float SW_avg_failures_per_day[num_unique_SWversion];
    for (int i = 0; i < num_unique_SWversion; i++) {
      if (SW_failures[i] == 0)
      {
         SW_avg_failures_per_day[i] = 0; 
      }
      else {
         SW_avg_failures_per_day[i] = (float)SW_failures[i] / (float)SW_days[i];
         
      }
    }

    // Find the index of the SW version with the highest average failures
    int highest_SW_avg_index = 0;
    for (int i = 1; i < num_unique_SWversion; i++) {
        if (SW_avg_failures_per_day[i] > SW_avg_failures_per_day[highest_SW_avg_index]) {
            highest_SW_avg_index = i;
        }
    }
  
   *Average_SW_Failure = SW_avg_failures_per_day[highest_SW_avg_index];
   strcpy(SWVersion, unique_SW_version[highest_SW_avg_index]);  
}


// **************************************************************************************
// This function calculates the average of failures per day for Location:
void CalculateLOCAvgFailures (DeviceStructure devices[], int NumberOfDevices,float *Average_Location_Failure, char *Location)
{
    // Find unique Locations
    int  num_unique_LOCversion = 0;
    char unique_LOC_version[NumberOfDevices][MAX_Size_LOC]; 
    
    for (int i = 0; i < NumberOfDevices; i++) {
        int FLAG_L = 0;
        for (int j = 0; j < num_unique_LOCversion; j++) {
            if (strcmp(devices[i].LOCATION, unique_LOC_version[j]) == 0) {
                FLAG_L = 1;
                break;
            }
        }
        if (!FLAG_L) {
            strcpy(unique_LOC_version[num_unique_LOCversion++], devices[i].LOCATION);
        }
    }

    // Calculate total failures and days employed for each unique location
    int LOC_failures[num_unique_LOCversion];
    int LOC_days[num_unique_LOCversion];
    memset(LOC_failures, 0, sizeof(LOC_failures));
    memset(LOC_days, 0, sizeof(LOC_days)); 
    for (int i = 0; i < NumberOfDevices; i++) {
        for (int j = 0; j < num_unique_LOCversion; j++) {
            if (strcmp(devices[i].LOCATION, unique_LOC_version[j]) == 0) {
                LOC_failures[j] += devices[i].NUMBER_FAILUERS;
                LOC_days[j] += devices[i].DAYS_DEPLOYED;
                break; 
            }
        }
    }

    // Calculate and store average failures per day for each unique location
    float LOC_avg_failures_per_day[num_unique_LOCversion];
    for (int i = 0; i < num_unique_LOCversion; i++) {
            if (LOC_failures[i] == 0) 
            {
               LOC_avg_failures_per_day[i] = 0;
                          
            }
             else  {
             LOC_avg_failures_per_day[i] = (float)LOC_failures[i] / (float)LOC_days[i]; 
       }
    }


    // Find the index of the location with the highest average failures
    int highest_LOC_avg_index = 0;
    for (int i = 1; i < num_unique_LOCversion; i++) {
        if (LOC_avg_failures_per_day[i] > LOC_avg_failures_per_day[highest_LOC_avg_index]) {
            highest_LOC_avg_index = i;
        }
    }
  
   *Average_Location_Failure = LOC_avg_failures_per_day[highest_LOC_avg_index];
   strcpy(Location, unique_LOC_version[highest_LOC_avg_index]); 
   
}

/****************************Main Function*******************************************/

int main() 
{
  
// ************************ Read lines of input***************************************
 
  int line = 0;
  int NumOfTotalDevices= 1000;
  char strdata[NumOfTotalDevices][SizeOfField]; // string to store input list
  char arrdata[NumOfTotalDevices][SizeOfField]; // aray to store data for each device

    for (int i = 0; i < NumOfTotalDevices; i++) { 
        if (fgets(strdata[i], sizeof(strdata), stdin) == NULL) { 
            break; 
        }
        line++; 

        // Copy the line from string to array 
        strcpy(arrdata[i], strdata[i]); 
    }

    NumOfTotalDevices = line;

// **************Tokenize the input data into devicelist****************************
    
  char deviceList[NumOfTotalDevices][NumOfFields][SizeOfField];
    int MAX_TOKEN_LEN = 50;
    const char* delim = ","; 
    char* tok;
    int row = 0, col = 0;

    for (int i = 0; i < NumOfTotalDevices; i++) { 
        tok = strtok(arrdata[i], delim); 
        col = 0; 

        while (tok != NULL && col < NumOfFields) {
            strcpy(deviceList[row][col], tok);
            tok = strtok(NULL, delim);
            col++;
        }
        row++;
    }

// ***************** Transfer the data to struct**********************
DeviceStructure Devices[NumOfTotalDevices];

char HWVersion;
char SWVersion;
char Location;
float Average_HW_Failure;  
float Average_SW_Failure;
float Average_Location_Failure;

 for (int m=0 ; m<NumOfTotalDevices; m++)
 {
    strcpy( Devices[m].SERIAL_NUMBER,deviceList[m][SERIAL_NUM_INDEX]);
    strcpy( Devices[m].HW_REVISION  ,deviceList[m][HW_REVISION_INDEX]);
    strcpy( Devices[m].SW_VERSION   ,deviceList[m][SW_VERSION_INDEX]);
    strcpy( Devices[m].LOCATION     ,deviceList[m][LOCATION_INDEX]);
    
     for (int i = 0; Devices[m].LOCATION[i] != '\0'; i++)   // Converts all location names to lower case to avoid confusion
     {
        Devices[m].LOCATION[i] = tolower(Devices[m].LOCATION[i]); 
     }
 
    Devices[m].DAYS_DEPLOYED   = atoi(deviceList[m][DAYS_INDEX]);   
    Devices[m].NUMBER_FAILUERS = atoi(deviceList[m][FAILURES_INDEX]);
 }
  
  
// ******************* Calculate average failure per day*****************
  
/* Calculate HWAverageFailures per day for all devices. Print the average and the hardware revision if necessary*/
   CalculateHWAvgFailures(Devices,NumOfTotalDevices,&Average_HW_Failure,&HWVersion);
     
     float Average_HW_Failure_value = Average_HW_Failure;
     char  HWrevision_name [HWrevision_size];
   
     strcpy(HWrevision_name, &HWVersion);
  
     /*printf("Average_HW:");
     printf("%.2f\n",Average_HW_Failure_value );
     printf("HW revision:");
     printf("%s\n",HWrevision_name );*/
  
         
/* Calculate SWAverageFailures per day for all devices. Print the average and the software version if necessary*/
  CalculateSWAvgFailures(Devices,NumOfTotalDevices,&Average_SW_Failure,&SWVersion);

     float Average_SW_Failure_value = Average_SW_Failure;
     char  SWversion_name [SWversion_size];
     
     strcpy(SWversion_name, &SWVersion);
     
     /*printf("Average_SW:");
     printf("%.2f\n",Average_SW_Failure_value );
     printf("SW version");
     printf("%s\n",SWversion_name);*/
 
 /* Calculate LocationAverageFailures per day for all devices.Print the average and the location if necessary*/
 CalculateLOCAvgFailures(Devices,NumOfTotalDevices,&Average_Location_Failure,&Location); 
 
     float Average_Location_Failure_value = Average_Location_Failure;
     char  Location_name [Location_size];
     
     strcpy(Location_name, &Location);

     /*printf("Average_Location:");
     printf("%.2f\n",Average_Location_Failure_value);
     printf("Location:");
     printf("%s\n",Location_name);*/
    
  
  
// *************************** Perform comparison to find the main root cause******************
   
   if (compare_float_equal(Average_HW_Failure_value, 0) && compare_float_equal(Average_SW_Failure_value, 0) && compare_float_equal(Average_Location_Failure_value, 0)) {
         printf("No failure");
    } 
    
  else if (compare_float_equal(Average_HW_Failure_value, Average_SW_Failure_value) && compare_float_equal(Average_HW_Failure_value, Average_Location_Failure_value)) {
         printf("Hardware revision :");
         printf("%s\n",HWrevision_name);
         printf("Software version :");
         printf("%s\n",SWversion_name);
         printf("Location :");
         printf("%s\n",Location_name);
    } 
 
  else if (compare_float_equal(Average_HW_Failure_value, Average_SW_Failure_value) && Average_HW_Failure_value >= Average_Location_Failure_value) {
         printf("Hardware revision :");
         printf("%s\n",HWrevision_name);
         printf("Software version :");
         printf("%s\n",SWversion_name);
    } 
  
  else if (compare_float_equal(Average_HW_Failure_value, Average_Location_Failure_value) && Average_HW_Failure_value >= Average_SW_Failure_value) {
         printf("Hardware revision :");
         printf("%s\n",HWrevision_name);
         printf("Location :");
         printf("%s\n",Location_name);
    } 
  
  else if (compare_float_equal(Average_SW_Failure_value, Average_Location_Failure_value) && (Average_SW_Failure_value >= Average_HW_Failure_value))
  {
         printf("Software version :");
         printf("%s\n",SWversion_name);
         printf("Location :");
         printf("%s\n",Location_name);
  }
   
  else if (Average_HW_Failure_value >= Average_SW_Failure_value && Average_HW_Failure_value >= Average_Location_Failure_value) {
         printf("Hardware revision :");
         printf("%s\n",HWrevision_name);
    } 
  
  else if (Average_SW_Failure_value >= Average_HW_Failure_value && Average_SW_Failure_value >= Average_Location_Failure_value) {
         printf("Software version :");
         printf("%s\n",SWversion_name);
    }
  
  else if (Average_Location_Failure_value >= Average_HW_Failure_value && Average_Location_Failure_value >= Average_SW_Failure_value) {
         printf("Location :");
         printf("%s\n",Location_name);

    }
  
    return 0;
}