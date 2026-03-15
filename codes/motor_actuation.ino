#define A1 8
#define A2 9 
#define B1 10
#define B2 11 
#define ust3 6
#define use3 7

int steps[4][4] = {
    {HIGH, LOW, HIGH, LOW},
    {HIGH, LOW, LOW, HIGH},
    {LOW, HIGH, LOW, HIGH},
    {LOW, HIGH, HIGH, LOW}
};

// Thresholds
const float distanceThreshold = 100.0;  // cm
const float velocityThreshold = 100.0;   // cm/s

void setup() {
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
    pinMode(ust3, OUTPUT);
    pinMode(use3, INPUT);
    Serial.begin(9600);  // For debugging
}

void rotation() {
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        for (int i = 0; i < 4; i++) {
            digitalWrite(A1, steps[i][0]);
            digitalWrite(A2, steps[i][1]);
            digitalWrite(B1, steps[i][2]);
            digitalWrite(B2, steps[i][3]);
            delay(5);
        }
    }
}

void hold() {
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        digitalWrite(A1, HIGH);
        digitalWrite(A2, LOW);
        digitalWrite(B1, HIGH);
        digitalWrite(B2, LOW);
        delay(5);
    }
}

float ultrasonicSensor(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    return duration * 0.0343 / 2;
}

void tightenSeatbelt() {
    rotation();
    //hold();
}

float calculateVelocity(float initialDist, float finalDist, float timeInterval) {
    return (finalDist - initialDist) / timeInterval;
}

void loop() {
    float d3_initial = ultrasonicSensor(ust3, use3);  // Initial distance for front side
    delay(10);  // Short delay for velocity measurement
    float d3_final = ultrasonicSensor(ust3, use3);    // Final distance for front side

    // Calculate velocity (distance change over 10 ms = 0.01 seconds)
    float v3 = calculateVelocity(d3_initial, d3_final, 0.01);

    // Check condition for tightening the seatbelt
    if (d3_final < distanceThreshold && v3 > velocityThreshold) {
        tightenSeatbelt();
    }
}

