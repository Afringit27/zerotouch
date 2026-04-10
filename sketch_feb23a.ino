#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

#define SOUND_PIN 34
#define VIB_PIN 25

void setup()
{
Serial.begin(115200);

Wire.begin();

mpu.initialize();

pinMode(VIB_PIN, INPUT);

Serial.println("System Ready");
}

void loop()
{

int soundValue = analogRead(SOUND_PIN);

int vibrationValue = digitalRead(VIB_PIN);

int16_t ax, ay, az;
mpu.getAcceleration(&ax, &ay, &az);

// convert to g
float ax_g = ax / 16384.0;
float ay_g = ay / 16384.0;
float az_g = az / 16384.0;

// magnitude
float accMagnitude = sqrt(ax_g*ax_g + ay_g*ay_g + az_g*az_g);

// smoothing sound
static int prevSound = 0;
int filteredSound = (prevSound + soundValue)/2;
prevSound = soundValue;

// AI decision logic
int riskScore = 0;

// sound condition
if(filteredSound > 150)
riskScore += 1;

// vibration condition
if(vibrationValue == 1)
riskScore += 1;

// acceleration condition
if(accMagnitude > 1.2)
riskScore += 1;

// heart rate condition (simulated)

// danger decision
String status="SAFE";

if(riskScore >= 1)
status="DANGER";

// output for python UI

Serial.print("SOUND:");
Serial.print(filteredSound);

Serial.print(",VIB:");
Serial.print(vibrationValue);

Serial.print(",ACC:");
Serial.print(accMagnitude);

Serial.print(",HR:");
Serial.print(75);

Serial.print(",STATUS:");
Serial.println(status);

delay(2000);
}
