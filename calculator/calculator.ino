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

char first_input[5] = "" , second_input[5] = "";
short counter = 0;
int max_char = 0;
char curr_input = 'n';

void loop() {
  char key = keypad.getKey();

  display.clearDisplay();

  if (key) {
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);

    /* D defines the first value and the second value */
    if (key == '#') {
      if (counter == 0) {
        display.println("Initialize First Number!");
        curr_input = 'x';
        counter++;
      } else if (counter == 1) {
        display.println("Initialize Second Number!");
        curr_input = 'y';
        counter--;
      }
      max_char = 0;
    /* Addition */
    } else if (key == 'A') {
       int x = atoi(first_input);
       int y = atoi(second_input);
       int reslt = x + y;

       display.print(x);
       display.print(" + ");
       display.print(y);
       display.print(" = ");
       display.print(reslt);
       max_char = 0;
    /* Subtraction */
    } else if (key == 'B') {
       int x = atoi(first_input);
       int y = atoi(second_input);
       int reslt = x - y;

       display.print(x);
       display.print(" - ");
       display.print(y);
       display.print(" = ");
       display.print(reslt);
       max_char = 0;
    /* C to clear everything and show available operations*/
    } else if (key == 'C'){
      display.println("A => Addition");
      display.println("B => Subtraction");
      display.println("* => Multiplication");
      display.println("D => Division");
      display.println("C => Clear");
      display.println("# => Initialize");
      max_char = 0;
      counter = 0;
      curr_input = 'n';
    /* Handle other inputs inputs */
    } else {
        if (max_char < 4) {
          if (counter == 1) {
            first_input[max_char] = key;
            display.println("First Number: ");
            display.println(first_input);
          } else if (counter == 0) {
            second_input[max_char] = key;
            display.println("Second Number: ");
            display.println(second_input);
          }
          max_char++;
        } else {
          display.println("Numbers can't exceed 4 digits");
          max_char = 0;
          counter = 0;
          curr_input = 'n';
        }
    }

    display.display();

  }
}
