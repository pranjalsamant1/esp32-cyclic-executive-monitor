#include <Arduino.h>
#include <Ticker.h>

// Please Define correct pins here, super important!!!
#define led_1 4

int wave_1 = 14;
int wave_2 = 25;

const int poten_pin = 15;
int poten_led = 2;

// Variables for task 2 and 3.
int highTime_1 = 0;
int lowTime_1  = 0;
float period_1 = 0.0f;
float freq_1   = 0.0f;

int highTime_2 = 0;
int lowTime_2  = 0;
float period_2 = 0.0f;
float freq_2   = 0.0f;

// Variables for Task 4
float avg = 0.0f;
float max_1 = 3.3f / 2.0f;
float poten_value = 0.0f;
float func_val = 0.0f;
float p1 = 0.0f, p2 = 0.0f, p3 = 0.0f, p4 = 0.0f;

// Frame and schduling done here.
static const uint32_t frame_us = 4000UL;      // 4 ms frame
static const uint32_t major_frames = 50;      // 200 ms / 4 ms
volatile uint32_t frameCounter = 0;

Ticker ticker;

// helpers
static inline int clamp99(int v) {
  if (v < 0) return 0;
  if (v > 99) return 99;
  return v;
}

// keeping pulse bounded here.
static const uint32_t PULSE_TIMEOUT_US = 3500UL;

// all given tasks below in order from 1 to 5.
void JobTask1() {
  digitalWrite(led_1, HIGH);
  delayMicroseconds(200);
  digitalWrite(led_1, LOW);
  delayMicroseconds(50);
  digitalWrite(led_1, HIGH);
  delayMicroseconds(30);
  digitalWrite(led_1, LOW);
}

void JobTask2() {
  highTime_1 = (int)pulseIn(wave_1, HIGH, PULSE_TIMEOUT_US);
  lowTime_1  = (int)pulseIn(wave_1, LOW,  PULSE_TIMEOUT_US);

  if (highTime_1 > 0 && lowTime_1 > 0) {
    period_1 = (float)(highTime_1 + lowTime_1);
    freq_1 = 1000000.0f / period_1;
  } else {
    freq_1 = 0.0f;
  }
}

void JobTask3() {
  highTime_2 = (int)pulseIn(wave_2, HIGH, PULSE_TIMEOUT_US);
  lowTime_2  = (int)pulseIn(wave_2, LOW,  PULSE_TIMEOUT_US);

  if (highTime_2 > 0 && lowTime_2 > 0) {
    period_2 = (float)(highTime_2 + lowTime_2);
    freq_2 = 1000000.0f / period_2;
  } else {
    freq_2 = 0.0f;
  }
}

void JobTask4() {
  poten_value = (float)analogRead(poten_pin);
  func_val = (3.3f * poten_value) / 4095.0f;

  p1 = p2; p2 = p3; p3 = p4; p4 = func_val;
  avg = (p1 + p2 + p3 + p4) * 0.25f;

  digitalWrite(poten_led, (avg > max_1) ? HIGH : LOW);
}

void JobTask5() {
  int s1 = (int)(((freq_1 - 333.0f) * 99.0f) / (1000.0f - 333.0f));
  int s2 = (int)(((freq_2 - 500.0f) * 99.0f) / (1000.0f - 500.0f));

  s1 = clamp99(s1);
  s2 = clamp99(s2);

  Serial.printf("%d,%d\r\n", s1, s2);
}

// Frame for cyclic executive
void frame() {
  const uint32_t slot = frameCounter % major_frames;

  // 4 ms frame schedule:
  // Task1: it is every 4ms, every frame.
  // Task2: it is every 20ms, every 5 frames.
  // Task3: it is every 8ms, every 2 frames.
  // Task4: it is every 20ms, every 5 frames.
  // Task5: it is every 100ms, every 25 frames.

  JobTask1();

  if ((slot % 2) == 0) {
    JobTask3();
  }

  if ((slot % 5) == 0) {
    JobTask2();
  }

  if ((slot % 5) == 2) {
    JobTask4();
  }

  if ((slot % 25) == 0) {
    JobTask5();
  }

  frameCounter++;
}

// Arduino Setup Here.
void setup() {
  Serial.begin(9600);

  pinMode(led_1, OUTPUT);
  pinMode(wave_1, INPUT);
  pinMode(wave_2, INPUT);

  pinMode(poten_led, OUTPUT);
  pinMode(poten_pin, INPUT);

  ticker.attach_us(frame_us, frame);
}

void loop() {
  
}
