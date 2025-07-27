#include "StepperMotor.h"

// Constructor implementation
StepperMotor::StepperMotor(int pinStep, int pinDir, int pinEnable, int stepsPerRevolutionMotor, int microstepsPerStep) {
  _stepPin = pinStep;
  _dirPin = pinDir;
  _enablePin = pinEnable;
  _stepsPerRevolutionMotor = stepsPerRevolutionMotor;
  _microstepsPerStep = microstepsPerStep;
  _totalMicrostepsPerRevolution = (long)_stepsPerRevolutionMotor * _microstepsPerStep;
  _currentAngle = 0.0; // Initialize current angle to 0
}

// begin() method implementation
void StepperMotor::begin() {
  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
  pinMode(_enablePin, OUTPUT);

  // Most stepper drivers have an active-low enable pin.
  // Set LOW to enable MKS-SERVO42C (assuming active-low).
  digitalWrite(_enablePin, LOW);
  Serial.println("StepperMotor Driver Enabled.");

  // Move to initial position (0 degrees) to ensure a known state.
  // This uses the default pulse delay.
  moveToAngle(0.0);
  Serial.println("Initial position set to 0 degrees.");
}

// Private helper to normalize angle to 0-360 range
float StepperMotor::_normalizeAngle(float angle) {
  if (angle < 0.0) {
    return 0.0;
  } else if (angle > 360.0) {
    return 360.0; // Or 0.0 if you want 360 to wrap to 0
  }
  return angle;
}

// moveToAngle() method implementation
void StepperMotor::moveToAngle(float targetAngle, int pulseDelayUs) {
  targetAngle = _normalizeAngle(targetAngle); // Validate and normalize target angle

  // Ensure pulseDelayUs is a reasonable value to prevent issues
  if (pulseDelayUs < 100) pulseDelayUs = 100; // Minimum reasonable delay
  if (pulseDelayUs > 5000) pulseDelayUs = 5000; // Maximum reasonable delay

  // Calculate Angle Difference: Determine the raw difference between target and current angle.
  float angleDifference = targetAngle - _currentAngle;

  // Determine Movement Direction based on raw angle difference:
  // This logic moves the motor directly by the calculated difference,
  // without finding the shortest path around the 360-degree circle.

  // Set Direction Pin:
  if (angleDifference >= 0.0) {
    digitalWrite(_dirPin, HIGH); // Set direction for Clockwise (CW) movement
    Serial.println("Direction: Clockwise");
  } else {
    digitalWrite(_dirPin, LOW);  // Set direction for Counter-Clockwise (CCW) movement
    Serial.println("Direction: Counter-Clockwise");
    angleDifference = -angleDifference; // Convert negative difference to positive for step count
  }

  // Convert Angle Difference to Microsteps:
  long stepsToMove = (long)((angleDifference / 360.0) * _totalMicrostepsPerRevolution);

  Serial.print("Moving from ");
  Serial.print(_currentAngle);
  Serial.print(" to ");
  Serial.print(targetAngle);
  Serial.print(" degrees. Steps to move: ");
  Serial.print(stepsToMove);
  Serial.print(" at pulse delay: ");
  Serial.print(pulseDelayUs);
  Serial.println(" us.");

  // Execute Steps:
  for (long i = 0; i < stepsToMove; i++) {
    digitalWrite(_stepPin, HIGH);      // Send a HIGH pulse
    delayMicroseconds(pulseDelayUs);   // Keep it HIGH for a short duration
    digitalWrite(_stepPin, LOW);       // Send a LOW pulse
    delayMicroseconds(pulseDelayUs);   // Keep it LOW for a short duration
  }

  // Update Current Angle:
  _currentAngle = targetAngle;
  Serial.print("Current angle updated to: ");
  Serial.println(_currentAngle);
}

// getCurrentAngle() method implementation
float StepperMotor::getCurrentAngle() {
  return _currentAngle;
}
