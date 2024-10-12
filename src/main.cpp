#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "NeuralNetwork.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

NeuralNetwork *nn;

void intro(float n1, float n2, char pred, char expected);
//void testdrawline();      // Draw many lines
//void testdrawrect();      // Draw rectangles (outlines)
//void testfillrect();      // Draw rectangles (filled)
//void testdrawcircle();    // Draw circles (outlines)
//void testfillcircle();    // Draw circles (filled)
//void testdrawroundrect(); // Draw rounded rectangles (outlines)
//void testfillroundrect(); // Draw rounded rectangles (filled)
//void testdrawtriangle();  // Draw triangles (outlines)
//void testfilltriangle();  // Draw triangles (filled)
//void testdrawbitmap();    // Draw a small bitmap image
//void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop() {
  float number1 = random(100) / 100.0;
  float number2 = random(100) / 100.0;

  nn->getInputBuffer()[0] = number1;
  nn->getInputBuffer()[1] = number2;

  float result = nn->predict();

  const char *expected = number2 > number1 ? "True" : "False";

  const char *predicted = result > 0.5 ? "True" : "False";

  Serial.printf("%.2f %.2f - result %.2f - Expected %s, Predicted %s\n", number1, number2, result, expected, predicted);

  intro(number1,number2, *predicted, *expected);

  delay(1000);
}

void intro(float n1, float n2, char pred, char expected) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("n1: "));
  display.println(n1);
  display.print(F("n2: "));
  display.println(n2);
  display.print(F("res.: "));
  display.println(pred);
  display.print(F("Exp.: "));
  display.println(expected);
  
  //display.setCursor(20, 20);
  //display.println(F("Display"));
  //display.setCursor(15, 40);
  //display.println(F("Tutorial"));
  
  display.display();// Show initial text
  delay(100);
}