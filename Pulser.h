#ifndef Pulser_h
#define Pulser_h

#include "Led.h"
#include "Arduino.h"

class Pulser {
  private:
  
  enum Direction { ASC, DESC };

  Led *led;
  int step_;
  int delay_;
  int start_at;
  int end_at;
  int reverse_count;

  Direction curr_direction;

  int increasing;

  bool is_reversable;
  bool is_repeatable;
  bool is_stoped;


  unsigned long int next_cycle;

  bool isBoundariesReached();

  public:

  Pulser(Led&, int , int , int = LOW, int = HIGH);
  
  void setRepeatable(bool);
  void setReversable(bool);
  void reverseDirection();

  void reset();
  
  void runCycle();
};
#endif
