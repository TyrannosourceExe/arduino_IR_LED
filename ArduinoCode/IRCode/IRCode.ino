/* LED Sheild control using infrared signals
 * Date last modified: 12/2/2018
 * Author: Terry Thurk
 */

#include <IRremote.h>

/* map all remote key signals, different for each remote */
#define VOL_MINUS 255
#define PLAY_PAUSE 32895
#define VOL_PLUS 16575
#define SETUP 8415
#define UP 41055
#define STOP_MODE 24735
#define LEFT 4335
#define ENTER_SAVE 36975
#define RIGHT 20655
#define ZERO_TEN 12495
#define DOWN 45135
#define RETURN 28815
#define ONE 2295
#define TWO 34935
#define THREE 18615
#define FOUR 10455
#define FIVE 43095
#define SIX 26675
#define SEVEN 6373
#define EIGHT 39015
#define NINE 22695
#define HOLD 65535



/* global IR objects */

int IR_pin = 8;

int first_led_pin = 7;
int second_led_pin = 6;
int third_led_pin = 5;
int fourth_led_pin = 4;

int led[] = {0,0,0,0};

IRrecv receiver(IR_pin);
decode_results IR_out;

void IR_init(void){
   /* infrared receiver setup*/
   receiver.enableIRIn();
}

void PIN_PORT_init(void){
  pinMode(first_led_pin, OUTPUT);
  pinMode(second_led_pin, OUTPUT);
  pinMode(third_led_pin, OUTPUT);
  pinMode(fourth_led_pin, OUTPUT);
}

void LED_init(void){
  
}

void setup(void) {
 IR_init();
 PIN_PORT_init();
}

void loop(void) {
  // put your main code here, to run repeatedly:
 if (receiver.decode(&IR_out)){
   unsigned int value = IR_out.value;
   switch (value) {
    case ONE:
      if(led[0] == 1) {
        digitalWrite(first_led_pin, LOW);
        led[0] = 0;
      } else {
        digitalWrite(first_led_pin, HIGH);
        led[0] = 1;
      }
      break;
    case TWO:
      if(led[1] == 1) {
        digitalWrite(second_led_pin, LOW);
        led[1] = 0;
      } else {
        digitalWrite(second_led_pin, HIGH);
        led[1] = 1;
      }
      break;
    case THREE:
      if(led[2] == 1) {
        digitalWrite(third_led_pin, LOW);
        led[2] = 0;
      } else {
        digitalWrite(third_led_pin, HIGH);
        led[2] = 1;
      }
      break;
    case FOUR:
      if(led[3] == 1) {
        digitalWrite(fourth_led_pin, LOW);
        led[3] = 0;
      } else {
        digitalWrite(fourth_led_pin, HIGH);
        led[3] = 1;
      }
      break;
   }
   receiver.resume();
 }
}
