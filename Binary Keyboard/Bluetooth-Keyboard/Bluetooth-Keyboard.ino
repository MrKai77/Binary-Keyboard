#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BleKeyboard.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);
BleKeyboard bleKeyboard("ESP32", "ESPRESSIF", 75);

int b0 = 19;
int b1 = 18;
int bB = 5;
bool State0;
bool State1;
bool StateB;

int binnum = 1;
int bin1 = 0;
int bin2 = 0;
int bin3 = 0;
int bin4 = 0;
int bin5 = 0;
int bin6 = 0;
int bin7 = 0;
int bin8 = 0;

String binary = " ";

void printD(String text) {
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 10);
  display.println(text);
}

bool wait() {
  delay(300);
}

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(b0, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(bB, INPUT_PULLUP);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 10);
  display.println("STARTING");
  display.display();
  bleKeyboard.begin();
  delay(2000);
  Serial.println("\n\nWaiting for a connection...");
}

void loop() {
  display.clearDisplay();
  State0 = 1-digitalRead(b0); //button for 0
  State1 = 1-digitalRead(b1); //button for 1
  StateB = 1-digitalRead(bB); //button for backspace

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 0);
  if(bleKeyboard.isConnected()) {
    display.println("   Connected!   ");
  } else {
    display.println("Not Connected...");
  }
  
  if(binnum == 9) {
    if(bleKeyboard.isConnected()) {
       String binresult = getBin(bin1,bin2,bin3,bin4,bin5,bin6,bin7,bin8);

       if(binresult == "KEY_TAB") {
          bleKeyboard.write(KEY_TAB);
       }
       else if(binresult == "KEY_BACKSPACE") {
          bleKeyboard.write(KEY_BACKSPACE);
       }
       else if(binresult == "KEY_ESC") {
          bleKeyboard.write(KEY_ESC);
       }
       else if(binresult == "KEY_DELETE") {
          bleKeyboard.write(KEY_DELETE);
       }
       else {
          bleKeyboard.print(binresult);
       }
       
    } else {
      Serial.print("Not Connected, ");
    }
    Serial.println(getBin(bin1,bin2,bin3,bin4,bin5,bin6,bin7,bin8));
    bin1 = 0;
    bin2 = 0;
    bin3 = 0;
    bin4 = 0;
    bin5 = 0;
    bin6 = 0;
    bin7 = 0;
    bin8 = 0;
    binnum = 1;
  }
  
  if(binnum == 0) {
    binnum = 8;
  }

  if(State0 == 1) {
    switch(binnum) {   
      case 1:
        bin1 = 0;
      break;

      case 2:
        bin2 = 0;
      break;

      case 3:
        bin3 = 0;
      break;

      case 4:
        bin4 = 0;
      break;

      case 5:
        bin5 = 0;
      break;

      case 6:
        bin6 = 0;
      break;

      case 7:
        bin7 = 0;
      break;

      case 8:
        bin8 = 0;
      break;
    }
    binnum++;
    while(digitalRead(b0) == false) {
      //do nothing until button is released
    }
  }
  
  if(State1 == 1) {
    switch(binnum) {
      case 1:
        bin1 = 1;
      break;

      case 2:
        bin2 = 1;
      break;

      case 3:
        bin3 = 1;
      break;

      case 4:
        bin4 = 1;
      break;

      case 5:
        bin5 = 1;
      break;

      case 6:
        bin6 = 1;
      break;

      case 7:
        bin7 = 1;
      break;

      case 8:
        bin8 = 1;
      break;
    }
    binnum++;
    while(digitalRead(b1) == false) {
      //do nothing until button is released
    }
  }
    
  if(StateB == 1) {
    binnum--;
    wait();
  }

  printD(String(bin1) + 
         String(bin2) + 
         String(bin3) + 
         String(bin4) + 
         String(bin5) + 
         String(bin6) + 
         String(bin7) + 
         String(bin8));
         
  switch(binnum) {
    case 1:
      display.drawLine(16, 25, 25, 25, SSD1306_WHITE);
      display.drawLine(16, 26, 25, 26, SSD1306_WHITE);
    break;

    case 2:
      display.drawLine(28, 25, 37, 25, SSD1306_WHITE);
      display.drawLine(28, 26, 37, 26, SSD1306_WHITE);
    break;

    case 3:
      display.drawLine(40, 25, 49, 25, SSD1306_WHITE);
      display.drawLine(40, 26, 49, 26, SSD1306_WHITE);
    break;

    case 4:
      display.drawLine(52, 25, 61, 25, SSD1306_WHITE);
      display.drawLine(52, 26, 61, 26, SSD1306_WHITE);
    break;

    case 5:
      display.drawLine(64, 25, 73, 25, SSD1306_WHITE);
      display.drawLine(64, 26, 73, 26, SSD1306_WHITE);
    break;
    
    case 6:
      display.drawLine(76, 25, 85, 25, SSD1306_WHITE);
      display.drawLine(76, 26, 85, 26, SSD1306_WHITE);
    break;
    
    case 7:
      display.drawLine(88, 25, 97, 25, SSD1306_WHITE);
      display.drawLine(88, 26, 97, 26, SSD1306_WHITE);
    break;
    
    case 8:
      display.drawLine(100, 25, 109, 25, SSD1306_WHITE);
      display.drawLine(100, 26, 109 , 26, SSD1306_WHITE);
    break;
  }
  display.display();
}


String getBin(int bit1, int bit2, int bit3, int bit4, int bit5, int bit6, int bit7, int bit8) { //binary decoder

  if(bit1 == 0 && bit2 == 0 && bit3 == 1 && bit4 == 1) {           //numbers & punctuation
    
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "0";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "1";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "2";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "3";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "4";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "5";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "6";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "7";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "8";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "9";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = ":";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = ";";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "<";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "=";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = ">";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "?";
      }
  }
  
  else if(bit1 == 0 && bit2 == 1 && bit3 == 0 && bit4 == 0) {           //capital letters & punctuation
    
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "@";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "A";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "B";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "C";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "D";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "E";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "F";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "G";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "H";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "I";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "J";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "K";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "L";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "M";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "N";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "O";
      }
  }
  
  else if(bit1 == 0 && bit2 == 1 && bit3 == 0 && bit4 == 1) {           //capital letters & punctuation 2
      
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "P";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "Q";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "R";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "S";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "T";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "U";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "V";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "W";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "X";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "Y";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "Z";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "[";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "\'";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "]";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "ˆ";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "_";
      }
  }

  else if(bit1 == 0 && bit2 == 1 && bit3 == 1 && bit4 == 0) {           //lowercase letters & punctuation 
      
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "`";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "a";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "b";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "c";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "d";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "e";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "f";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "g";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "h";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "i";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "j";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "k";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "l";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "m";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "n";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "o";
      }
  }

  else if(bit1 == 0 && bit2 == 1 && bit3 == 1 && bit4 == 1) {           //lowercase letters & punctuation 2
      
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "p";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "q";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "r";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "s";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "t";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "u";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "v";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "w";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "x";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "y";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "z";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "{";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "|";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "}";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "~";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "KEY_DELETE";
      }
  }

  else if(bit1 == 0 && bit2 == 0 && bit3 == 1 && bit4 == 0) {           //punctuation
      
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = " ";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "!";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "\"";
      }
      if(bit5 == 0 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "#";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = "$";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "%";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = "&";
      }
      if(bit5 == 0 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "'";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "(";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = ")";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 0) {
        binary = "*";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "+";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 0) {
        binary = ",";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 0 && bit8 == 1) {
        binary = "-";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 0) {
        binary = ".";
      }
      if(bit5 == 1 && bit6 == 1 &&  bit7 == 1 && bit8 == 1) {
        binary = "/";
      }
  }

  else if(bit1 == 0 && bit2 == 0 && bit3 == 0 && bit4 == 0) {           //special keys
      
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 1) {
        binary = "KEY_TAB";
      }
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 0 && bit8 == 0) {
        binary = "KEY_BACKSPACE";
      }
  }
  
  else if(bit1 == 0 && bit2 == 0 && bit3 == 0 && bit4 == 1) {  
    //special keys 2
      
      if(bit5 == 1 && bit6 == 0 &&  bit7 == 1 && bit8 == 1) {
        binary = "KEY_ESC";
      }
  }
  
  return binary;
}
