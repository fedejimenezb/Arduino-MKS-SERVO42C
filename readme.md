Stepper Motor Control Library for ESP32-C6
This repository contains an Arduino library designed to control a stepper motor using an ESP32-C6 microcontroller and an MKS-SERVO42C driver. The library allows for precise angular positioning and speed control of the stepper motor.

Files Included
This library consists of three main files:

StepperMotor.h (Header File)

This file defines the StepperMotor class.

It declares the class constructor and public methods that you can use to interact with the stepper motor, such as begin() for initialization and moveToAngle() for moving the motor.

It also declares private member variables to store pin assignments, motor parameters, and the current angle.

StepperMotor.cpp (Source File)

This file provides the implementation details for the methods declared in StepperMotor.h.

Constructor: Initializes the stepper motor object with the specified pins and motor parameters (steps per revolution, microstepping).

begin(): Configures the GPIO pins as outputs and enables the MKS-SERVO42C driver. It also performs an initial movement to 0 degrees to set a known starting position.

moveToAngle(float targetAngle, int pulseDelayUs): This is the core function for controlling the motor.

It takes a targetAngle (0-360 degrees) and an optional pulseDelayUs (microseconds between step pulses) to control speed.

It calculates the angle difference between the current and target positions.

It determines the direction (clockwise or counter-clockwise) based on the sign of the angle difference.

It converts the required angular movement into the corresponding number of microsteps.

It then generates the necessary step pulses on the STEP_PIN with the specified pulseDelayUs to move the motor.

The currentAngle is updated after the movement.

Note: This implementation moves the motor directly by the calculated difference, meaning it does not automatically choose the "shortest path" around the 360-degree circle if the difference is greater than 180 degrees. For example, moving from 0 to 270 degrees will result in a 270-degree clockwise rotation.

getCurrentAngle(): Returns the motor's last known angular position.

_normalizeAngle(float angle) (Private Helper): Ensures the target angle is within the valid 0-360 degree range.

StepperMotor_Example.ino (Example Arduino Sketch)

This is an example program demonstrating how to use the StepperMotor library.

It includes the StepperMotor.h header.

It defines the specific GPIO pins for your ESP32-C6 and the motor parameters (steps per revolution, microsteps). You must adjust these constants to match your hardware.

It creates an instance of the StepperMotor class, passing the pin and motor parameters to its constructor.

setup() function:

Initializes serial communication for debugging.

Calls myStepper.begin() to set up the motor driver.

Prints instructions to the Serial Monitor for controlling the motor.

loop() function:

Continuously checks for incoming data on the Serial Monitor.

Parses the serial input to extract the targetAngle and an optional pulseDelayUs (speed). The input format is ANGLE or ANGLE,SPEED_US.

Validates the input.

Calls myStepper.moveToAngle() with the parsed values to move the motor.

Prints status and error messages to the Serial Monitor.

How to Use the Library
Create Library Folder:

Navigate to your Arduino sketchbook directory (usually Documents/Arduino/).

Inside, create a new folder named libraries.

Inside libraries, create another new folder named StepperMotorLib.

Place Files:

Save the content of StepperMotor.h into StepperMotorLib/StepperMotor.h.

Save the content of StepperMotor.cpp into StepperMotorLib/StepperMotor.cpp.

Restart Arduino IDE: Close and reopen the Arduino IDE to allow it to discover the new library.

Open Example Sketch:

Open the StepperMotor_Example.ino file in the Arduino IDE.

Go to Sketch > Include Library > StepperMotorLib to confirm the library is recognized.

Configure Pins and Motor Parameters:

In StepperMotor_Example.ino, modify the STEP_PIN, DIR_PIN, ENABLE_PIN constants to match the GPIO pins you've connected on your ESP32-C6.

Adjust STEPS_PER_REVOLUTION and MICROSTEPS to accurately reflect your stepper motor's specifications and the microstepping setting on your MKS-SERVO42C driver.

Wiring:

Connect the STEP, DIR, and ENABLE pins from your ESP32-C6 to the corresponding inputs on the MKS-SERVO42C.

Ensure a common ground connection between the ESP32 and the driver.

Provide an external power supply to the MKS-SERVO42C and your stepper motor as per their specifications.

Upload and Control:

Select your ESP32-C6 board and the correct COM port in Tools > Board and Tools > Port.

Upload the StepperMotor_Example.ino sketch to your ESP32-C6.

Open the Serial Monitor (set to 115200 baud).

Type commands in the Serial Monitor's input field and press Enter:

90: Moves the motor to 90 degrees using the default speed.

180,200: Moves the motor to 180 degrees with a pulse delay of 200 microseconds (faster).

0,1000: Moves the motor to 0 degrees with a pulse delay of 1000 microseconds (slower).

Important Notes
Speed Control (pulseDelayUs): Experiment with pulseDelayUs values. Too low (too fast) can cause missed steps or stalling. Too high (too slow) might result in jerky motion. A range of 100-5000 microseconds is generally safe to start with.

Motor Torque: Stepper motor torque decreases at higher speeds.

Physical Limits: Ensure your mechanical setup prevents the motor arm from hitting physical stops, as the code does not implement external limit switches. The angle range (0-360) is a software limit.

Power Supply: Always use an adequate external power supply for the MKS-SERVO42C and the stepper motor.

