#define BUTTON_PIN 8  // Pin for Spacebar
#define RELAY_PIN 3   // Arduino pin connected to relay's pin

int previousButtonState = HIGH;
unsigned long lastPress = 0;
unsigned long lastBlink = 0;
unsigned long idleWaitTime = 10000;  //10 sec
unsigned long blinkDelay = 700;    //1.3 sec


void setup() {
  Serial.begin(9600);                 // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN, OUTPUT);         // set arduino pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);       // set up built-in LED
}

void loop() {

  // // Print a Built In LED heartbeat
  // if (millis() > lastBlink + blinkDelay) {
  //   digitalWrite(LED_BUILTIN, HIGH);  // turn on LED with high voltage
  //   lastBlink = millis();
  // } else {
  //   digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  // }

  int buttonState = digitalRead(BUTTON_PIN);  // read new state

  if (buttonState == LOW) {           // is pressed
    digitalWrite(RELAY_PIN, HIGH);    // turn on relay
    digitalWrite(LED_BUILTIN, HIGH);  // turn on LED with high voltage
    if (previousButtonState == HIGH) {
      Serial.println("Down");
      delay(30);  // solves the spacing problem.
      lastPress = millis();
    }
    delay(25);
  } else if (buttonState == HIGH) {
    digitalWrite(RELAY_PIN, LOW);    // turn off
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }

  if (millis() > lastPress + idleWaitTime) {
    if (millis() > lastBlink + 2 * blinkDelay) {
      digitalWrite(RELAY_PIN, HIGH);  // turn on relay
      digitalWrite(LED_BUILTIN, HIGH);
      //Serial.println("Blinked");
      delay(blinkDelay);
      lastBlink = millis();
    }
  }


  previousButtonState = buttonState;
}
