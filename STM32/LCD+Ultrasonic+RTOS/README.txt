# Ultrasonic Distance Measurement with STM32 and FreeRTOS

## Project Overview

This project demonstrates a simple ultrasonic distance measurement system using an STM32 microcontroller and the FreeRTOS real-time operating system. The system utilizes an HC-SR04 ultrasonic sensor to measure distances and displays the readings on an SSD1306 OLED display.

**Key Components:**

* **STM32 Microcontroller:** The microcontroller acts as the brain of the system, controlling the sensor, processing data, and updating the display.
* **HC-SR04 Ultrasonic Sensor:** This sensor measures distances by emitting ultrasonic pulses and measuring the time it takes for the pulses to return.
* **SSD1306 OLED Display:** This display shows the measured distance in centimeters.
* **FreeRTOS:** A real-time operating system that allows for concurrent execution of tasks, making the system more organized and responsive.

**Functionality:**

1.  **Ultrasonic Measurement:**
    * The `ultrasonicTask` triggers the HC-SR04 sensor to emit an ultrasonic pulse.
    * It then captures the echo signal and calculates the distance.
    * The calculated distance is sent to a FreeRTOS queue.
2.  **Display Update:**
    * The `lcdTask` receives the distance from the queue.
    * It formats the distance into a string and updates the SSD1306 display.

## Hardware Setup

* Connect the HC-SR04 sensor to the STM32 as follows:
    * VCC to 5V
    * GND to GND
    * Trig to an STM32 GPIO pin (PE8)
    * Echo to an STM32 GPIO pin (PE9)
* Connect the SSD1306 OLED display to the STM32 via I2C (PB6.PB7).

## Software Implementation

* **FreeRTOS Tasks:**
    * `ultrasonicTask`: Handles ultrasonic sensor readings and sends data to the queue.
    * `lcdTask`: Receives data from the queue and updates the LCD display.
* **Timer Configuration:**
    * TIM1 is configured for input capture to measure the echo pulse width.
* **Queue:**
    * A FreeRTOS queue (`xdistanceQueue`) is used to pass distance data between tasks.
* **SSD1306 Library:**
    * The `ssd1306.c` and `ssd1306.h` files provide functions for controlling the OLED display.
* **HCSR04 Driver:**
    * The code contains the functions to trigger the sensor, and to capture the echo.

## Why FreeRTOS?

While this project could be implemented without an RTOS, I chose to use FreeRTOS to:

* Demonstrate my understanding of RTOS concepts.
* Showcase my coding style in a multi-tasking environment.
* Create a more organized and modular codebase.
* Prepare for more complex projects.

I recognize that FreeRTOS is typically used for more complex applications, but this simple example allows me to illustrate my ability to work with real-time operating systems.

## Important Notes

* **Timer Precision:** The accuracy of the distance measurement depends on the precision of the timer configuration.
* **Wiring:** Double-check the wiring between the STM32 and the HC-SR04 sensor and the OLED display.
* **RTOS Configuration:** Ensure that FreeRTOS is correctly configured in your project.
* **Datasheet:** Refer to the HC-SR04 datasheet for detailed information about the sensor.