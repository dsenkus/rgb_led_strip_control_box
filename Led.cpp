#include "Led.h"
#include "Arduino.h"

Led::Led(int pin_value, int min_value, int max_value){
  _pin = pin_value;
  _min = min_value;
  _max = max_value;

  _current = _min;
}

void Led::inc(int val){
  _current += val;
  
  if(_current > _max){
    _current = _max;
  }
}

void Led::dec(int val){
  _current -= val;
  
  if(_current < _min){
    _current = _min;
  }
}

void Led::setMin(){
  _current = _min;
}

void Led::setMax(){
  _current = _max;
}

void Led::set(int val){
  _current = val;
}

int Led::getCurrent(){
  return _current;
}

void Led::show(){
  analogWrite(_pin, _current);
}
