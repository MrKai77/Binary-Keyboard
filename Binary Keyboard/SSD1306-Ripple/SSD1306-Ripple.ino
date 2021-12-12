#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Ripple.h"

Adafruit_SSD1306 display(128, 32, &Wire, -1);

int del = 15;

int bL = 19;
int bR = 18;
bool StateL;
bool StateR;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 10);
  display.println("STARTING");
  display.display();
  pinMode(bL, INPUT_PULLUP);
  pinMode(bR, INPUT_PULLUP);
  delay(1000);
  display.clearDisplay();

  Serial.println("Startup finished!");
}

void loop() {
  display.clearDisplay();
  StateL = 1-digitalRead(bL); //button for left
  StateR = 1-digitalRead(bR); //button for right

  if (StateL == true) {
    display.drawBitmap(0, 0, bigL, 32, 32, WHITE);      //write the big "L" icon
    Serial.print("Left: 1    ");
  } else {
    display.drawBitmap(0, 0, small, 32, 32, WHITE);     //write a small circle
    Serial.print("Left: 0    ");
  }
  if (StateR == true) {
    display.drawBitmap(96, 0, bigR, 32, 32, WHITE);     //write the big "R" icon
    Serial.print("Right: 1  ");
  } else {
    display.drawBitmap(96, 0, small, 32, 32, WHITE);    //write a small circle
    Serial.println("Right: 0");
  }
  
  // while(digitalRead(bL) == false) {/*do nothing*/}
  // while(digitalRead(bR) == false) {/*do nothing*/}
  display.display();
}
