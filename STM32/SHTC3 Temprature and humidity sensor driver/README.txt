# SHT3 Temperature and Humidity Sensor Driver (Simulated)

## Project Overview

This project provides a C driver for the SHT3 temperature and humidity sensor. It includes a helper function to simulate the I2C communication, allowing for testing and development without requiring actual hardware.

**Key Components:**

* **`sensor.c` and `sensor.h`:** These files contain the driver implementation for the SHT3 sensor, providing functions to read temperature and humidity data.
* **`main.c` and `main.h`:** These files demonstrate how to use the SHT3 driver and helper functions in a main application.
* **`helperFunc.c` and `helperFunc.h`:** These files contain helper functions to simulate the I2C communication, enabling testing and development without hardware.

**Functionality:**

1.  **Sensor Driver:**
    * The `sensor.c` file implements functions to:
        * Initialize the SHT3 sensor.
        * Read temperature and humidity data.
        * Process the raw sensor data.
2.  **I2C Simulation:**
    * The `helperFunc.c` file provides functions to simulate I2C communication, including:
        * Simulating I2C start and stop conditions.
        * Simulating sending and receiving data over I2C.
3.  **Main Application:**
    * The `main.c` file demonstrates how to use the sensor driver and helper functions to:
        * Initialize the sensor.
        * Read temperature and humidity data.
        * Print the data to the console (or simulate other output).

## Software Implementation

* **Sensor Driver (`sensor.c` and `sensor.h`):**
    * Implements functions to communicate with the SHT3 sensor using simulated I2C.
    * Handles sensor initialization and data reading.
    * Applies necessary conversions to obtain temperature and humidity values.
* **Helper Functions (`helperFunc.c` and `helperFunc.h`):**
    * Provides functions to simulate I2C communication.
    * Allows for testing and development without hardware.
* **Main Application (`main.c` and `main.h`):**
    * Demonstrates how to use the sensor driver and helper functions.
    * Simulates a main application loop.

## Why Simulation?

This project uses simulated I2C communication to:

* Enable testing and development without requiring physical hardware.
* Facilitate rapid prototyping and experimentation.
* Provide a platform for learning and understanding the SHT3 sensor and I2C communication.

## Building and Running the Project

1.  **Prerequisites:**
    * A development environment (e.g.Visual Studio Code).
2.  **Compile the Project:**
    * Compile the `sensor.c`, `helperFunc.c`, and `main.c` files using your C compiler.
3.  **Run the Executable:**
    * Execute the compiled program.
    * The program will simulate reading temperature and humidity data from the SHT3 sensor and print the results to the console.

## Important Notes

* **Hardware Testing:** This project is based on simulated I2C communication. To test with actual hardware, you will need to replace the helper functions with actual I2C communication functions for your target platform.
* **Sensor Datasheet:** Refer to the SHT3 sensor datasheet for detailed information about the sensor's registers and communication protocol.
* **Error Handling:** The current implementation may not include comprehensive error handling. Consider adding error handling for production use.
* **I2C Implementation:** The I2C helper function is a simple software simulation, and it may not be suitable for all I2C devices.