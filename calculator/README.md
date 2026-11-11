# Arduino Calculator with 4x4 Keypad, OLED Display, and Audible Feedback

### Description
A simple calculator built using an Arduino Uno R4 Minima. It takes user input via a 4x4 matrix keypad, displays the operands, operators, and calculation results on a 0.96" I2C OLED display, and provides audible keypress feedback via a buzzer.

### Components Used
- Microcontroller: Arduino Uno R4 Minima
- Input: 4x4 Matrix Keypad
- Output (Visual): 0.96" I2C OLED Display 128x64 (SSD1306)
- Output (Audible): Passive or Active Buzzer (5V)

### Wiring / Connections

#### 4x4 Matrix Keypad to Arduino Uno R4 Minima
| Keypad Pin | Arduino Pin |
| --- | --- | 
| Row 1 | 9 |
| Row 2 | 8 |
| Row 3 | 7 |
| Row 4 | 6 |
| Column 1 | 5 |
| Column 2 | 4 |
| Column 3 | 3 |
| Column 4 | 2 |

#### OLED Display (I2C) to Arduino Uno R4 Minima
| OLED Pin | Arduino Pin |
| --- | --- | 
| VCC or VDD | 5V (or 3.3V depending on your module) |
| GND | GND |
| SCL or SCK| Pin A5 |
| SDA | Pin A4 |

#### Buzzer to Arduino Uno R4 Minima
| Buzzer Pin | Arduino Pin |
| --- | --- | 
| Positive (+) | Pin 11 |
| Negative (-) | GND |

### Required Libraries
- `DIYables_Keypad`
- `Adafruit SSD1306`
- `Adafruit GFX Library`

### How to Use
- **Numbers (0-9)**: Type the first number (up to 5 digits).
- **Operators**:

| Key | Operation |
| --- | --- |
| A | Addition (+) |
| B | Subtraction (-) |
| * | Multiplication (*) |
| D | Division (/) |

- **Equals**: Press `#` to calculate and display the result. The result is automatically stored as the first input for chained calculations.
- **Clear**: Press `C` to clear the screen, reset the state variables, and prepare for a new calculation.
- **Audible Feedback**: A short 2000Hz beep (100ms duration) is generated on every valid keypress to confirm input registration.
