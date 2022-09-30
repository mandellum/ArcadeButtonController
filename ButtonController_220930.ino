uint8_t buf[8] = { 0 };   //Keyboard report buffer

#define BUTTON_PIN 8 // Pin for Spacebar
#define RELAY_PIN 3 // Arduino pin connected to relay's pin

int previousButtonState = HIGH;



void setup() {
  Serial.begin(19200);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN, OUTPUT);        // set arduino pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);      // set up built-in LED

}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); // read new state

  if (buttonState == LOW) { // is pressed
    digitalWrite(RELAY_PIN, HIGH);    // turn on relay
    digitalWrite(LED_BUILTIN, HIGH);  // turn on LED with high voltage
    if (previousButtonState == HIGH) {
      buf[2] = 44;   // Space keycode
      Serial.write(buf, 8); // Send keypress
      releaseKey();
    }
    delay(50); // solves the double-click problem.
  }
  else if (buttonState == HIGH) {
    digitalWrite(RELAY_PIN, LOW);  // turn off
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

  }
  previousButtonState = buttonState;
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Send Release key
}
