#include <LiquidCrystal.h>

// Initialize LCD: RS = 8, E = 9, D4 = 5, D5 = 4, D6 = 3, D7 = 2
LiquidCrystal lcd(8, 9, 5, 4, 3, 2);

// LED Pins
const int redLED = 13;    // MSB
const int yellowLED = 12;
const int greenLED = 11;  // LSB
const int doneLED = 10;   // Turns on when count reaches 7

// Slide switch
const int switchPin = 7;  // Active LOW

void setup() {
  // Set LED pins as OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(doneLED, OUTPUT);

  // Set switch as INPUT_PULLUP (reads HIGH when off, LOW when ON)
  pinMode(switchPin, INPUT_PULLUP);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    // Switch is ON — begin operation
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Running...");

    resetLEDs();

    for (int i = 0; i < 8; i++) {
      // Show binary count on LCD
      lcd.setCursor(0, 1);
      lcd.print("Count: ");
      lcd.print(i, BIN);
      lcd.print("   ");  // Clear residual digits

      // Light LEDs based on binary bits
      digitalWrite(redLED,    (i >> 2) & 1);  // MSB
      digitalWrite(yellowLED, (i >> 1) & 1);
      digitalWrite(greenLED,  (i >> 0) & 1);  // LSB

      // Turn on Done LED when count is 7
      if (i == 7) {
        digitalWrite(doneLED, HIGH);
        lcd.setCursor(10, 1);
        lcd.print("Done");
      } else {
        digitalWrite(doneLED, LOW);
        lcd.setCursor(10, 1);
        lcd.print("    "); // Clear "Done"
      }

      delay(1000);
    }
  } else {
    // Switch is OFF — idle state
    resetLEDs();
    digitalWrite(doneLED, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Waiting for");
    lcd.setCursor(0, 1);
    lcd.print("Switch ON...");
    delay(800);
    lcd.clear();  // Prevent flickering
  }
}

void resetLEDs() {
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}
