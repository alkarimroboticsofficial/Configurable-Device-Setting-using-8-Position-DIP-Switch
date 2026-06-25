# 🌱 Configurable Device Setting using 8-Position DIP Switch

An ESP32-based **Hardware Configuration Interface** that reads binary parameters from an 8-position DIP switch array, converts the structural states into real-time decimal/hex values, and renders data parameters onto a 16x2 I2C LCD using custom pins 21 and 20.

---

## 📌 Project Overview

This project simulates industrial configuration architectures where **hardware device profiling**, **I2C address masking**, and **firmware option toggles** are configured locally using physical switches.  
The system scans the switch matrix state patterns dynamically without programmatic overhead.

- Flipping individual toggles dynamically shifts the compiled bit mask from `0` to `255`
- The system live-translates binary combinations into standard hardware profiles instantly

The system displays:

- Raw 8-bit binary word layouts (`00000000` to `11111111`)
- Mapped base-10 numerical representations (Decimal `0` to `255`)
- Equivalent hex values for low-level register configuration referencing (Hex `0x00` to `0xFF`)

on the 16x2 alphanumeric LCD framework.

---

## 🖼️ Circuit Diagram

![Circuit Diagram](circuit_diagram.png)

---

# 🛠️ Components Used

| Component                  | Quantity |
| -------------------------- | -------- |
| ESP32 Development Board    | 1        |
| 8-Position DIP Switch      | 1        |
| 16x2 I2C LCD Display Module| 1        |
| Jumper Wires & Breadboard  | As Required |

---

# ⚙️ Working Principle

1. The 8 separate toggles on the DIP switch are connected to dedicated digital input pins on the ESP32.
2. Pins are configured using internal `INPUT_PULLUP` resistor channels. When a switch is turned ON, it connects the pin directly to Ground ($0\text{V}$ / LOW logic).
3. The core system loop scans the array positions sequentially every 500 milliseconds.
4. Boolean state indicators invert the inputs to align with positive logic mapping (GND = `1`, Disconnected = `0`).
5. A binary weight accumulation calculation transforms individual bit arrays into a single composite byte integer.
6. The compiled values pass through base translation functions to yield decimal string structures.
7. Real-time updates send data packets across custom I2C master lines (`SDA=21, SCL=20`) to format rows on the alpha screen display matrix.

---

# 🔌 Pin Connections

Inputs rely entirely on internal microcontroller pull-ups. Connect one side of the switch array to the target GPIO pins, and tie the opposite parallel pin rail completely to Common GND.

## 8-Position DIP Switch Mapping Array

| DIP Position | ESP32 Target GPIO Pin | Binary Bit Weight Value |
| ------------ | -------------------- | ----------------------- |
| Position 1   | GPIO14               | $2^7 = 128$ (MSB)       |
| Position 2   | GPIO13               | $2^6 = 64$              |
| Position 3   | GPIO12               | $2^5 = 32$              |
| Position 4   | GPIO11               | $2^4 = 16$              |
| Position 5   | GPIO10               | $2^3 = 8$               |
| Position 6   | GPIO9                | $2^2 = 4$               |
| Position 7   | GPIO46               | $2^1 = 2$               |
| Position 8   | GPIO3                | $2^0 = 1$ (LSB)         |

---

## 16x2 I2C LCD Display Module

| LCD Hardware Pin | Power Line Connection Target | ESP32 Target Interface Pin |
| ---------------- | --------------------------- | ------------------------- |
| VCC              | 5V Power Distribution Rail  | 5V / Vin Power Pin        |
| GND              | Common Ground Return Rail   | System GND                |
| SDA              | Shared Data Line Interconnect | GPIO21                    |
| SCL              | Clock Synchronization Rail  | GPIO20                    |

---

# 💻 Features

- 8-bit parameter generation providing up to 256 unique hardware setting profiles
- Software-driven loop state evaluation removing floating pin data anomalies
- Custom-configured high-efficiency I2C bus footprints minimizing overall pin requirements
- Dynamic variable padding filtering visual row jitter or residual characters
- Highly adaptable configuration structure perfect for simulating addressable networking arrays

---

# 🧠 ESP32 Code Logic

The ESP32 performs the following tasks:

- Overrides system defaults to construct data pipelines across custom I2C channels 21 and 20
- Iterates arrays through compact loops to scan multiple inputs sequentially
- Executes bitwise binary operations (`1 << shift`) to calculate base byte strings
- Outputs diagnostic stream packets into the serial data line at 115200 baud
- Controls physical visual refresh states across the alphanumeric matrix array frames

---

# 📊 Binary Weight Masking Formula

The translation tracking individual switch pins ($S_i$) into a single output decimal index utilizes standard base-2 summation math models:

```math
Decimal\ Value \(= \sum_{i=0}^{7} S_i \times 2^\){(7-i)}
```

---

# 🚀 Installation Steps

1. Press the 8-Position DIP switch down firmly into the center trough layout of your breadboard.
2. Route the 8 target pin tracks cleanly into the assigned GPIO locations on your ESP32 board.
3. Bridge the opposite parallel pin side of the switch block completely to the system Ground (GND) rail.
4. Attach the I2C LCD display lines safely using custom ports GPIO21 and GPIO20.
5. Deploy the customized production source code to your ESP32 target memory block using the Arduino IDE.
6. Toggle individual switch pins to observe instant hex, decimal, and binary parameter changes on the fly.

---

# 📚 Required Libraries

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

Install the **LiquidCrystal_I2C** toolkit framework inside your active Arduino Library Manager utility panel.

---

# 🔮 Future Improvements

- Map switch combinations to execute distinct device subroutines (like altering motor speed steps or sensor profiles)
- Save configurations directly to the non-volatile EEPROM storage space using a confirmation button
- Stream the current profile settings over local server loops using native ESP32 Wi-Fi paths
- Introduce a parity bit validation check row to demonstrate hardware error corrections

---

# 🎯 Applications

- Manual I2C/SPI node device address assignment testing arrays
- Local multi-mode firmware parameter selection matrices
- Prototype security passcode verification inputs
- Educational training platforms demonstrating computer architecture binary systems

---

# 👨‍💻 Author

**Muhammad Zulqarnain**  
BS Intelligent Systems & Robotics

---

# 📄 License

This project is open-source and free to use for educational purposes.
