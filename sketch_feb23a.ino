#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Pins
#define SOUND_PIN 34
#define VIB_PIN 25


// Thresholds (you can tune)
#define FALL_THRESHOLD 1.1
#define SOUND_THRESHOLD 50

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  if(!mpu.testConnection())



  pinMode(VIB_PIN, INPUT);

  Serial.println("System Initializing...");
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected");
  } else {
    Serial.println("MPU6050 Connection Failed");
  }
}

void loop() {

  // -------- MODULE 1: DATA ACQUISITION --------
  
  int soundValue = analogRead(SOUND_PIN);
  int vibrationValue = digitalRead(VIB_PIN);


  int16_t ax, ay, az;
mpu.getAcceleration(&ax, &ay, &az);

Serial.print("AX: "); Serial.print(ax);
Serial.print(" AY: "); Serial.print(ay);
Serial.print(" AZ: "); Serial.println(az);

// -------- MODULE 2: PREPROCESSING --------

// Convert acceleration to g units
float ax_g = ax / 16384.0;
float ay_g = ay / 16384.0;
float az_g = az / 16384.0;

// Calculate magnitude
float accMagnitude = sqrt(ax_g*ax_g + ay_g*ay_g + az_g*az_g);



// Simple smoothing for sound
static int prevSound = 0;
int filteredSound = (prevSound + soundValue) / 2;
prevSound = soundValue;

  // -------- MODULE 3: AI / DECISION LOGIC --------
int riskScore = 0;

float delta = abs(accMagnitude - 1.0);

if(delta > 1.5)

if(accMagnitude > 1.5) riskScore += 2;
if(filteredSound > 100) riskScore += 1;
if(vibrationValue == 1) riskScore += 1;

String status = "SAFE";


if(riskScore >= 2) {
  status = "DANGER";

  }

  // -------- SIMPLE UI OUTPUT --------
Serial.print("SOUND:");
Serial.print(filteredSound);
Serial.print(",VIB:");
Serial.print(vibrationValue);
Serial.print(",ACC:");
Serial.print(accMagnitude);
Serial.print(",STATUS:");
Serial.println(status);

  delay(700);
}