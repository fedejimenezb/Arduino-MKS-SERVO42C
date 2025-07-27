#ifndef StepperMotor_h
#define StepperMotor_h

#include <Arduino.h>

class StepperMotor {
  public:
    // Constructor: Initializes the StepperMotor object.
    // pinStep: The GPIO pin connected to the STEP input of the driver.
    // pinDir: The GPIO pin connected to the DIR input of the driver.
    // pinEnable: The GPIO pin connected to the ENABLE input of the driver.
    // stepsPerRevolutionMotor: Number of full steps for one motor revolution (e.g., 200).
    // microstepsPerStep: Microstepping setting on the driver (e.g., 16).
    StepperMotor(int pinStep, int pinDir, int pinEnable, int stepsPerRevolutionMotor, int microstepsPerStep);

    // Initializes the motor driver pins and enables the driver.
    void begin();

    // Moves the stepper motor to a specified absolute angle.
    // targetAngle: The desired angle in degrees (0.0 to 360.0).
    // pulseDelayUs: The delay in microseconds between each step pulse.
    //               Smaller values result in faster speed. Default is 500 us.
    void moveToAngle(float targetAngle, int pulseDelayUs = 500);

    // Returns the current angular position of the motor in degrees.
    float getCurrentAngle();

  private:
    int _stepPin;
    int _dirPin;
    int _enablePin;
    int _stepsPerRevolutionMotor;
    int _microstepsPerStep;
    long _totalMicrostepsPerRevolution;
    float _currentAngle;

    // Private helper function to validate and normalize angles.
    float _normalizeAngle(float angle);
};

#endif
