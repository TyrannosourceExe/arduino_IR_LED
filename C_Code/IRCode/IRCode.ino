#include <IRremote.h>

/* global IR objects */

int IR_pin = 8;
IRrecv receiver(IR_pin);
decode_results IR_out;

void IR_init(void){
   /* infrared receiver setup*/
   Serial.begin(9600);
   receiver.enableIRIn();
}

void LED_init(void){
  
}

void setup(void) {
 IR_init();
 /* get IR signals */
}

void loop(void) {
  // put your main code here, to run repeatedly:
 if (receiver.decode(&IR_out)){
   unsigned int value = IR_out.value;
   Serial.println(value);
   receiver.resume();
 }
}
