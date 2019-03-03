#ifndef MATH_H
#define MATH_H

// Does an Inverse Lerp on the from range, followed by a lerp to the to range.
// Designed to work with integers without rounding or overflow.
int InverseLerpLerp(int fromMin, int fromMax, int toMin, int toMax, int fromValue) {
  int fromRange = fromMax - fromMin;
  int toRange = toMax - toMin;
  int fromDelta = fromValue - fromMin;
  return (int)(toMin + (long)toRange * fromDelta / fromRange);
}

#endif
