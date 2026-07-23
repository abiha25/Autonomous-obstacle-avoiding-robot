# Wiring Notes — Autonomous Obstacle-Avoiding Robot

Detailed pin mapping, power distribution, and bill of materials to accompany the main circuit diagram.

## Bill of Materials (BOM)

| # | Component | Qty | Notes |
|---|---|---|---|
| 1 | Arduino Uno | 1 | Main controller |
| 2 | L298N Dual H-Bridge Motor Driver | 1 | Drives both DC motors |
| 3 | DC Gear Motor (3–6V) | 2 | Left & right wheels |
| 4 | HC-SR04 Ultrasonic Sensor | 1 | Front obstacle detection |
| 5 | SG90 Micro Servo Motor | 1 | Sweeps the ultrasonic sensor left/right |
| 6 | 12V Battery Pack | 1 | Powers the L298N motor supply |
| 7 | SPST Toggle/Rocker Switch | 1 | Main power on/off |
| 8 | Robot Chassis + Wheels | 1 set | Mounting platform |
| 9 | Jumper Wires (M-M, M-F) | Assorted | Signal & power connections |
| 10 | USB Cable | 1 | Programming / optional Arduino power |

## Arduino Uno Pin Mapping

| Signal | Arduino Pin | Connects To |
|---|---|---|
| Servo signal | D7 | SG90 servo signal wire |
| Ultrasonic Trig | D3 | HC-SR04 Trig |
| Ultrasonic Echo | D6 | HC-SR04 Echo |
| Motor Driver IN1 (T1) | D11 | L298N IN1 |
| Motor Driver IN2 (T2) | D10 | L298N IN2 |
| Motor Driver IN3 (T3) | D9 | L298N IN3 |
| Motor Driver IN4 (T4) | D8 | L298N IN4 |
| GND | GND | Common ground — Arduino, L298N, HC-SR04, servo |

> Motor driver ENA/ENB enable pins are not software-controlled in this build (jumpered high) — motors run at fixed speed. See "Future Improvements" in the main README for PWM speed control.

## L298N Motor Driver Wiring

| L298N Terminal | Connects To |
|---|---|
| OUT1 / OUT2 | Left DC motor |
| OUT3 / OUT4 | Right DC motor |
| 12V | Positive terminal of 12V battery pack (via toggle switch) |
| GND | Battery negative **and** Arduino GND (shared ground) |
| 5V (out) | Not used to power Arduino in this build |
| IN1–IN4 | Arduino D11, D10, D9, D8 (see table above) |

## Power Distribution

- **Motors + L298N:** powered directly from the 12V battery pack, switched through the toggle switch.
- **Arduino Uno:** powered separately via USB (during testing) or Vin.
- **Servo + HC-SR04:** powered from the Arduino 5V and GND pins.
- **Critical:** all GND lines (battery, L298N, Arduino, sensor, servo) must be tied together for the circuit to function correctly — this is the most common source of erratic behavior if missed.

## Motor Direction Logic Reference

For quick reference when debugging, this is how the direction pins map to movement in the code:

| Function | T1 (D11) | T2 (D10) | T3 (D9) | T4 (D8) |
|---|---|---|---|---|
| `forward()` | LOW | HIGH | LOW | HIGH |
| `backward()` | HIGH | LOW | HIGH | LOW |
| `turnLeft()` | HIGH | LOW | LOW | LOW |
| `turnRight()` | LOW | LOW | HIGH | LOW |
| `stopCar()` | LOW | LOW | LOW | LOW |

If left/right feels reversed on your physical build, swap the motor's two output wires on the L298N terminal rather than editing the code.
