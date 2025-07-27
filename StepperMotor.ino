#include <Arduino.h>
#include <StepperMotor.h> // Include the newly created library

// Define the GPIO pins connected to the MKS-SERVO42C driver.
// IMPORTANT: Adjust these to your ESP32-C6 board's actual pinout.
const int STEP_PIN = 5;
const int DIR_PIN = 6;
const int ENABLE_PIN = 4;

// --- Motor Parameters ---
// Adjust these based on your specific stepper motor and MKS-SERVO42C settings.
const int STEPS_PER_REVOLUTION = 200; // Example: 1.8 degree/step motor
const int MICROSTEPS = 16;            // Example: MKS-SERVO42C set to 16 microsteps

// Create an instance of the StepperMotor object
// The constructor takes (STEP_PIN, DIR_PIN, ENABLE_PIN, STEPS_PER_REVOLUTION, MICROSTEPS)
StepperMotor myStepper(STEP_PIN, DIR_PIN, ENABLE_PIN, STEPS_PER_REVOLUTION, MICROSTEPS);

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to open

  Serial.println("ESP32-C6 Stepper Control Example Sketch.");
  myStepper.begin(); // Initialize the stepper motor pins and enable the driver

  Serial.println("\nReady to receive commands via Serial.");
  Serial.println("Enter 'ANGLE' (e.g., '90') for default speed.");
  Serial.println("Or 'ANGLE,SPEED_US' (e.g., '180,200') to specify speed in microseconds.");
  Serial.println("Smaller SPEED_US = Faster. Recommended range: 100-5000.");
}

void loop() {
  // Check if data is available on the Serial port
  if (Serial.available()) {
    String serialInput = Serial.readStringUntil('\n'); // Read the input string until newline
    serialInput.trim(); // Remove any leading/trailing whitespace

    float targetAngle;
    int pulseDelayUs = 500; // Default pulse delay

    // Find comma to separate angle from speed
    int commaIndex = serialInput.indexOf(',');
    String angleString;
    String speedString = "";

    if (commaIndex != -1) {
      angleString = serialInput.substring(0, commaIndex);
      speedString = serialInput.substring(commaIndex + 1);
      pulseDelayUs = speedString.toInt(); // Convert speed string to integer
    } else {
      angleString = serialInput;
    }
  
    targetAngle = angleString.toFloat();

    // Check if the conversion was successful and the input is valid
    if (angleString.length() > 0 && (targetAngle >= 0.0 && targetAngle <= 360.0)) {
      Serial.print("Received command: Move to ");
      Serial.print(targetAngle);
      Serial.print(" degrees at ");
      Serial.print(pulseDelayUs);
      Serial.println(" us pulse delay.");
      myStepper.moveToAngle(targetAngle, pulseDelayUs); // Use the library method
    } else {
      Serial.print("Invalid input: '");
      Serial.print(serialInput);
      Serial.println("'. Please enter an angle (0-360) or 'ANGLE,SPEED_US'.");
    }
  }
}
