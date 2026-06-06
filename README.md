# Self-Balancing Robot

A two-wheeled self-balancing robot implemented with PID control, demonstrating practical application of inverted pendulum control theory using Arduino, MPU6050 IMU sensor, and L298N motor driver.

## Overview

This project implements a real-time feedback control system that maintains a two-wheeled robot in an upright position. The system continuously measures tilt angle using an MPU6050 sensor and adjusts motor torque via PID control to keep the robot balanced against gravity and external disturbances.

**Project Status:** ✅ Completed — Achieved 5+ seconds of continuous balance with optimized PID tuning.

## Team

- **Mahim Yadav** (2023UEE0142)
- **Saksham Vijay** (2023UEE0150)

Department of Electrical Engineering, Indian Institute of Technology Jammu

## Key Features

- **PID-Based Stabilization:** Proportional-integral-derivative control for dynamic balance
- **IMU Feedback:** 100 Hz tilt measurement with MPU6050 sensor
- **Real-Time Control Loop:** 6.2 ms average execution time per cycle
- **Robust Disturbance Rejection:** 0.8s recovery from 15° external push
- **Optimized Gains:** Empirically tuned parameters (Kp=80, Ki=200, Kd=1)
- **Hardware Troubleshooting:** Comprehensive solutions for common integration challenges

## Hardware Requirements

### Bill of Materials

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Microcontroller |
| MPU6050 Sensor | 1 | 6-axis IMU (accelerometer + gyroscope) |
| L298N Motor Driver | 1 | Dual H-bridge for motor control |
| BO Gear Motors | 2 | 200 RPM DC motors with gearbox |
| Wheels | 2 | ~6.5 cm diameter |
| Li-ion Battery Cells | 2 | 2S configuration (7.4V nominal) |
| Battery Holder | 2 | For 2S Li-ion cells |
| Chassis Material | 1 Set | Acrylic or 3D-printed |
| Jumper Wires | 1 Set | Breadboard and sensor connections |

**Total Cost:** ~₹3,500-4,500 (India pricing)

## Circuit Connections

### Arduino Pinout

**MPU6050 (I2C Interface):**
- SDA → A4
- SCL → A5
- VCC → 5V
- GND → GND

**L298N Motor Driver:**
- ENA → D11 (PWM)
- ENB → D9 (PWM)
- IN1 → D12
- IN2 → D13
- IN3 → D6
- IN4 → D7
- OUT1, OUT2 → Motor A
- OUT3, OUT4 → Motor B
- +12V → 7.4V Battery
- GND → Common ground

**Power:**
- Arduino Vin → 7.4V Li-ion battery
- L298N +12V → 7.4V Li-ion battery
- Common GND for Arduino, motor driver, and sensors

### Connection Schematic

```
    [7.4V Li-ion Battery]
           |
    -------|-------
    |             |
[Arduino Vin]  [L298N +12V]
    |             |
    |        [Motor Driver]
    |        /    |    \
   MPU6050  M_A  M_B  Control Pins
   (I2C)
```

## Software Architecture

### Control Algorithm

**Discrete-time PID Controller (Δt = 10 ms):**

```
u[k] = Kp * e[k] + Ki * Σ(e[j] * Δt) + Kd * (e[k] - e[k-1]) / Δt
```

Where:
- `e[k]` = tilt error (radians)
- `u[k]` = motor PWM command [0-255]
- `Kp` = proportional gain
- `Ki` = integral gain
- `Kd` = derivative gain

**Control Loop Frequency:** 100 Hz (10 ms sampling period)

### Key Software Components

1. **IMU Data Acquisition:** DMP-based tilt angle extraction from MPU6050
2. **Error Computation:** Vertical reference (0°) vs. measured angle
3. **PID Calculation:** Real-time gain computation with anti-windup
4. **Motor Actuation:** PWM mapping to motor direction and speed
5. **Feedback:** Millisecond-level response for fast pendulum dynamics

## Tuning Guide

### Optimal Configuration

| Parameter | Value | Justification |
|-----------|-------|---------------|
| **Kp** | 80 | Immediate correction without oscillation |
| **Ki** | 200 | Eliminates drift, avoids integral windup |
| **Kd** | 1 | Damping without amplifying sensor noise |

### Tuning Process

1. **Start Conservative:** Kp=40, Ki=0, Kd=0 (proportional only)
2. **Increase Kp:** Incrementally raise until sustained oscillation (~60-80 range)
3. **Add Integral:** Increase Ki to eliminate drift (180-220 range)
4. **Fine-Tune Derivative:** Add small Kd (0.5-2) for damping
5. **Test Disturbances:** Push robot gently to verify recovery

### Sensitivity Analysis

| Effect | Kp Too Low | Kp Too High | Ki Too Low | Ki Too High | Kd Too High |
|--------|-----------|------------|-----------|------------|------------|
| Behavior | Falls slowly | Oscillates violently | Drift accumulates | Windup overshoot | Sensor noise amplified |
| Solution | Increase Kp | Decrease Kp | Increase Ki | Decrease Ki | Decrease Kd |

## Performance Metrics

### Experimental Results (Optimal Configuration)

| Metric | Value | Notes |
|--------|-------|-------|
| **Balance Duration** | 5+ seconds | Continuous upright position |
| **Steady-State Error** | ±1.5° | Oscillation around vertical |
| **Disturbance Recovery** | 0.8 s | From 15° push, 2 oscillation cycles |
| **Control Loop Frequency** | 100 Hz | 10 ms sampling period |
| **Execution Time** | 6.2 ms avg | <10 ms per cycle |
| **Sensor Update Rate** | 100 Hz | MPU6050 output |

## Integration Challenges & Solutions

### Challenge 1: MPU6050 I2C Communication Failure

**Problem:** I2C bus hangs, sensor unresponsive
- **Root Cause:** Missing pull-up resistors, bus contention
- **Solution:** Add 4.7kΩ pull-ups to SDA/SCL; reduce I2C clock to 100kHz

### Challenge 2: Motor Overheating

**Problem:** Motors burn out after 2-3 minutes
- **Root Cause:** Continuous high-current draw at low speed
- **Solution:** Implement `MIN_ABS_SPEED` threshold (30/255 PWM minimum); add thermal cutoff

### Challenge 3: Arduino Pin Failure

**Problem:** Digital pins become unresponsive after soldering
- **Root Cause:** Excessive heat during soldering; solder bridges
- **Solution:** Use hot-air rework station; test continuity before assembly

### Challenge 4: Sensor Burnout During Soldering

**Problem:** MPU6050 damaged during assembly
- **Root Cause:** High soldering temperature, prolonged heat exposure
- **Solution:** Use pre-soldered breakout boards; employ flux to reduce heat

### Challenge 5: Motor Asymmetry

**Problem:** Robot drifts left/right despite balanced control
- **Root Cause:** Mechanical differences in motors, gearbox wear, wheel imbalance
- **Solution:** Implement software calibration factor (~0.8 scaling on slower motor)

## Mechanical Design

### Chassis Considerations

- **Center-of-Mass Height:** Elevated above wheel axis for restoring torque
- **Motor Mounts:** Reinforced to reduce vibration coupling into IMU
- **IMU Placement:** Centered and isolated from vibration sources
- **Battery Position:** Above wheel axis for moment arm advantage
- **Wheel Size:** ~6.5 cm diameter; consistent hardness for traction


## Getting Started

### Prerequisites

- Arduino IDE (1.8.x or higher)
- MPU6050 library: [Jeff Rowberg's I2CDev Library](https://github.com/jrowberg/i2cdevlib)
- L298N motor driver (no library needed)
- USB cable for Arduino programming

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Sakshamvijay-078/self_balancing_robot.git
   cd self_balancing_robot
   ```

2. **Install Arduino Libraries:**
   - Open Arduino IDE → Sketch → Include Library → Manage Libraries
   - Search and install: `MPU6050` by Jeff Rowberg
   - Alternatively, download from: https://github.com/jrowberg/i2cdevlib/Arduino

3. **Upload Firmware:**
   - Connect Arduino Uno via USB
   - Open `firmware/self_balancing_robot.ino`
   - Select Board: Arduino Uno, Port: COM3 (or your port)
   - Click Upload

4. **Hardware Assembly:**
   - Follow circuit diagram in `/schematics/`
   - Solder MPU6050 and L298N breakout boards
   - Connect motors to L298N outputs
   - Test all connections with multimeter

5. **Initial Testing:**
   - Power on via 7.4V battery
   - Monitor Serial output (9600 baud) for sensor readings
   - Verify motor response to tilting motions

### Basic Usage

```cpp
// Configuration constants (adjust for your hardware)
const float Kp = 80;      // Proportional gain
const float Ki = 200;     // Integral gain
const float Kd = 1;       // Derivative gain
const float dt = 0.01;    // Control loop period (10 ms)

// Initialization
void setup() {
  initializeMPU6050();
  initializeMotorPins();
}

// Main control loop runs at 100 Hz
void loop() {
  float tilt = readTiltAngle();
  float error = 0 - tilt;  // Error from vertical
  float pidOutput = computePID(error);
  setMotorSpeed(pidOutput);
}
```

## Experimental Results

### PID Tuning Trials

| Trial | Kp | Ki | Kd | Balance (sec) | Remarks |
|-------|----|----|----|----|---------|
| 1 | 40 | 100 | 1 | 0-1 | Insufficient torque, falls |
| 2 | 80 | 100 | 1 | 0-1 | Stable but drift present |
| 3 | 80 | 270 | 1 | 1-2 | Integral windup, violent oscillation |
| 4 | 80 | 200 | 5 | 2-3 | Derivative noise amplified |
| **5** | **80** | **200** | **1** | **500+** | **✅ Optimal: 5+ sec stable** |
| 6 | 120 | 200 | 1 | 4-5 | Excessive oscillation |
| 7 | 60 | 200 | 1 | 2-3 | Slow recovery |

## Theory Reference

### Inverted Pendulum Dynamics

For small-angle approximation (linearized):

```
θ̈ = (g/L)θ - u / ((M+m)L)
```

Where:
- θ = tilt angle (radians)
- L = center-of-mass height (meters)
- g = 9.81 m/s²
- M = body mass
- m = wheel mass
- u = motor torque (input)

This is an **unstable system** (poles at ±√(g/L)) requiring active feedback control.

### Theoretical vs. Experimental

| Metric | Theoretical | Experimental | Reason for Deviation |
|--------|-----------|-------------|----------------------|
| Stability | Indefinite | 5 s | Unmodeled friction, sensor noise |
| Recovery | Instantaneous | 0.8 s | Motor inertia, I2C latency |
| Steady-State Error | 0° | ±1.5° | Finite sampling, quantization |

## Troubleshooting

### Robot Falls Immediately

- Check battery voltage (minimum 6.8V required)
- Verify motor direction (should push robot away from tilt)
- Increase Kp gradually (start from 40)
- Ensure MPU6050 is calibrated (run calibration routine)

### Continuous Oscillation

- Reduce Kp (excessive proportional gain)
- Reduce Ki (integral windup)
- Increase Kd slightly for damping

### Sensor Drift

- Verify MPU6050 I2C pull-ups (4.7kΩ)
- Check sensor orientation (Y-axis should measure tilt)
- Recalibrate gyroscope offset after power cycle

### Motors Not Responding

- Test PWM output with multimeter
- Verify motor direction pins (IN1, IN2, etc.)
- Check motor power connections
- Test motors independently with battery

### Asymmetric Balancing

- Measure motor speeds independently
- Apply software calibration factor to slower motor
- Check wheel diameter consistency
- Verify gear mesh alignment

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit changes with clear messages
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request with detailed description

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Dr. Nalin Kumar Sharma** — Project supervisor, Control Systems Lab
- **Jeff Rowberg** — I2C/MPU6050 libraries
- **IIT Jammu Electrical Engineering Department** — Lab resources and mentorship
- **InvenSense Inc.** — MPU6050 technical documentation

## References

1. Ogata, K. (2010). *Modern Control Engineering* (5th ed.). Prentice Hall.
2. Nise, N. S. (2015). *Control Systems Engineering* (7th ed.). Wiley.
3. Ziegler, J. G., & Nichols, N. B. (1942). Optimum Settings for Automatic Controllers. *Trans. ASME*, 64, 759-768.
4. MPU6050 Product Specification. InvenSense Inc., 2013.
5. Arduino PID Library. Brett Beauregard. https://github.com/br3ttb/Arduino-PID-Library
6. Control Systems Project Manual (2025-26). Dept. of Electrical Eng., IIT Jammu.


## Contact & Support

For questions or issues:
- Open an [GitHub Issue](https://github.com/Sakshamvijay-078/self_balancing_robot/issues)
- Contact: 2023uee0150@iitjammu.ac.in

---

**Last Updated:** November 2025  
**Project Status:** ✅ Complete — Ready for deployment and further optimization
