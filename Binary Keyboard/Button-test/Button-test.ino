int b0 = 19;
int b1 = 18;
int bB = 5;
bool State0;
bool State1;
bool StateB;

void setup() {
  // put your setup code here, to run once:
  pinMode(b0, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(bB, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  State0 = digitalRead(b0); //button for 0
  State1 = digitalRead(b1); //button for 1
  StateB = digitalRead(bB); //button for backspace

  if (State0 == 0) {
    Serial.println("0");
  }
  else if (State1 == 0) {
    Serial.println("1");
  }
  else if (StateB == 0) {
    Serial.println("B");
  }
  delay(100);
}
