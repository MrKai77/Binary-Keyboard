#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
}

void loop() {
  printD("1_______");
  delay(200);
  printD("11______");
  delay(200);
  printD("111_____");
  delay(200);
  printD("1111____");
  delay(200);
  printD("11111___");
  delay(200);
  printD("111111__");
  delay(200);
  printD("1111111_");
  delay(200);
  printD("11111111");
  delay(200);

}

void printD(String text) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 10);
  display.println(text);
  display.display();
}
