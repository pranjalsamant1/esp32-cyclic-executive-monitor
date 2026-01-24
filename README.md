<p align="center">
  <img src="assets/images/architecture.png" alt="ESP32 Cyclic Executive Architecture" width="700">
</p>

<p align="center">
  <em>System architecture of the ESP32 cyclic executive monitor</em>
</p>

## ESP32 Cyclic Executive Monitor (Embedded Software)

An embedded systems project implementing a **cyclic-executive–style scheduler** on an ESP32 to execute a set of periodic real-time tasks.
The system performs digital waveform generation, frequency measurement, analog signal monitoring, and periodic serial logging without using an RTOS.

This project was developed as part of an **Embedded Software coursework** and focuses on deterministic, time-triggered execution.

---

## 📌 Project Overview

The goal of this project is to design and implement a simple **cyclic executive** that repeatedly executes a fixed set of periodic tasks with known timing constraints.

The system demonstrates:
- Deterministic task execution
- Polling-based I/O timing
- Basic real-time scheduling concepts
- Embedded signal monitoring and reporting

All functionality is implemented using standard Arduino/ESP32 APIs, without interrupts or an operating system.

---

## 🧠 Task Set Description

The system executes the following five tasks:

### Task 1 — Digital Output Waveform
- **Period:** 4 ms
- **Description:**
  Generates a precise timing pattern on a digital output pin:
  - HIGH for 200 µs
  - LOW for 50 µs
  - HIGH for 30 µs

This task demonstrates software-based microsecond timing control.

---

### Task 2 — Frequency Measurement (Input 1)
- **Period:** 20 ms
- **Input:** 3.3 V square wave (50% duty cycle)
- **Frequency Range:** 333 Hz – 1000 Hz
- **Method:** Polling-based measurement using `pulseIn()`

---

### Task 3 — Frequency Measurement (Input 2)
- **Period:** 8 ms
- **Input:** 3.3 V square wave (50% duty cycle)
- **Frequency Range:** 500 Hz – 1000 Hz
- **Method:** Polling-based measurement using `pulseIn()`

---

### Task 4 — Analog Input Monitoring
- **Period:** 20 ms
- **Input:** Potentiometer (0–3.3 V)
- **Processing:**
  - Computes a moving average of the last 4 samples
  - Activates an LED when the average exceeds half-scale

This task demonstrates basic signal filtering and threshold-based control.

---

### Task 5 — Serial Logging
- **Period:** 100 ms
- **Output:** Serial port at **9600 baud**
- **Format:**
  ```text
  freq_task2_scaled, freq_task3_scaled
  ```

Frequencies are scaled to a range of 0–99:
- Task 2: 333–1000 Hz → 0–99
- Task 3: 500–1000 Hz → 0–99

---

## ⏱️ Scheduling Approach

- Tasks are executed sequentially in the main loop.
- Execution time of each task is measured using `micros()`.
- The design follows a cyclic executive concept, where task periods and execution times are known in advance.
- Frame-based scheduling logic can be extended further if required.

This approach keeps the system simple and deterministic, suitable for small embedded real-time applications.

---

## 🔌 Pin Mapping (ESP32)

| Function | GPIO |
| --- | --- |
| Task 1 output LED | GPIO 4 |
| Task 2 frequency input | GPIO 14 |
| Task 3 frequency input | GPIO 25 |
| Potentiometer (ADC) | GPIO 15 |
| Threshold indicator LED | GPIO 2 |
| Serial baud rate | 9600 |

---

## 📂 Repository Structure

```text
arduino/
├── esp32_cyclic_executive_monitor.ino
├── B31DGMonitor.h
└── B31DGMonitor.cpp
```

- `esp32_cyclic_executive_monitor.ino` — Main application logic and task execution
- `B31DGMonitor.h` / `B31DGMonitor.cpp` — Supporting definitions and helper functionality

---

## ▶️ Build & Run (Arduino IDE)

1. Open the file:
   - `arduino/esp32_cyclic_executive_monitor.ino`
2. Select your ESP32 board and COM port.
3. Upload the program.
4. Open the Serial Monitor and set:
   - **9600 baud**

---

## 📈 Example Serial Output

```text
12,25
48,67
99,99
```

---

## 📝 Notes

- Frequency measurement is implemented using polling (`pulseIn()`), not interrupts.
- Execution time of each task is printed for debugging and timing analysis.
- The design can be extended to:
  - Enforce strict frame scheduling
  - Detect deadline overruns
  - Migrate to an RTOS-based solution for comparison

---

## 🚀 Future Improvements

- Implement a strict frame-based cyclic executive
- Add deadline miss detection and logging
- Visualize task schedule using a Gantt chart
- Compare cyclic executive vs RTOS scheduling

---

## 👤 Author

Pranjal Samant
Embedded Systems & Software
