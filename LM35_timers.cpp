#include <TimerOne.h> // Include TimerOne library

const int sensorPin = A0;  // Analog pin connected to LM35 sensor
const int ledPin = 13;     // Pin connected to onboard LED

volatile bool ledState = LOW; // Current state of the LED (LOW or HIGH)
const unsigned int blinkIntervalCold = 250; // Blink interval when temperature is below 30°C (ms)
const unsigned int blinkIntervalHot = 500;  // Blink interval when temperature is above 30°C (ms)

void setup() {
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  Timer1.initialize(blinkIntervalCold); // Initialize Timer1 with initial blink interval
  Timer1.attachInterrupt(toggleLED);   // Attach interrupt routine for LED control
  Timer1.start();                    // Start Timer1
}

void loop() {
  // Read analog voltage from sensor
  int sensorValue = analogRead(sensorPin);

  // Convert voltage to temperature in Celsius (assuming LM35 calibration)
  float temperature = sensorValue * 5.0 / 1023.0;

  // Check temperature and update blink interval
  if (temperature < 30) {
    Timer1.stop();                 // Stop Timer1
    Timer1.setPeriod(blinkIntervalCold); // Set Timer1 interval (cold)
    Timer1.start();                 // Restart Timer1
  } else {
    Timer1.stop();                 // Stop Timer1
    Timer1.setPeriod(blinkIntervalHot);  // Set Timer1 interval (hot)
    Timer1.start();                 // Restart Timer1
  }
}

void toggleLED() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}
