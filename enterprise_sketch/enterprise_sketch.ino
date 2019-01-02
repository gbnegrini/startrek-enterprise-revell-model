/*===================================== USS ENTERPRISE NCC-1701 ARDUINO SKETCH ===========================================================================
 * This sketch was written to control light and sound effects of the USS Enterprise NCC-1701 (Revell - 1:600) model.
 * Please note there are several ways to achieve the same effects or even different ones. This sketch was written as best suited to the author's needs. 
 * Authors: Guilherme Negrini & Luísa Lucchese
 */


#include <LedFlasher.h>
#include <LedFader.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
 
SoftwareSerial DFPlayerSerial(10, 11); // RX, TX

//Some instructions to use the DFPlayer functions
/*
mp3_play();      //start play
mp3_play(5);   //play "mp3/0005.mp3"
mp3_pause();
mp3_stop();
mp3_next();      
mp3_prev();
 
mp3_set_volume(uint16_t volume);   //0~30
mp3_set_EQ();   //0~5
void mp3_single_loop(boolean state);   //set single loop
void mp3_random_play();
*/

//Sounds
/*
 * 0001_opening.mp3 > 60s (1min)
 * 0002_bridge.mp3 > 870s (14min30s)
 * 0003_redalert.mp3 > 33s
 * 0004_phasers.mp3 > 30s
 * 0005_torpedoes.mp3 > 4s
 */

//LedFlasher class (author: Nick Gammon) used to blink the saucer LEDs
LedFlasher SaucerBlink (6, 1000, 1000); // pin 6, off for 1000 ms, on for 1000 ms

// constants won't change. Used here to set a pin number:
//Bussard's LEDs pins
const int buss_yellow = 2;
const int buss_red = 3;
const int buss_green_blue = 4;
const int buss_white = 5;

//Firing LEDs pin
const int fire = 9;

//Button's pins
const int button_theme = 14;
const int button_bridge = 15;
const int button_alert = 16;
const int button_firing = 17;
const int button_mute = 18;

//Button's variables
int button_theme_state = 0;
int button_bridge_state = 0;
int button_alert_state = 0;
int button_firing_state = 0;
int button_mute_state = 0;

 // ledState used to set the Bussards LED
int ledState_yellow = LOW;
int ledState_red = LOW; 
int ledState_green_blue = LOW; 
int ledState_white = LOW; 


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
// previousMillis will store last time LED was updated
unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0; 


// interval at which to blink (milliseconds)
const long interval_yellow = 100;
const long interval_red = 200;
const long interval_green_blue = 300;
const long interval_white1 = 500;    
const long interval_white2 = 580; 


//Function to set the states of the Bussards LEDs (turn on or off)
void setBussLED (){
  digitalWrite(buss_yellow, ledState_yellow);
  digitalWrite(buss_red, ledState_red);
  digitalWrite(buss_green_blue, ledState_green_blue);
  digitalWrite(buss_white, ledState_white);
}

//Function to blink the Bussards collectors LEDs's in the desired sequence and interval
void BussBlink(){
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= interval_yellow and currentMillis - previousMillis1 <= interval_red) {
   //light only the yellows
   ledState_yellow = HIGH;
   ledState_red = LOW;
   ledState_green_blue = LOW;
   ledState_white = LOW;

   // set the LED with the ledState of the variable:
   setBussLED();
    
  }
  
  if (currentMillis - previousMillis1 >= interval_red and currentMillis - previousMillis1 <= interval_green_blue) {
    //light only the reds
    ledState_yellow = LOW;
    ledState_red = HIGH;
    ledState_green_blue = LOW;
    ledState_white = LOW;
      
    // set the LED with the ledState of the variable:
    setBussLED();
  }
  
  if (currentMillis - previousMillis1 >= interval_green_blue) {
    // save the last time you blinked the LED
    previousMillis1 = currentMillis;

    //light only the greens and blues
    ledState_yellow = LOW;
    ledState_red = LOW;
    ledState_green_blue = HIGH;
    ledState_white = LOW;
      
    // set the LED with the ledState of the variable:
    setBussLED();
    
  }

  if (currentMillis - previousMillis2 >= interval_white1 and currentMillis - previousMillis2 <= interval_white2) {

    ledState_white = HIGH;
    digitalWrite(buss_white, ledState_white);
  }

  if (currentMillis - previousMillis2 >= interval_white2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;
    
    ledState_white = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(buss_white, ledState_white);
  }

}

//Functions called when buttons are pressed
void ThemeSound(){
  button_theme_state = digitalRead(button_theme);   //reads button state
  if (button_theme_state == LOW){                   //if pressed
    mp3_stop();                                     //stops previous sound
    mp3_set_volume(20);                             //sets volume
    mp3_play(1);                                    //play sound
  }
}

void BridgeSound(){
  button_bridge_state = digitalRead(button_bridge);
  if (button_bridge_state == LOW){
    mp3_stop();
    mp3_set_volume(25);  
    mp3_play(2);
  }
  
}

void AlertSound(){
  button_alert_state = digitalRead(button_alert);
  if (button_alert_state == LOW){
    mp3_stop();
    mp3_set_volume(20);   
    mp3_play(3);
  }
  
}

void FiringMode(){
  button_firing_state = digitalRead(button_firing);
  unsigned long cm = millis();
  unsigned long cm2 = millis();
  int fadeValue = 0;
  int contador = 0;
  float maxvalluz=255.0; 
  int sonzinhoini=500;
  int inicial2= 2900;
  int range1=900;
  int range2=200;
  int inicial=3000;
  int fadeout=1000;
  int extra=200;
  int range=range1+range2;
  analogWrite(fire, fadeValue);
  if (button_firing_state == LOW){
   mp3_stop();
   mp3_set_volume(20);
   mp3_play(4);
   while (cm2-cm<inicial+range+extra){ 
    cm2 = millis();
    if (cm2-cm>sonzinhoini and cm2-cm<=inicial2){
     digitalWrite(fire, HIGH);
    }
    if (cm2-cm>inicial2 and cm2-cm<inicial){
     digitalWrite(fire, LOW);
    }
    
    if (cm2-cm>inicial and contador==0){
     mp3_stop();
     mp3_set_volume(20);
     mp3_play(5);
     
     contador=1;
    }
    if (cm2-cm>inicial and cm2-cm<inicial+range1){ 
     fadeValue=(cm2-cm-inicial)*(maxvalluz-100)/(range);
     Serial.print(fadeValue); 
     Serial.println(" ");
     analogWrite(fire, fadeValue);
    }
    if (cm2-cm>inicial+range1 and cm2-cm<inicial+range){ 
     fadeValue=(maxvalluz/range)*(cm2-cm-inicial);
     Serial.print(fadeValue); 
     Serial.println(" ");
     analogWrite(fire, fadeValue);
    }
    if (cm2-cm>inicial+range and cm2-cm<inicial+range+extra){ 
     fadeValue=255;
     analogWrite(fire, fadeValue);
    }
    if (cm2-cm>inicial+range+extra and cm2-cm<inicial+range+extra+fadeout){ 
     fadeValue=255-(maxvalluz/fadeout)*(cm2-cm-inicial-range-extra);
     //Serial.print(fadeValue); 
     //Serial.println(" ");
     analogWrite(fire, fadeValue);
    }
    }
  }
}

void MuteMode()
{
  button_mute_state = digitalRead(button_mute);
  if (button_mute_state == LOW){
    mp3_stop();
  }
}

void setup() {
  // Set the digital pin as output:
  pinMode (buss_yellow, OUTPUT);
  pinMode (buss_red, OUTPUT);
  pinMode (buss_green_blue, OUTPUT);
  pinMode (buss_white, OUTPUT);

  // Set button pins as input
  pinMode (button_theme, INPUT);
  pinMode (button_bridge, INPUT);
  pinMode (button_alert, INPUT);
  pinMode (button_firing, INPUT);
  pinMode (button_mute, INPUT);

  //Set up the saucer's LEDs 
  SaucerBlink.begin();

  //Set configuration of DFPlayer mini
  Serial.begin(9600);
  DFPlayerSerial.begin(9600);
  mp3_set_serial(DFPlayerSerial);
}

void loop() {

  SaucerBlink.update();
  BussBlink();
  ThemeSound();
  BridgeSound();
  AlertSound();
  FiringMode();
  MuteMode();

}
