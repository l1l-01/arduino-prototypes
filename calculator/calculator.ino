#include <DIYables_Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

char first_input[5] = "", second_input[5] = "";
byte max_char = 0;
char curr_input = 'x';
char op = 'n';

void loop() {
  char key = keypad.getKey();

  display.clearDisplay();

  if (key) {
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);

    /* # => equal */
    if (key == '#') {

      float x = atof(first_input);
      float y = atof(second_input);
      float reslt = 0;

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
      display.print(reslt);

     for(byte i = 0; i < 5; i++) {
         first_input[i] = '\0';
         second_input[i] = '\0';
     }
      max_char = 0;
      curr_input = 'x';
      op = 'n';
    /* Addition */
    } else if (key == 'A') {
      display.print(first_input);
      display.print(" + ");
      op = '+';
      if (curr_input == 'x') {
        curr_input = 'y';
        max_char = 0;
      }
    /* Subtraction */
    } else if (key == 'B') {
      display.print(first_input);
      display.print(" - ");
      op = '-';
      if (curr_input == 'x') {
        curr_input = 'y';
        max_char = 0;
      }
    /* Clear Everything */
    } else if (key == 'C'){
      display.clearDisplay();
      max_char = 0;
      curr_input = 'x';
      op = 'n';
      for(byte i = 0; i < 5; i++) {
          first_input[i] = '\0';
          second_input[i] = '\0';
      }
    /* Division */
    } else if (key == 'D') {
      display.print(first_input);
      display.print(" / ");
      op = '/';
      if (curr_input == 'x') {
        curr_input = 'y';
        max_char = 0;
      }
    /* Multiplication */
    } else if (key == '*') {
      display.print(first_input);
      display.print(" * ");
      op = '*';
      if (curr_input == 'x') {
        curr_input = 'y';
        max_char = 0;
      }
    }else {
      if (max_char < 4) {
        if (curr_input == 'x') {
          first_input[max_char] = key;
          display.print(first_input);
        } else if (curr_input == 'y') {
          second_input[max_char] = key;
          display.print(first_input);
          display.print(" ");
          display.print(op);
          display.print(" ");
          display.print(second_input);
        }
        max_char++;
        } else {
          display.println("Numbers can't exceed 4 digits");
          max_char = 0;
          curr_input = 'x';
          op = 'n';
          for(byte i = 0; i < 5; i++) {
              first_input[i] = '\0';
              second_input[i] = '\0';
          }
        }
    }

    display.display();

  }
}
