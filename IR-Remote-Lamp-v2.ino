//
//   Living room remote control box for two lamps
//   using buttons 7 and 8 on the Prior 3 button remote control.
//   v 2.0 Oct 17 2020
//   minor correction to flag management June 24 2021

#include <IRremote.h>                                 // load the IRremote library

int RECV_PIN = 2;                                     // IRreceiver on pin 2
int RELAY1_PIN = 3;                                   // Relay 1 on pin 3
int RELAY2_PIN = 4;                                   // Relay 2 on pin 4
int LED = 5;                                          // LED receive indicator on pin 5

IRrecv irrecv(RECV_PIN);                              // Create an instance for irrecv
decode_results results;                               // Create an instance to store the collected data in

boolean flag7 = 0;                                    // Flags are initially zero/both relays are off
boolean flag8 = 0;


void setup()
{
  pinMode(RELAY1_PIN, OUTPUT);                        // set pins to relays
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(LED, OUTPUT);                               // set pin to LED
  pinMode(RECV_PIN, INPUT);                           // set IR receive pin

  irrecv.enableIRIn();                                // start the receiver
}

void loop()
{
  if (irrecv.decode(&results))                        // Checks if we received a signal from the IR receiver
  {
    unsigned long val = results.value;

    if (val == 0xFF13EC) {
      digitalWrite(LED, HIGH);                        // Flash the LED
      delay(300);
      digitalWrite(LED, LOW);
      if (flag7 == 0) {
        flag7 = 1;
      } else {
        flag7 = 0;
      }
      //flag7 != flag7;                               // toggle flag7
      
    } else if (val == 0xFF936C) {
      digitalWrite(LED, HIGH);                        // Flash the LED
      delay(300);
      digitalWrite(LED, LOW);
      if (flag8 == 0) {
        flag8 = 1;
      } else {
        flag8 = 0;
      }
      //flag8 != flag8;                               // toggle flag8
      
      
    }
    else if (val == 0xFF837C) {                       // Toggle both devices - green button
      digitalWrite(LED, HIGH);                        // Flash the LED
      delay(300);
      digitalWrite(LED, LOW);
      if ((flag7 == 0) && (flag8 == 0)) {
        flag8 = 1;
        flag7 = 1;
      } else {
        flag8 = 0;
        flag7 = 0;
      }
                                                      // toggle flag7 and flag8

    }

    irrecv.resume();                                  // receive the next IR value

    // Actuate relays ===============================
    digitalWrite(RELAY1_PIN, flag7);
    digitalWrite(RELAY2_PIN, flag8);
  }
}
