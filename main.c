#include <Servo.h>

Servo servo;                // Create Servo object
int eastLDR = 0;            // Analog pin for East LDR
int westLDR = 1;            // Analog pin for West LDR
int east = 0;               // Variable to store East LDR reading
int west = 0;               // Variable to store West LDR reading
int threshold = 500;        // Threshold for light intensity
int eastPosition = 150;     // Servo position for East (maximum tilt)
int westPosition = 30;      // Servo position for West (minimum tilt)
int currentPosition = 90;   // Default position (middle)

void setup() {
  servo.attach(9);          // Attach servo to pin 9
  servo.write(currentPosition);  // Set initial servo position to middle

  // Initialize Serial communication at 9600 baud
  Serial.begin(9600);
  Serial.println("System Initialized!");
}

void loop() {
  // Read the light intensity from both LDRs
  east = analogRead(eastLDR);
  west = analogRead(westLDR);

  // Display LDR values and current position on the Serial Monitor
  Serial.print("East LDR: ");
  Serial.print(east);
  Serial.print("\tWest LDR: ");
  Serial.print(west);
  Serial.print("\tCurrent Position: ");
  Serial.println(currentPosition);

  // Check if the east LDR detects high intensity
  if (east > threshold && east > west) {
    if (currentPosition != eastPosition) { // Move only if not already in position
      currentPosition = eastPosition;
      servo.write(currentPosition);       // Move servo to east position
      delay(1000);                         // Allow time for the servo to move
    }
  }
  // Check if the west LDR detects high intensity
  else if (west > threshold && west > east) {
    if (currentPosition != westPosition) { // Move only if not already in position
      currentPosition = westPosition;
      servo.write(currentPosition);       // Move servo to west position
      delay(1000);                         // Allow time for the servo to move
    }
  }
  // If neither side has significant intensity, return to middle
  else {
    if (currentPosition != 90) {          // Move only if not already in middle
      currentPosition = 90;
      servo.write(currentPosition);       // Move servo to the middle
      delay(1000);                         // Allow time for the servo to move
    }
  }

  delay(100); // Small delay for stability
}
