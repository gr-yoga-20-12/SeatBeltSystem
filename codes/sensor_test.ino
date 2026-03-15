#include <LiquidCrystal.h>

#define trg A0
#define ech A1

int dis = 0;
int t = 0;
int x[2]; // distance
int dx = 0; // delta dist
int tim[2]; // time
double dt = 0; // delta time
int v = 0; // speed
int s = 0; // step condition
int coun = 0; // time

void setup() {
  Serial.begin(9600);
  pinMode(trg, OUTPUT);
  pinMode(ech, INPUT);
}

void loop() {
  digitalWrite(trg, LOW);
  delayMicroseconds(5);
  digitalWrite(trg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trg, LOW);
  t = pulseIn(ech, HIGH);
  dis = t / 57;
  dis = (dis * .975) + 1; // Calibration factor for distance

  if (s < 2) {
    x[0] = dis;
  } else {
    x[1] = dis;
  }
  v = 1000 * dx / dt;

  // Display warning message based on distance
  if (dis < 10) {
    Serial.println("Warning: Object too close");
  } else {
    Serial.println("Clear");
  }

  coun = millis();
  dx = x[0] - x[1];
  dx = abs(dx); // absolute delta of distance

  /* Result print */
  Serial.print("Distance: ");
  Serial.print(dis);
  Serial.print(" cm ");

  if (s == 0) {
  } 
  else if (s == 1) {
  }

  if (s % 2) {
    tim[0] = coun;
  } else {
    tim[1] = coun;
  }

  dt = abs(tim[0] - tim[1]);
  dt = abs(dt) * 0.001; // absolute delta of time in seconds

  if (dt != 0) { // avoid division by zero
    v = dx / dt; // Calculate speed
    Serial.print("Speed: ");
    Serial.print(v);
    Serial.println(" cm/s");
  }

  delay(1000);
  coun = millis();
}

