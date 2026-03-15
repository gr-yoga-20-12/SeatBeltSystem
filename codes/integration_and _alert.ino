// Pin Definitions
#define A1 8              // Stepper motor pins
#define A2 9
#define B1 10
#define B2 11
#define ust3 6            // Ultrasonic sensor trigger pin
#define use3 7            // Ultrasonic sensor echo pin
#define VIBRATION_SENSOR_PIN 2 // Vibration sensor pin

// Bluetooth via HC-05
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(4, 5); // RX, TX pins for HC-05 module

// Stepper Motor Step Sequence
int steps[4][4] = {
    {HIGH, LOW, HIGH, LOW},
    {HIGH, LOW, LOW, HIGH},
    {LOW, HIGH, LOW, HIGH},
    {LOW, HIGH, HIGH, LOW}
};

// Thresholds
const float distanceThreshold = 100.0;  // Distance threshold in cm

void setup() {
    // Pin Modes
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
    pinMode(ust3, OUTPUT);
    pinMode(use3, INPUT);
    pinMode(VIBRATION_SENSOR_PIN, INPUT);

    // Initialize Serial and Bluetooth
    Serial.begin(9600);           // For Serial Monitor
    bluetooth.begin(9600);        // For HC-05
    Serial.println("System Initialized...");
}

void rotateMotorForTenSeconds() {
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {  // Rotate for 10 seconds
        for (int i = 0; i < 4; i++) {
            digitalWrite(A1, steps[i][0]);
            digitalWrite(A2, steps[i][1]);
            digitalWrite(B1, steps[i][2]);
            digitalWrite(B2, steps[i][3]);
            delay(5);  // Adjust delay for motor speed
        }
    }
}

void holdMotorTorqueForTenSeconds() {
    unsigned long startTime = millis();
    // Hold the current position of the motor for 10 seconds
    while (millis() - startTime < 10000) {
        // Apply the last step position to keep the motor in torque hold
        digitalWrite(A1, HIGH);  // Hold position
        digitalWrite(A2, LOW);
        digitalWrite(B1, HIGH);
        digitalWrite(B2, LOW);
        delay(5);  // Adjust delay for motor holding torque
    }
}

float ultrasonicSensor(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    return duration * 0.0343 / 2;  // Convert duration to distance in cm
}

void loop() {
    // Measure distance from ultrasonic sensor
    float distance = ultrasonicSensor(ust3, use3);

    // Check if the object is within the threshold distance
    if (distance < distanceThreshold) {
        Serial.println("Object detected within threshold. Rotating motor...");
        rotateMotorForTenSeconds();  // Rotate the motor for 10 seconds

        // After rotating, hold the motor torque for 10 seconds
        holdMotorTorqueForTenSeconds();

        // Check vibration after motor rotation and holding torque
        int vibrationStatus = digitalRead(VIBRATION_SENSOR_PIN);
        if (vibrationStatus == HIGH) {  // If vibration is detected
            Serial.println("Vibration detected after motor rotation and holding.");
            if (distance < distanceThreshold) {
                // Send accident message
                bluetooth.println("A");
                Serial.println("Bluetooth message sent: Accident happened!");
            }
        } else {
            Serial.println("No vibration detected after motor rotation and holding.");
        }
    } else {
        Serial.println("No object detected within threshold.");
    }

    delay(100);  // Short delay for stability
}

