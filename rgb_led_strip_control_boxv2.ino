#include <IRremote.h>
#include <Wire.h>

#include "RTClib.h"

#include "Led.h"
#include "Pulser.h"

#define RED_PIN 10  // red pin
#define GREEN_PIN 5 // green pin
#define BLUE_PIN 9  // blue pin

#define RECEIVER 2 // IR receiver pin

#define DEF_STEP 1 // PWM step value
#define DEF_DELAY 3 // delay between steps in milliseconds

#define PRINT_TIME_TO_SERIAL false

/* -- RGB remote controller button values -- */
const unsigned long r_incBrightness = 0xF700FF;
const unsigned long r_decBrightness = 0xF7807F;
const unsigned long r_off           = 0xF740BF;
const unsigned long r_on            = 0xF7C03F;
const unsigned long r_red1          = 0xF720DF;
const unsigned long r_red2          = 0xF710EF;
const unsigned long r_red3          = 0xF730CF;
const unsigned long r_red4          = 0xF708F7;
const unsigned long r_red5          = 0xF728D7;
const unsigned long r_green1        = 0xF7A05F;
const unsigned long r_green2        = 0xF7906F;
const unsigned long r_green3        = 0xF7B04F;
const unsigned long r_green4        = 0xF78877;
const unsigned long r_green5        = 0xF7A857;
const unsigned long r_blue1         = 0xF7609F;
const unsigned long r_blue2         = 0xF750AF;
const unsigned long r_blue3         = 0xF7708F;
const unsigned long r_blue4         = 0xF748B7;
const unsigned long r_blue5         = 0xF76897;
const unsigned long r_white         = 0xF7E01F;
const unsigned long r_flash         = 0xF7D02F;
const unsigned long r_strobe        = 0xF7F00F;
const unsigned long r_fade          = 0xF7C837;
const unsigned long r_smooth        = 0xF7E817;
/* ----------------------------------------- */

Led *red_led;
Led *green_led;
Led *blue_led;

RTC_DS1307 RTC;

unsigned int curr_button;
unsigned int prev_button;

unsigned long int last_cycle;

IRrecv irrecv(RECEIVER);
decode_results results;

Pulser *red_puls;
Pulser *green_puls;
Pulser *blue_puls;

void setup() {
  if(PRINT_TIME_TO_SERIAL) {
    Serial.begin(9600);
  }

  // setup clock
  pinMode(17, OUTPUT); //analog3 SDA
  digitalWrite(17, HIGH);
  pinMode(16, OUTPUT); //analog2
  digitalWrite(16, LOW);
  Wire.begin();
  RTC.begin();
  // set new time when needed
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  
  // enable IR receiver
  irrecv.enableIRIn();
  
  // set RGB pins to output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  red_led = new Led(RED_PIN, 0, 255);
  green_led = new Led(GREEN_PIN, 0, 255);
  blue_led = new Led(BLUE_PIN, 0, 255);

  red_led->set(0);
  green_led->set(0);
  blue_led->set(0);

  red_led->show();
  green_led->show();
  blue_led->show();
}

int temp_sec = 0;

bool isOff(){
  return red_led->getCurrent() == 0 && green_led->getCurrent() == 0 && blue_led->getCurrent() == 0;
}

void destroyPulsers(){
  free(red_puls);
  free(green_puls);
  free(blue_puls);
}

void print_current_time_to_serial(DateTime now){
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void loop() {
  DateTime now = RTC.now();

  if(PRINT_TIME_TO_SERIAL){
    print_current_time_to_serial(now);
  }

  if (irrecv.decode(&results)) {  
    if(results.value == r_off){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0);
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_on) {
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255);
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255); 
  
    } else if (results.value == r_red1){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_red2){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 64); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_red3){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 128); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_red4){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 192); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_red5){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0); 

    } else if (results.value == r_green1){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0);

    } else if (results.value == r_green2){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 64);

    } else if (results.value == r_green3){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 128);

    } else if (results.value == r_green4){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 192);

    } else if (results.value == r_green5){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_blue1){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_blue2){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 64); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_blue3){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 128); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_blue4){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 192); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_blue5){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_white){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 255); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 255); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 255);

    } else if (results.value == r_strobe){
      destroyPulsers();
      red_puls = new Pulser(*red_led, red_led->getCurrent(), 200, red_led->getCurrent(), 0); 
      red_puls->setRepeatable(true);
      red_puls->setReversable(true);
      green_puls = new Pulser(*green_led, green_led->getCurrent(), 200, green_led->getCurrent(), 0); 
      green_puls->setRepeatable(true);
      green_puls->setReversable(true);
      blue_puls = new Pulser(*blue_led, blue_led->getCurrent(), 200, blue_led->getCurrent(), 0);
      blue_puls->setRepeatable(true);
      blue_puls->setReversable(true);

    } else if (results.value == r_fade){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), 0); 
      red_puls->setRepeatable(true);
      red_puls->setReversable(true);
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), 0); 
      green_puls->setRepeatable(true);
      green_puls->setReversable(true);
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), 0);
      blue_puls->setRepeatable(true);
      blue_puls->setReversable(true);

    } else if (results.value == r_decBrightness){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), red_led->getCurrent()-50); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), green_led->getCurrent()-50); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), blue_led->getCurrent()-50);

    } else if (results.value == r_incBrightness){
      destroyPulsers();
      red_puls = new Pulser(*red_led, DEF_STEP, DEF_DELAY, red_led->getCurrent(), red_led->getCurrent()+50); 
      green_puls = new Pulser(*green_led, DEF_STEP, DEF_DELAY, green_led->getCurrent(), green_led->getCurrent()+50); 
      blue_puls = new Pulser(*blue_led, DEF_STEP, DEF_DELAY, blue_led->getCurrent(), blue_led->getCurrent()+50);
      
    }
    
    irrecv.resume(); // Receive the next value
  }
    
  if(isOff() && now.hour() == 7 && now.minute() == 5 && now.second() == 0){
      delay(1000);
      destroyPulsers();
      red_puls = new Pulser(*red_led, 1, 4000, 0, 255);
      green_puls = new Pulser(*green_led, 1, 4000, 0, 255); 
      blue_puls = new Pulser(*blue_led, 1, 4000, 0, 255); 
  }
  
  red_puls->runCycle();
  green_puls->runCycle();
  blue_puls->runCycle();
  
  red_led->show();
  green_led->show();
  blue_led->show();
}
