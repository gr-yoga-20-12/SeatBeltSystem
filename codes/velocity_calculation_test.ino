#define ust3 9
#define use3 10

// Thresholds
const float distanceThreshold = 100.0;  // cm
const float velocityThreshold = 100.0; // cm/s

void setup() 
{
    pinMode(ust3, OUTPUT);
    pinMode(use3, INPUT);
    Serial.begin(9600); 
}

float ultrasonicSensor(int triggerPin, int echoPin) 
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    return duration * 0.0343 / 2; // Convert time to distance in cm
}

float calculateVelocity(float initialDist, float finalDist, float timeInterval) 
{
    return (finalDist - initialDist) / timeInterval;
}

void loop() 
{
    // Take the initial distance
    float d3_initial = ultrasonicSensor(ust3, use3);
    unsigned long time1 = millis();

    // Add a small delay to allow meaningful time difference
    delay(500); // 500 ms delay

    // Take the final distance
    float d3_final = ultrasonicSensor(ust3, use3);
    unsigned long time2 = millis();

    // Calculate time interval in seconds
    float timeInterval = (time2 - time1) / 1000.0; // Convert ms to seconds

    // Calculate velocity
    float v3 = calculateVelocity(d3_initial, d3_final, timeInterval);

    // Print the results
    Serial.print("distance = ");
    Serial.print(d3_final);
    Serial.println(" cm");

    Serial.print("speed = ");
    Serial.print(v3);
    Serial.println(" cm/s");

    // Check thresholds

    delay(500);
}


