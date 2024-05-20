#include <Unistep2.h>

#include <Arduino.h>
#include <BasicEncoder.h>

const int8_t pinA = 2;
const int8_t pinB = 3;

Unistep2 stepper(8, 9, 10, 11, 4096, 1000);// IN1, IN2, IN3, IN4, 總step數, 每步的延遲(in micros)
BasicEncoder encoder(pinA, pinB);
int motorStep=0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Polling in loop()"));
  stepper.run();  //步進機啟動
}

void loop() {
  encoder.service();
  int encoder_change = encoder.get_change();
  if (encoder_change) {
    motorStep =encoder.get_count();
    Serial.println(motorStep);
  } 

  if (motorStep > 0) {
    stepper.move(4096 * motorStep); 
  }
}
