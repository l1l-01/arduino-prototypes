// Include necessary libraries for keypad, communication, and OLED display
#include <DIYables_Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>

// OLED Display configuration macros
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Hardware pin assignments
const uint8_t BUZZER_PIN = 11; // Pin 11 used for buzzer

// Keypad matrix dimensions
const int ROW_NUM = 4;    // four rows
const int COLUMN_NUM = 4; // four columns

// Keymap defining the physical layout of the 4x4 keypad
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Pin mappings for keypad rows and columns
byte pin_rows[ROW_NUM] = { 9, 8, 7, 6 };      // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 5, 4, 3, 2 }; // connect to the column pinouts of the keypad

// Initialize the keypad object with the keymap and pin configurations
DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// Initialize the OLED display object using I2C (Wire)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Configure buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    // Halt execution in an infinite loop if display initialization fails
    for(;;);
  }

  display.clearDisplay(); // Clear the display buffer
  noTone(BUZZER_PIN);     // Ensure buzzer is silent at startup
}

// Calculator state variables
char first_input[6] = "", second_input[6] = ""; // Buffers for operands (max 5 chars + 1 null terminator)
uint8_t max_char = 0; // Tracks the current number of characters entered for the active operand
uint8_t counter = 0;  // State flag: 0 = entering first_input, 1 = entering second_input
char op = 'n';        // Current operation ('n' = none, '+', '-', 'x', '/')

void loop() {
  // Read the pressed key (returns NO_KEY if none)
  char key = keypad.getKey();

  // Clear the display buffer for the new frame
  display.clearDisplay();

  // If a key was pressed
  if (key) {
    // Set Text color, size and position
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);

    // Audible feedback when a key is pressed
    tone(BUZZER_PIN, 2000, 100);

    // '#' acts as the Equals/Calculate button
    if (key == '#') {
      // Cast inputs to integers
      int x = atoi(first_input);
      int y = atoi(second_input);
      int reslt = 0;

      // Perform the selected arithmetic operation
      switch (op) {
          case '+': reslt = x + y; break;
          case '-': reslt = x - y; break;
          case '/': reslt = x / y; break;
          case 'x': reslt = x * y; break;
      }

      // Display formatting based on whether an operation was previously selected
      if (op == 'n') {
          display.print(first_input);
          display.print(" ");
          display.print("?");
          display.print(" ");
          display.print(second_input);
          display.print(" = ");
          display.println("??");
      } else {
          display.print(first_input);
          display.print(" ");
          display.print(op);
          display.print(" ");
          display.print(second_input);
          display.print(" = ");
          display.println(reslt);
      }

      /* Clear Inputs */
      for(byte i = 0; i < 6; i++) {
         first_input[i] = '\0';
         second_input[i] = '\0';
      }

      /* Use the result as the first input for another operation (chained calculation) */
      snprintf(first_input, sizeof(first_input), "%d", reslt);

      // Reset state variables for the next calculation
      max_char = 0;
      counter = 0;
      op = 'n';

    /* Addition */
    } else if (key == 'A') {
      display.print(first_input);
      display.print(" + ");
      op = '+';
      if (counter == 0) {
        max_char = 0; // Reset character counter for the second operand
        counter++;    // Switch state to accept second operand
      }

    /* Subtraction */
    } else if (key == 'B') {
      display.print(first_input);
      display.print(" - ");
      op = '-';
      if (counter == 0) {
        max_char = 0;
        counter++;
      }

    /* Clear Everything */
    } else if (key == 'C') {
      display.clearDisplay();
      max_char = 0;
      counter = 0;
      op = 'n';
      for(byte i = 0; i < 6; i++) {
          first_input[i] = '\0';
          second_input[i] = '\0';
      }

    /* Division */
    } else if (key == 'D') {
      display.print(first_input);
      display.print(" / ");
      op = '/';
      if (counter == 0) {
        max_char = 0;
        counter++;
      }

    /* Multiplication */
    } else if (key == '*') {
      display.print(first_input);
      display.print(" x ");
      op = 'x';
      if (counter == 0) {
        max_char = 0;
        counter++;
      }

    } else { // Handle numeric keys (0-9)
      /* Store inputs */
      if (max_char < 5) { // Limit input to 5 characters to prevent buffer overflow (array size is 6)
        if (counter == 0) {
          first_input[max_char] = key;
          display.print(first_input);
        } else {
          second_input[max_char] = key;
          display.print(first_input);
          display.print(" ");
          display.print(op);
          display.print(" ");
          display.print(second_input);
        }
        // Increment character count for the active operand
        max_char++;

      /* Stop reading input after the maximum character count has reached 5 */
      } else {
        if (counter == 0) {
          display.print(first_input);
        } else {
          display.print(first_input);
          display.print(" ");
          display.print(op);
          display.print(" ");
          display.print(second_input);
        }
      }
    }

     // Push the updated buffer to the physical OLED screen
    display.display();
  }
}
