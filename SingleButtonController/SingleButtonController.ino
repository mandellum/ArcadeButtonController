/* The Single Button Controller is the programming half of a physical Arduino-powered arcade button.
   Any generic arcade button will suffice to provide a button input. If the button is lit by an LED 
   that requires up to 12 volts, a relay is necessary to separate a 12-volt source from the
   5-volt Arduino unit and its USB connection to a PC. 
   
   The output of the Arduino is done with discrete serial messages that Ardity is continually
   polling for. NOTE: There is an Ardity listener script, however in my tests it seems to only work in
   Unity Editor, not in Stand-alone builds.*/

#define BUTTON_PIN 8  // Pinout 8 for button input
#define RELAY_PIN 3   // Pinout 3 for relay

int previousButtonState = HIGH;  // Not pressed = high
unsigned long lastPress = 0;
unsigned long lastBlink = 0;
unsigned long idleWaitTime = 10000;  // 10s
unsigned long blinkDelay = 700;      // 0.7s

void setup() {
  Serial.begin(9600);                 // initialize serial baud rate at 9600 - in tests, it worked well
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN, OUTPUT);         // set arduino pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);       // set up built-in LED
}

void loop() {

  int buttonState = digitalRead(BUTTON_PIN);  // read new state

  if (buttonState == LOW) {             // button is pressed
    digitalWrite(RELAY_PIN, HIGH);      // turn on relay
    digitalWrite(LED_BUILTIN, HIGH);    // turn on LED with high voltage
    if (previousButtonState == HIGH) {  // if button was last unpressed
      Serial.println("Down");           // sends message "Down" to the PC
      delay(30);                        // solves the spacing problem.
      lastPress = millis();
    }
    delay(25);
  } else if (buttonState == HIGH) {
    digitalWrite(RELAY_PIN, LOW);    // turn off
    digitalWrite(LED_BUILTIN, LOW);  // turn off LED
  }

  // Idle animation (blinks once for every three counts)
  if (millis() > lastPress + idleWaitTime) {
    if (millis() > lastBlink + 2 * blinkDelay) {
      digitalWrite(RELAY_PIN, HIGH);    // turn on relay
      digitalWrite(LED_BUILTIN, HIGH);  // turn on built-in
      delay(blinkDelay);
      lastBlink = millis();             // Loops pattern
    }
  }

  previousButtonState = buttonState;
}