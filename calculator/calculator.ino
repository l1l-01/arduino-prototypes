#include <DIYables_Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

//four rows
const int ROW_NUM = 4;
//four columns
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

//connect to the row pinouts of the keypad
byte pin_rows[ROW_NUM] = { 9, 8, 7, 6 };
//connect to the column pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 5, 4, 3, 2 };

DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Serial.begin(115200);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

char first_input[6] = "", second_input[6] = "";
uint8_t max_char = 0, counter = 0;
char op = 'n';

void loop() {
  char key = keypad.getKey();

  display.clearDisplay();

  if (key) {
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);

    if (key == '#') {
      int x = atof(first_input);
      int y = atof(second_input);
      int reslt = 0;

      switch (op) {
      case '+': reslt = x + y; break;
      case '-': reslt = x - y; break;
      case '/': reslt = x / y; break;
      case '*': reslt = x * y; break;
      }

      display.print(first_input);
      display.print(" ");
      display.print(op);
      display.print(" ");
      display.print(second_input);
      display.print(" = ");
      display.println(reslt);

      /* Clear Inputs */
      for(byte i = 0; i < 6; i++) {
         first_input[i] = '\0';
         second_input[i] = '\0';
      }

      /* Use the result as the first input for another operation */
      snprintf(first_input,sizeof(first_input),"%d",reslt);

      max_char = 0;
      counter = 0;
      op = 'n';
    /* Addition */
    } else if (key == 'A') {
      display.print(first_input);
      display.print(" + ");
      op = '+';
      if (counter == 0) {
        max_char = 0;
        counter++;
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
    } else if (key == 'C'){
      display.clearDisplay();
      max_char = 0;
      counter == 0;
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
      display.print(" * ");
      op = '*';
      if (counter == 0) {
        max_char = 0;
        counter++;
      }
    }else {
      /* Store inputs */
      if (max_char < 5) {
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
        max_char++;

      /* Stop reading input after the maximum character count has reached 5 */
        } else {
          if (counter == 0) {
            display.print(first_input);
          }else {
            display.print(first_input);
            display.print(" ");
            display.print(op);
            display.print(" ");
            display.print(second_input);
          }
        }
    }

    display.display();

  }
}
