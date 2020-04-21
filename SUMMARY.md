Software Summary
================

The *source* directory contains the software I wrote, 
with the other folders containing drivers and files provided by NXP and freeRTOS.
The *car_drivers* folder within *source* contains the C++ code I implemented to
drive the components of the car on top of the existing low-level microcontroller peripheral drivers.
The *PortExpander* and *UserInterface* files are sources provided by Adafruit to interface with an
LCD display / button input module designed to work with arduino, with modifications by me to work 
on top of freeRTOS and with the NXP I2C driver.

The other files in the *source* directory implement the main functionality of the project, combining
the input and output drivers to navigate our car around the track by processing camera input. The main
function can be found in *NXP_Car_Drive.cpp.* *MotorDrive.cpp* implements a helper class for driving the
pair of motors on the car in tandem, allowing for differential speed to improve cornering performance.
Because the particular camera used for the project requires a set of carefully timed control signals, much
of that is handled within *interrupt_handlers.cpp* which creates appropriate signals based on the output of
a few of the K64F's timer peripherals. Once one scan of the camera is complete, the interrupt handler unblocks
an RTOS task to process that data.

The main function within *NXP_Car_Drive.cpp* handles peripheral initialization, initialization of the
car actuator and camera drivers, setting of interrupt priorities, and then simply starts all of the 
necessary RTOS tasks that implement the car driving behavior. 