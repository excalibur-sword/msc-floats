#ifndef _0AA174A7_C786_4362_9ABD_6103B7DE5C86
#define _0AA174A7_C786_4362_9ABD_6103B7DE5C86

#include "float_80.h"

class double_float_80_t {
  float_80_t x[2];

  inline __declspec(nothrow) double_float_80_t(
    const float_80_t &hi, const float_80_t &lo
  ) {
    this->x[0] = hi;
    this->x[1] = lo;
  }
public:
  inline __declspec(nothrow) ~double_float_80_t(void) = default;
  inline __declspec(nothrow) double_float_80_t(void) {}
  inline __declspec(nothrow) double_float_80_t(const float_80_t &ld) {
    this->x[0] = ld;
    this->x[1] = {0};
  }
  inline __declspec(nothrow) double_float_80_t(const double_float_80_t &) = default;

  inline __declspec(nothrow) float_80_t Hi(void) const {return this->x[0];}
  inline __declspec(nothrow) float_80_t Lo(void) const {return this->x[1];}

  // Assignments
  inline double_float_80_t & operator =(double v) {
    DoubleToLongDouble(this->x[0], v);
    this->x[1] = {0};
    return *this;
  }
  double_float_80_t & operator =(const double_float_80_t &) = default;

  // Unary Minus
  inline __declspec(nothrow) double_float_80_t operator -(void) const {
    return {-this->x[0], -this->x[1]};
  }
  inline bool IsZero(void) const {return this->x[0].IsZero() && this->x[1].IsZero();}

  // Self-Additions
  double_float_80_t & operator +=(const float_80_t &a);
  double_float_80_t & operator +=(const double_float_80_t &a);

  // Self-Subtractions
  double_float_80_t & operator -=(const float_80_t &a);
  double_float_80_t & operator -=(const double_float_80_t &a);

  // Self-Multiplications
  double_float_80_t & operator *=(const float_80_t &a);
  double_float_80_t & operator *=(const double_float_80_t &a);

  // Self-Divisions
  double_float_80_t & operator /=(const float_80_t &a);
  double_float_80_t & operator /=(const double_float_80_t &a);
};

// Additions
inline double_float_80_t operator +(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t += b;
  return t;
}
inline double_float_80_t operator +(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(b);
  t += a;
  return t;
}
inline double_float_80_t operator +(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t += b;
  return t;
}

// Subtractions
inline double_float_80_t operator -(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}
inline double_float_80_t operator -(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}
inline double_float_80_t operator -(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}

// Multiplications
inline double_float_80_t operator *(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t *= b;
  return t;
}
inline double_float_80_t operator *(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(b);
  t *= a;
  return t;
}
inline double_float_80_t operator *(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t *= b;
  return t;
}

// Divisions
inline double_float_80_t operator /(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}
inline double_float_80_t operator /(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}
inline double_float_80_t operator /(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}

#endif // _0AA174A7_C786_4362_9ABD_6103B7DE5C86
