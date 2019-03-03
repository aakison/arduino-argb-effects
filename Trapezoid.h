#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Math.h"

class Trapezoid {
  public:
    Trapezoid(int startRampUp, int endRampUp, int startRampDown, int endRampDown, int duration) {
      this->startRampUp = startRampUp;
      this->endRampUp = endRampUp;
      this->startRampDown = startRampDown;
      this->endRampDown = endRampDown;
      this->duration = duration;
      offset = 0;
    }
    int Evaluate(long time) {
      int delta = time % duration;
      if(delta < startRampUp) {
        return 0;
      }
      else if(delta < endRampUp) {
        return InverseLerpLerp(startRampUp, endRampUp, 0, 255, delta);
      }
      else if(delta < startRampDown) {
        return 255;
      }
      else if(delta < endRampDown) {
        return InverseLerpLerp(startRampDown, endRampDown, 255, 0, delta);
      }
      else {
        return 0;
      }
    }
    Trapezoid Offset(int offset) {
      Trapezoid t = Trapezoid(startRampUp, endRampUp, startRampDown, endRampDown, duration);
      t.offset = offset;
      return t;
    }
  private:
    int startRampUp;
    int endRampUp;
    int startRampDown;
    int endRampDown;
    int duration;
    int offset;
};

#endif
