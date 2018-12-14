/* LED Sheild control using infrared signals
 * Date last modified: 12/3/2018
 * Author: Terry Thurk
 */

#include <Adafruit_NeoPixel.h>

typedef uint32_t COLOR;

int led_pin = 6;
int led_max = 40;
/* create NeoPixel object */
Adafruit_NeoPixel LED = Adafruit_NeoPixel(led_max, led_pin, NEO_RGBW + NEO_KHZ800);

/* LED Brightness */
int brtns = 2;
/* Half brightness calculated once here because division is an expensive operation */
int hlfbrtns = brtns/2;
/* upper and lower bounds of brightness */
const int brtns_min = 2;
const int brtns_max = 50; 

/* delay in rendering for color effect */
int delay_time = 10;


/* LED Colors */
COLOR off = LED.Color(0,0,0,0);
COLOR red = LED.Color(0,brtns,0,0);
COLOR purple = LED.Color(0,hlfbrtns,hlfbrtns,0);
COLOR blue = LED.Color(0,0,brtns,0);
COLOR cyan = LED.Color(hlfbrtns,0,hlfbrtns,0);
COLOR green = LED.Color(brtns,0,0,0);
COLOR yellow = LED.Color(hlfbrtns,hlfbrtns,0,0);
COLOR white = LED.Color(0,0,0,brtns);

//! function to decrease LED brightness
void dec_led_brtns(void){
  if (brtns < brtns_min){
    brtns = brtns_min;
  } else {
    brtns = brtns - 2;
  }
  hlfbrtns = brtns/2;
  red = LED.Color(0,brtns,0,0);
  purple = LED.Color(0,hlfbrtns,hlfbrtns,0);
  blue = LED.Color(0,0,brtns,0);
  cyan = LED.Color(hlfbrtns,0,hlfbrtns,0);
  green = LED.Color(brtns,0,0,0);
  yellow = LED.Color(hlfbrtns,hlfbrtns,0,0);
  white = LED.Color(0,0,0,brtns);
}

void inc_led_brtns(void){
  if (brtns > brtns_max) {
    brtns = brtns_max;
  } else {
    brtns += 2;
  } 
  hlfbrtns = brtns/2;
  red = LED.Color(0,brtns,0,0);
  purple = LED.Color(0,hlfbrtns,hlfbrtns,0);
  blue = LED.Color(0,0,brtns,0);
  cyan = LED.Color(hlfbrtns,0,hlfbrtns,0);
  green = LED.Color(brtns,0,0,0);
  yellow = LED.Color(hlfbrtns,hlfbrtns,0,0);
  white = LED.Color(0,0,0,brtns);
}

//! function to change LED color
void chg_led_color(COLOR color_req){
  int i;
  for (i = 0; i < led_max; ++i){
    LED.setPixelColor(i, color_req);
    delay(delay_time);
    LED.show();
  }
}
/* create a heart using LED display */
void led_heart(COLOR color_req){
  int i;
  int idx_cnt = 20;
  int led_idxs[] = {2,5,9,10,11,12,13,14,17,18,19,20,21,22,26,27,28,29,35,36};
  chg_led_color(off);
  for (i = 0; i < idx_cnt; ++i){
      LED.setPixelColor(led_idxs[i], color_req);
      delay(10);
      LED.show();
  }
  delay(1000);
}

void PIN_PORT_init(void){
}

void LED_init(void){
  LED.begin();
  LED.show(); // Initialize all pixels to 'off'
}

void setup(void) {
  LED_init();
}

void loop(void) {

chg_led_color(off);
//chg_led_color(purple);  
//chg_led_color(blue);
//chg_led_color(cyan);
//chg_led_color(green);
//chg_led_color(yellow);
//led_heart(red);


}
