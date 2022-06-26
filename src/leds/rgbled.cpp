#include "rgbled.h"

#define RED_LED_PIN 15
#define GREEN_LED_PIN 13
#define BLUE_LED_PIN 12

void setUpRgbLed() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    analogWrite(RED_LED_PIN, 0);
    analogWrite(GREEN_LED_PIN, 0);
    analogWrite(BLUE_LED_PIN, 0);
    
    delay(2000);

    analogWrite(RED_LED_PIN, 0);
    analogWrite(GREEN_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 255);

    delay(2000);

    analogWrite(RED_LED_PIN, 255);
    analogWrite(GREEN_LED_PIN, 0);
    analogWrite(BLUE_LED_PIN, 255);
    
    delay(2000);

    analogWrite(RED_LED_PIN, 255);
    analogWrite(GREEN_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 0);

    delay(2000);

    analogWrite(RED_LED_PIN, 255);
    analogWrite(GREEN_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 255);
}

void setRgbLedColor(struct Color color) {

}


///*LED_Breathing.ino Arduining.com  20 AUG 2015
//Using NodeMCU Development Kit V1.0
//Going beyond Blink sketch to see the blue LED breathing.
//A PWM modulation is made in software because GPIO16 can't
//be used with analogWrite().
//*/
//
//#define LED     D0        // Led in NodeMCU at pin GPIO16 (D0).
//
//#define BRIGHT    5     //max led intensity (1-500)
//#define INHALE    1250    //Inhalation time in milliseconds.
//#define PULSE     INHALE*1000/BRIGHT
//#define REST      1000    //Rest Between Inhalations.
//
////----- Setup function. ------------------------
//void setup() {
//  pinMode(LED, OUTPUT);   // LED pin as output.
//}
//
////----- Loop routine. --------------------------
//void loop() {
//  //ramp increasing intensity, Inhalation:
//  for (int i=1;i<BRIGHT;i++){
//    digitalWrite(LED, LOW);          // turn the LED on.
//    delayMicroseconds(i*10);         // wait
//    digitalWrite(LED, HIGH);         // turn the LED off.
//    delayMicroseconds(PULSE-i*10);   // wait
//    delay(0);                        //to prevent watchdog firing.
//  }
//  //ramp decreasing intensity, Exhalation (half time):
//  for (int i=BRIGHT-1;i>0;i--){
//    digitalWrite(LED, LOW);          // turn the LED on.
//    delayMicroseconds(i*10);          // wait
//    digitalWrite(LED, HIGH);         // turn the LED off.
//    delayMicroseconds(PULSE-i*10);  // wait
//    i--;
//    delay(0);                        //to prevent watchdog firing.
//  }
//  delay(REST);                       //take a rest...
//}