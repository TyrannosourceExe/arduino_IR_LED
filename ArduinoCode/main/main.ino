/* LED Sheild control using infrared signals
 * Date last modified: 12/3/2018
 * Author: Terry Thurk
 */

#include <Adafruit_NeoPixel.h>
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
#define SIX 26775
#define SEVEN 6375
#define EIGHT 39015
#define NINE 22695
#define HOLD 65535

/* c type definition */
typedef uint32_t COLOR;

/* global LED objects */
int led_pin = 6;
int led_max = 40;
/* create NeoPixel object */
Adafruit_NeoPixel LED = Adafruit_NeoPixel(led_max, led_pin, NEO_RGBW + NEO_KHZ800);
/* LED Colors */
COLOR *color_ary_ptr;
/* Maximum number of colors */
const short color_idx_max = 9;
/* LED Brightness */
int brtns = 2;
/* Half brightness calculated once here because division is an expensive operation */
int hlfbrtns = brtns/2;
/* upper and lower bounds of brightness */
const int brtns_min = 2;
const int brtns_max = 50; 

/* delay in rendering for color effect */
int delay_time = 10;

/* boolean for if the led should be dancing colors*/
boolean is_dance = false;

/* global IR objects */
int IR_pin = 8;
IRrecv receiver(IR_pin);
decode_results IR_out; 

//! function to decrease LED brightness
void dec_led_brtns(void){
  if (brtns <= brtns_min){
    brtns = brtns_min;
  } else {
    brtns = brtns - 2;
  }
  hlfbrtns = brtns/2;
  /* off */
  color_ary_ptr[0] = LED.Color(0,0,0,0);
  /* red */
  color_ary_ptr[1] = LED.Color(0,brtns,0,0);
  /* purple */
  color_ary_ptr[2] = LED.Color(0,hlfbrtns,hlfbrtns,0);
  /* blue */
  color_ary_ptr[3] = LED.Color(0,0,brtns,0);
  /* cyan */
  color_ary_ptr[4] = LED.Color(hlfbrtns,0,hlfbrtns,0);
  /* green */
  color_ary_ptr[5]= LED.Color(brtns,0,0,0);
  /* yellow */
  color_ary_ptr[6] = LED.Color(hlfbrtns,hlfbrtns,0,0);
  /* orange */
  color_ary_ptr[7] = LED.Color(hlfbrtns,brtns,0,0);
  /* white */
  color_ary_ptr[8] = LED.Color(0,0,0,brtns);
}

//! function to increase brightness
void inc_led_brtns(void){
  if (brtns >= brtns_max) {
    brtns = brtns_max;
  } else {
    brtns += 2;
  } 
  hlfbrtns = brtns/2;
  /* off */
  color_ary_ptr[0] = LED.Color(0,0,0,0);
  /* red */
  color_ary_ptr[1] = LED.Color(0,brtns,0,0);
  /* purple */
  color_ary_ptr[2] = LED.Color(0,hlfbrtns,hlfbrtns,0);
  /* blue */
  color_ary_ptr[3] = LED.Color(0,0,brtns,0);
  /* cyan */
  color_ary_ptr[4] = LED.Color(hlfbrtns,0,hlfbrtns,0);
  /* green */
  color_ary_ptr[5]= LED.Color(brtns,0,0,0);
  /* yellow */
  color_ary_ptr[6] = LED.Color(hlfbrtns,hlfbrtns,0,0);
  /* orange */
  color_ary_ptr[7] = LED.Color(hlfbrtns,brtns,0,0);
  /* white */
  color_ary_ptr[8] = LED.Color(0,0,0,brtns);
}

//! function to change LED color
void chg_led_color(COLOR color_req){
  /* turn is_dance off */
  is_dance = 0;
  int pixel_idx;
  for (pixel_idx = 0; pixel_idx < led_max; ++pixel_idx){
    LED.setPixelColor(pixel_idx, color_req);
    delay(delay_time);
    LED.show();
  }
}

/* create a heart using LED display */
void led_heart(COLOR color_req){
  /* turn is_dance off */
  int pixel_idx;
  int idx_cnt = 20;
  int led_idxs[] = {2,5,9,10,11,12,13,14,17,18,19,20,21,22,26,27,28,29,35,36};
  chg_led_color(color_ary_ptr[0]);
  for (pixel_idx = 0; pixel_idx < idx_cnt; ++pixel_idx){
      LED.setPixelColor(led_idxs[pixel_idx], color_req);
      delay(delay_time);
      LED.show();
  }
}

void led_dance(void){
  int color_idx;
  int pixel_idx;
  for (color_idx = 0; color_idx < color_idx_max; ++color_idx){
    for (pixel_idx = 0; pixel_idx < led_max; ++pixel_idx){
      LED.setPixelColor(pixel_idx, color_ary_ptr[color_idx]);
      delay(delay_time);
      LED.show();
    }
  }
}

void LED_init(void){
  /*initialize LED Colors */
  color_ary_ptr = (COLOR*) malloc(color_idx_max * sizeof(COLOR));
  /* off */
  color_ary_ptr[0] = (COLOR) LED.Color(0,0,0,0);
  /* red */
  color_ary_ptr[1] = LED.Color(0,brtns,0,0);
  /* purple */
  color_ary_ptr[2] = LED.Color(0,hlfbrtns,hlfbrtns,0);
  /* blue */
  color_ary_ptr[3] = LED.Color(0,0,brtns,0);
  /* cyan */
  color_ary_ptr[4] = LED.Color(hlfbrtns,0,hlfbrtns,0);
  /* green */
  color_ary_ptr[5]= LED.Color(brtns,0,0,0);
  /* yellow */
  color_ary_ptr[6] = LED.Color(hlfbrtns,hlfbrtns,0,0);
  /* orange */
  color_ary_ptr[7] = LED.Color(hlfbrtns,brtns,0,0);
  /* white */
  color_ary_ptr[8] = LED.Color(0,0,0,brtns);
  LED.begin();
  LED.show(); // Initialize all pixels to 'off'
}

void IR_init(void){
   receiver.enableIRIn();
}

void setup(void) {
  IR_init();
  LED_init();
}

void loop(void) {
  if (receiver.decode(&IR_out)){
    unsigned int value;
    value = IR_out.value;
    /* switch statement based on infrared remote */
    switch(value) {
      case VOL_PLUS:
        inc_led_brtns();
        break;
      case VOL_MINUS:
        dec_led_brtns();
        break;
      case STOP_MODE:
        chg_led_color(color_ary_ptr[0]);
        break;
      case ZERO_TEN:
        break;        
      case ONE:
        chg_led_color(color_ary_ptr[8]);
        break;
      case TWO:
        chg_led_color(color_ary_ptr[1]);
        break;
      case THREE:
        chg_led_color(color_ary_ptr[2]);  
        break;
      case FOUR:
        chg_led_color(color_ary_ptr[3]);
        break;
      case FIVE:
        chg_led_color(color_ary_ptr[4]);
        break;
      case SIX:
        chg_led_color(color_ary_ptr[5]);
        break;
      case SEVEN:
        chg_led_color(color_ary_ptr[6]);
        break;
      case EIGHT:
        chg_led_color(color_ary_ptr[7]);
        break;
      case NINE:
        led_heart(color_ary_ptr[1]);
        break;
      case PLAY_PAUSE:
        is_dance = true;
        break;
      case HOLD:
        is_dance = false;
        break;
    }
    receiver.resume();
  } else if (is_dance == true){
    led_dance();
  } 
}
