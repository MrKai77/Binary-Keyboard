#include <BleMouse.h>

BleMouse bleMouse("ESP32", "ESPRESSIF", 75);

void setup() {
  Serial.begin(9600);
  bleMouse.begin();
  Serial.println("Started!");
}

void loop() {
  if(bleMouse.isConnected()) {
    Serial.println("Left click");
    bleMouse.click(MOUSE_LEFT);
    delay(1000);
  }
}
