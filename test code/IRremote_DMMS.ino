#include <IRremote.h>  // Include the IRremote library

int RECV_PIN = 9;  // Pin connected to the IR receiver
IRrecv irrecv(RECV_PIN);  // Create an IRrecv object

int OUTPUT_MOTOR = 10; // Pin that will be used for PWM for motor control
int OUTPUT_UV = 11; // Pin that will be used for PWM for UV light

// Define button codes for toggling, increasing, and decreasing motor speed
uint64_t TOGGLE_MOTOR = 0xBC43FF00; // Button to toggle motor ON/OFF
uint64_t INCREASE_MOTOR_SPEED = 0xBF40FF00; // Button to increase motor speed
uint64_t DECREASE_MOTOR_SPEED = 0xBB44FF00; // Button to decrease motor speed

// Define button codes for toggling, increasing, and decreasing brightness for UV light
uint64_t TOGGLE_UV = 0xF609FF00; // Button to toggle UV light ON/OFF
uint64_t INCREASE_UV_BRIGHTNESS = 0xEA15FF00; // Button to increase brightness for UV light
uint64_t DECREASE_UV_BRIGHTNESS = 0xF807FF00; // Button to decrease brightness for UV light

// Variables to manage state and brightness
bool pinState_1 = false; // false = OFF, true = ON for motor
bool pinState_2 = false; // false = OFF, true = ON for UV light
int motor_speed = 15; // Speed for motor (15-255)
int uv_brightness = 15; // Brightness level for UV light (15-255)

void setup() {
  Serial.begin(9600);  // Initialise serial communication at 9600 bps
  irrecv.enableIRIn(); // Start the IR receiver
  pinMode(OUTPUT_MOTOR, OUTPUT); // Set OUTPUT_MOTOR as an output
  pinMode(OUTPUT_UV, OUTPUT); // Set OUTPUT_UV as an output
  digitalWrite(OUTPUT_MOTOR, LOW); // Ensure motor is off initially
  digitalWrite(OUTPUT_UV, LOW); // Ensure UV light is off initially
}

void loop() {
  if (irrecv.decode()) {  // Check if an IR signal is received
    Serial.print("IR Code: ");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);  // Print the decoded value in hex

    // Check if the received code matches the toggle button for motor
    if (irrecv.decodedIRData.decodedRawData == TOGGLE_MOTOR) {
      pinState_1 = !pinState_1; // Toggle the state for motor
      digitalWrite(OUTPUT_MOTOR, pinState_1 ? HIGH : LOW); // Set pin 10 based on pinState_1
      analogWrite(OUTPUT_MOTOR, pinState_1 ? motor_speed : 0); // Maintain speed if turned on
      Serial.println(pinState_1 ? "Motor turned ON" : "Motor turned OFF");
    }
    // Check if the received code matches the increase speed button for the motor
    else if (irrecv.decodedIRData.decodedRawData ==INCREASE_MOTOR_SPEED) {
      if (pinState_1) { // Only change speed if motor is ON
        motor_speed = min(motor_speed + 15, 255); // Increase speed, max 255
        analogWrite(OUTPUT_MOTOR, motor_speed); // Set the new speed
        Serial.print("Motor speed increased to: ");
        Serial.println(motor_speed);
      }
    }
    // Check if the received code matches the decrease speed button for the motor
    else if (irrecv.decodedIRData.decodedRawData == DECREASE_MOTOR_SPEED) {
      if (pinState_1) { // Only change speed if motor is ON
        motor_speed = max(motor_speed - 15, 15); // Decrease speed, min 15
        analogWrite(OUTPUT_MOTOR, motor_speed); // Set the new speed
        Serial.print("Motor speed decreased to: ");
        Serial.println(motor_speed);
      }
    }

    // Check if the received code matches the toggle button for the UV light
    else if (irrecv.decodedIRData.decodedRawData == TOGGLE_UV) {
      pinState_2 = !pinState_2; // Toggle the state for UV light
      digitalWrite(OUTPUT_UV, pinState_2 ? HIGH : LOW); // Set pin 11 based on pinState_2
      analogWrite(OUTPUT_UV, pinState_2 ? uv_brightness : 0); // Maintain brightness if turned on
      Serial.println(pinState_2 ? "UV light turned ON" : "UV light turned OFF");
    }
    // Check if the received code matches the increase brightness button for the UV light
    else if (irrecv.decodedIRData.decodedRawData == INCREASE_UV_BRIGHTNESS) {
      if (pinState_2) { // Only change brightness if UV light is ON
        uv_brightness = min(uv_brightness + 15, 255); // Increase brightness, max 255
        analogWrite(OUTPUT_UV, uv_brightness); // Set the new brightness level
        Serial.print("UV brightness increased to: ");
        Serial.println(uv_brightness);
      }
    }
    // Check if the received code matches the decrease brightness button for the UV light
    else if (irrecv.decodedIRData.decodedRawData == DECREASE_UV_BRIGHTNESS) {
      if (pinState_2) { // Only change brightness if UV light is ON
        uv_brightness = max(uv_brightness - 15, 15); // Decrease brightness, min 15
        analogWrite(OUTPUT_UV, uv_brightness); // Set the new brightness level
        Serial.print("LED 2 brightness decreased to: ");
        Serial.println(uv_brightness);
      }
    }

    irrecv.resume();  // Prepare to receive the next value
  }
}