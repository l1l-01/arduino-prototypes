# Arduino Calculator with 4x4 Keypad and OLED Display

### Desciption
A simple calculator built using an Arduino Uno R4 Minima. It takes user input via a 4x4 matrix keypad and displays the operands, operators, and calculation results on a 0.96" I2C OLED display.

### Components Used
- Microcontroller: Arduino Uno R4 Minima
- Input: 4x4 Matrix Keypad
- Output: 0.96" I2C OLED Display 128x64 (SSD1306)

### Wiring / Connections
- 4x4 Matrix Keypad to Arduino Uno R4 Minima
| OLED Pin | Arduino Pin |
| --- | --- | 
| Row 1 | 9 |
| Row 2 | 8 |
| Row 3 | 7 |
| Row 4 | 6 |
| Column 1 | 5 |
| Column 2 | 4 |
| Column 3 | 3 |
| Column 4 | 2 |

- OLED Display (I2C) to Arduino Uno R4 Minima
Keypad Pin | Arduino Pin |
--- | --- | 
VCC\VDD | 5V (or 3.3V depending on your module) |
GND | GND |
SCL\SCK | Pin A5 |
SDA | Pin A4 |

### Required Libraries
- DIYables_Keypad
- Adafruit SSD1306
- Adafruit GFX Library

### How to Use
- Numbers (0-9): Type the first number (up to 5 digits).
- Operators:
| Key| Operation |
| --- | --- |
| A | Addition (+) |
| B | Subtraction (-) |
| * | Multiplication (*) |
| D | Division (/) |
- Equals: Press # to calculate and display the result.
- Clear: Press C to clear the screen and reset the calculator for a new calculation.
