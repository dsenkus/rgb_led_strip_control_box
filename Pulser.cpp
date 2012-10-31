#include "Pulser.h"
//TODO: reversible, repeatable
Pulser::Pulser(Led &led, int step_, int delay_, int start_at, int end_at)
: led(&led), step_(step_), delay_(delay_), start_at(start_at), end_at(end_at)
{
  // check and adjust boundaries if necessary
  if(end_at < LOW){
    end_at = LOW;
  }
  if(end_at > HIGH){
    end_at = HIGH;
  }
  if(start_at < LOW){
    start_at = LOW;
  }
  if(start_at > HIGH){
    start_at = HIGH;
  }

  is_repeatable = false;
  is_reversable = false;
  reset();
  next_cycle = millis();
}

void Pulser::setRepeatable(bool val){
  is_repeatable = val;
}

void Pulser::setReversable(bool val){
  is_reversable = val;
}

void Pulser::reset(){
  led->set(start_at);
  reverse_count = 0;
  is_stoped = false;

  if(start_at < end_at){    
    curr_direction = ASC;
  } else {
    curr_direction = DESC;
  }  
}

void Pulser::reverseDirection(){
  curr_direction = curr_direction == ASC ? DESC : ASC;       
  reverse_count++; 
}

bool Pulser::isBoundariesReached(){
  int first_boundary  = start_at < end_at ? end_at : start_at;
  int second_boundary = start_at < end_at ? start_at : end_at; 
  return (curr_direction == ASC && led->getCurrent() >= first_boundary) 
      || (curr_direction == DESC && led->getCurrent() <= second_boundary);
}

void Pulser::runCycle()
{
  if(millis() >= next_cycle && start_at != end_at){
    // check for start/end bound values
    if(isBoundariesReached()){
      if(is_repeatable){
        if(is_reversable){
          reverseDirection();
        } else {
          reset();
        }     
      } else {
        if(is_reversable){
          if(reverse_count >= 1){ // only single reversion allows, since it is not repeatable
            is_stoped = true;
          } else {
            reverseDirection();
          }
        } else {
          is_stoped = true;
        }   
      }
    }


    if(!is_stoped){
      // increase/decrease led value
      if(curr_direction == ASC){
        led->inc(step_);  
      } else if (curr_direction == DESC){
        led->dec(step_);
      }
    }

    // calculate next cycle
    next_cycle = millis() + delay_;
  }
}
