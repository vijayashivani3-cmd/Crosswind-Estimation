
# Crosswind Estimation using MPU6050 & OLED Display

This project estimates **crosswind speed** using MPU6050 accelerometer data, applies a **low-pass filter** for noise reduction, and displays results on an **SSD1306 OLED** display.

The code uses a **simulated dataset** for testing, which can be replaced with real accelerometer readings from the MPU6050.

---

## 🚀 Features
- Reads raw X-axis acceleration from MPU6050.
- Implements a **low-pass filter** using exponential smoothing.
- Calculates approximate wind speed from filtered acceleration.
- Displays raw, filtered, and wind speed values on an OLED display.
- Provides real-time data output via Serial Monitor.

---

## 📦 Hardware Required
- **Arduino** (e.g., Uno, Nano, Mega)
- **MPU6050** Accelerometer + Gyroscope module
- **SSD1306 OLED display** (I²C)
- Connecting wires

---

## 🛠 Wiring
| Component  | Arduino Pin | Notes |
|------------|-------------|-------|
| OLED SDA   | A4          | I²C Data |
| OLED SCL   | A5          | I²C Clock |
| MPU SDA    | A1 (SoftwareWire) | Custom I²C SDA |
| MPU SCL    | A2 (SoftwareWire) | Custom I²C SCL |
| VCC (OLED & MPU) | 5V/3.3V     | Match module specs |
| GND        | GND         | Common ground |
