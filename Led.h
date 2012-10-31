#ifndef Led_h
#define Led_h
#include "Arduino.h"

class Led {
  private:
  int _pin;
  int _current;
  int _min;
  int _max;

  public:

  Led(int pin_value, int min_value = LOW, int max_value = HIGH);
  void inc(int val = 1);
  void dec(int val = 1); 
  void setMin(); 
  void setMax(); 
  void set(int val); 
  int getCurrent();
  void show();
};
#endif
