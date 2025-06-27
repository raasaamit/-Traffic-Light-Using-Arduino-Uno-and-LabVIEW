//   Copyright 2016 Lukas Lösche <lloesche@fedoraproject.org>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define red_led 4         // Output pin of the red LED
#define yellow_led 3      // Output pin of the yellow LED
#define green_led 2       // Output pin of the green LED
#define red_phase 6000    // How long the red phase lasts in ms
#define yellow_phase 2000 // How long the yellow phase lasts in ms
#define green_phase 7000  // How long the green phase lasts in ms
#define button1 9         // Input pin of Button 1
#define button2 8         // Input pin of Button 2
#define button3 7         // Input pin of Button 3
#define num_buttons 3     // Number of installed buttons

bool button_down[num_buttons];        // Stores when a button is pushed down
bool red = false;                     // True while the red LED is on
bool yellow = false;                  // True while the yellow LED is on
bool green = false;                   // True while the green LED is on
unsigned long to_red_millis = 0;      // Time in millis() when red was turned on
unsigned long to_yellow_millis = 0;   // Time in millis() when yellow was turned on
unsigned long to_green_millis = 0;    // Time in millis() when green was turned on
unsigned int buttons[] = {button1, button2, button3};  // List of buttons



void setup() {
  pinMode(red_led, OUTPUT);       // Set the LED Pins to
  pinMode(yellow_led, OUTPUT);    // be output pins
  pinMode(green_led, OUTPUT);     // 
  digitalWrite(red_led, LOW);     // and pull them LOW.
  digitalWrite(yellow_led, LOW);  // 
  digitalWrite(green_led, LOW);   // 

  for (int i=0; i<num_buttons; i++) { // Iterate over the list
    pinMode(buttons[i], INPUT);       // of push buttons and
    digitalWrite(buttons[i], HIGH);   // pull them HIGH.
    button_down[i] = false;            // Default to the button not
  }                                   // being pressed right now.

  Serial.begin(115200);
  blocking_light_test();  // Run an LED test at startup and
  Serial.println("defaulting to red on");
  to_red();               // default to red after the test.
}


void loop() {
  unsigned long currentMillis = millis(); // Store the current time in millis();

  if(red && yellow && !green) {                                               // If we're currently switching from red to green
    if ((unsigned long)(currentMillis - to_yellow_millis) >= yellow_phase) {  // and the yellow phase is over.
      Serial.println("red and yellow are on, switching to green");
      red_off();
      yellow_off();
      green_on();
    }
  } else if(red && !yellow && !green) {                                       // If the light is red
    if ((unsigned long)(currentMillis - to_red_millis) >= red_phase) {        // and the red phase is over.
      Serial.println("red is on, turning on yellow");
      red_on();
      yellow_on();
    }
  } else if(green && !red && !yellow) {                                       // If the light is green
    if ((unsigned long)(currentMillis - to_green_millis) >= green_phase) {    // and the green phase is over.
      Serial.println("green is on, switching to yellow");
      green_off();
      yellow_on();
    }
  } else if(yellow && !red && !green) {                                       // If we're currently switching from green to red
    if ((unsigned long)(currentMillis - to_yellow_millis) >= yellow_phase) {  // and the yellow phase is over.
      Serial.println("yellow is on, switching to red");
      yellow_off();
      red_on();
    }
  } else {                                                                    // If we're in some undefined state
    Serial.println("undefined state, resetting");                             // e.g. after a light test
    red_on();                                                                 // default to red.
    yellow_off();
    green_off();
  }

  handle_buttons();  // Handle Button Presses
}


// The <color>_on/off() functions turn
// the individual LEDs on or off. They
// store the time a LED was turned on in
// millis() and set the corresponding bool
// color variable true or false.
void red_on() {
  to_red_millis = millis();
  digitalWrite(red_led, HIGH);
  red = true;
  Serial.println("red on");
}

void red_off() {
  digitalWrite(red_led, LOW);
  red = false;
  Serial.println("red off");
}


void yellow_on() {
  to_yellow_millis = millis();
  digitalWrite(yellow_led, HIGH);
  yellow = true;
  Serial.println("yellow on");
}

void yellow_off() {
  digitalWrite(yellow_led, LOW);
  yellow = false;
  Serial.println("yellow off");
}


void green_on() {
  to_green_millis = millis();
  digitalWrite(green_led, HIGH);
  green = true;
  Serial.println("green on");
}

void green_off() {
  digitalWrite(green_led, LOW);
  green = false;
  Serial.println("green off");
}


// Switch from any state to red
void to_red() {
  if(red) {               // If the red light is on either alone or in combination
    red_on();             // with yellow we switch immediately back to red
    yellow_off();         // thereby extending the red phase.
    green_off();
  } else if(green) {      // If light is currently green
    to_green_millis = 0;  // expire the green phase immediately.
  } else if(!red && !yellow && !green) {
    red_on();             // Turn red on if all lights were previously off.
  }
  // There's one scenario missing where the light is just yellow.
  // We don't do anything in that case and just wait for
  // it to switch to red.
}


// Switch from any state to green
void to_green() {
  if(red && !yellow) {    // If the light is red we expire
    to_red_millis = 0;    // the red phase immediately.
  } else if (yellow && !red) {  // If we're currently switching from green to red
    yellow_off();               // 
    red_off();                  // 
    green_on();                 // abort the switch and go back to green immediately.
  } else if (green) {     // If we're already green we extend the green phase
    red_off();            // and also turn all other lights off just in case
    yellow_off();         // they were on due to some light test phase.
    green_on();
  } else if(!red && !yellow && !green) {
    green_on();           // Turn green on if all lights were previously off.
  }
  // There's one scenario missing where red and yellow are on.
  // In that case we don't do anything and just wait for the yellow
  // phase to expire and the light switch to green by itself.
}


// Run an LED test.
// During the test no inputs are being processed.
// The test ends with all lights being off.
void blocking_light_test() {
  int delay_time = 70;
  int test_rounds = 10;
  Serial.println("running light test");
  red_off();
  yellow_off();
  green_off();
  for(int i=0; i<test_rounds; i++) {
    red_on();
    delay(delay_time);
    yellow_on();
    delay(delay_time);
    green_on();
    delay(delay_time);
    red_off();
    delay(delay_time);
    yellow_off();
    delay(delay_time);
    green_off();
    delay(delay_time);
  }
}


// Handle button presses
// The button inputs are HIGH by default and go LOW when pushed down.
void handle_buttons() {
  for (int i=0; i<num_buttons; i++) {   // Iterate over the installed buttons
    if (!digitalRead(buttons[i])) {     // If the button is pulled LOW
      button_down[i] = true;             // we remember that it was pressed down.
    } else {                            // If it's currently not being pressed
      if(button_down[i]) {               // but previously was consider it a full
        button_down[i] = false;          // button push and reset it's state.
        Serial.print("button ");
        Serial.println(i+1);
        switch(i) {                     // Check which button was pressed down.
          case 0:                       // Button 1 switches
            to_red();                   // the light to red.
            break;
          case 1:                       // Button 2 runs
            blocking_light_test();      // the LED startup test.
            break;
          case 2:                       // Button 3 switches
            to_green();                 // the light to green.
            break;
        }
      }
    }
  }
}

