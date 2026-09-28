# Arduino Line Follower Robot

A line follower robot developed as an academic final examination (UAS) project using Arduino Uno, three line tracking sensors, an L298N motor driver, and two DC motors.

## Features

- Three-sensor line detection
- PD-based line tracking control
- Sensor error calculation
- Differential motor speed control
- Pivot turning for sharp deviations
- Serial Monitor output for debugging

## Hardware

- Arduino Uno
- 3 line tracking sensors
- L298N motor driver
- 2 DC motors
- Robot chassis and supporting components

## Control Method

The robot uses proportional-derivative (PD) control to calculate motor correction from the detected line-position error.

```text
motorSpeed = (Kp × error) + (Kd × change in error)
```

The correction is then applied differentially to the two motors:

```text
speedA = speedBase + motorSpeed
speedB = speedBase - motorSpeed
```

## Main Parameters

```text
Kp = 35
Kd = 62
speedBase = 85
```

## Sensor and Motor Pins

The pin assignments are defined in `line_follower.ino`.

## Project Structure

```text
Arduino-Line-Follower/
├── line_follower.ino
├── README.md
└── images/
    └── robot.jpg
```

## Project Context

This project was developed as a UAS (final examination) project in 2026.

## Notes

The repository contains the Arduino source code used for the line follower robot. Hardware behavior may vary depending on sensor calibration, motor characteristics, battery condition, and track surface.
