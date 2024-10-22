// Define the PWM pin connected to the motor controller
const int motorPin = 9; // You can change this to the pin you're using

void setup() {
  // put your setup code here, to run once:
  // Set the motor pin as an output
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Gradually increase the motor speed from 0V to 5V
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(motorPin, speed); // Write the PWM value to the motor
    delay(50); // Delay to control the speed of the increase
  }
  
  delay(5000); // Hold at full speed for 5 seconds

  // Gradually decrease the motor speed back to 0V
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(motorPin, speed); // Write the PWM value to the motor
    delay(50); // Delay to control the speed of the decrease
  }
  
  delay(2000); // Hold at 0 speed for 2 seconds
}
