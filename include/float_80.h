#ifndef _9F964833_F9D8_4D80_992F_45B17DCAD943
#define _9F964833_F9D8_4D80_992F_45B17DCAD943

class float_80_t;

extern "C" {
void fpu_get_cw(unsigned short int &cw);
void fpu_set_cw(const unsigned short int &cw);
void DoubleToLongDouble(float_80_t &ld, const double &d);
void LongDoubleToDouble(const float_80_t &ld, double &d);
void IntegerToLongDouble(float_80_t &ld, const int &i);
void LongDoubleAdd(float_80_t &ld, const float_80_t &v);
void LongDoubleSubtract(float_80_t &ld, const float_80_t &v);
void LongDoubleMultiply(float_80_t &ld, const float_80_t &v);
void LongDoubleDivide(float_80_t &ld, const float_80_t &v);
void LongDoubleSqrt(float_80_t &f, const float_80_t &x);
void LongDoubleSin(float_80_t &f, const float_80_t &x);
void LongDoubleCos(float_80_t &f, const float_80_t &x);
void LongDoubleLn(float_80_t &f, const float_80_t &x);
void LongDoubleLog2(float_80_t &f, const float_80_t &x);
void LongDoubleLog10(float_80_t &f, const float_80_t &x);
void LongDoubleRcp(float_80_t &f, const float_80_t &x);
int LongDoubleCompare(const float_80_t &a, const float_80_t &b);
} // extern "C"

class float_80_t {
  // bitmap
  //  fraction : 63; // fractional part
  //  one      :  1; // always 1 if nonzero and normal
  //  exponent : 15; // exponent + 0x3FFF
  //  sign     :  1; // sign bit
  unsigned short int x[5];

public:
  inline __declspec(nothrow) ~float_80_t(void) = default;
  inline __declspec(nothrow) float_80_t(void) {}
  inline __declspec(nothrow) float_80_t(const int &v) {
    IntegerToLongDouble(*this, v);
  }
  inline __declspec(nothrow) float_80_t(const double &v) {
    DoubleToLongDouble(*this, v);
  }
  inline __declspec(nothrow) float_80_t(
    unsigned short int v0,
    unsigned short int v1,
    unsigned short int v2,
    unsigned short int v3,
    unsigned short int v4
  ) {
    this->x[0] = v0;
    this->x[1] = v1;
    this->x[2] = v2;
    this->x[3] = v3;
    this->x[4] = v4;
  }
  float_80_t(float_80_t const &) = default;

  inline __declspec(nothrow) unsigned short int x0(void) const {return this->x[0];}
  inline __declspec(nothrow) unsigned short int x1(void) const {return this->x[1];}
  inline __declspec(nothrow) unsigned short int x2(void) const {return this->x[2];}
  inline __declspec(nothrow) unsigned short int x3(void) const {return this->x[3];}
  inline __declspec(nothrow) unsigned short int x4(void) const {return this->x[4];}

  inline __declspec(nothrow) double ToDouble(void) const {
    double r;
    LongDoubleToDouble(*this, r);
    return r;
  }

  // Assignments
  inline __declspec(nothrow) float_80_t & operator =(double v) {
    DoubleToLongDouble(*this, v);
    return *this;
  }
  float_80_t & operator =(const float_80_t &) = default;

  // Unary Minus
  inline __declspec(nothrow) float_80_t operator -(void) const {
    return {
      this->x[0],
      this->x[1],
      this->x[2],
      this->x[3],
      (unsigned short int)(this->x[4] ^ 0x8000u)
    };
  }

  // Self-Additions
  inline float_80_t & operator +=(const float_80_t &a) {
    LongDoubleAdd(*this, a);
    return *this;
  }
  // Self-Subtractions
  inline float_80_t & operator -=(const float_80_t &a) {
    LongDoubleSubtract(*this, a);
    return *this;
  }
  // Self-Multiplications
  inline float_80_t & operator *=(const float_80_t &a) {
    LongDoubleMultiply(*this, a);
    return *this;
  }
  // Self-Divisions
  inline float_80_t & operator /=(const float_80_t &a) {
    LongDoubleDivide(*this, a);
    return *this;
  }

  // Equality Comparisons
  inline __declspec(nothrow) bool operator ==(const float_80_t &a) const {
    return (
      this->x[0] == a.x[0] &&
      this->x[1] == a.x[1] &&
      this->x[2] == a.x[2] &&
      this->x[3] == a.x[3] &&
      this->x[4] == a.x[4]
    );
  }
  // Not-Equal-To Comparisons
  inline __declspec(nothrow) bool operator !=(const float_80_t &a) const {
    return (
      this->x[0] != a.x[0] ||
      this->x[1] != a.x[1] ||
      this->x[2] != a.x[2] ||
      this->x[3] != a.x[3] ||
      this->x[4] != a.x[4]
    );
  }
  // Greater-Than Comparisons
  inline bool operator >(const float_80_t &a) const {
    return (0 < LongDoubleCompare(*this, a));
  }
  // Less-Than Comparisons
  inline bool operator <(const float_80_t &a) const {
    return (0 > LongDoubleCompare(*this, a));
  }
  // Greater-Than-Or-Equal-To Comparisons
  inline bool operator >=(const float_80_t &a) const {
    return (0 <= LongDoubleCompare(*this, a));
  }
  // Less-Than-Or-Equal-To Comparisons
  inline bool operator <=(const float_80_t &a) const {
    return (0 >= LongDoubleCompare(*this, a));
  }

  // Micellaneous
  inline __declspec(nothrow) bool IsZero(void) const {
    return (
      0 == this->x[0] &&
      0 == this->x[1] &&
      0 == this->x[2] &&
      0 == this->x[3] &&
      0 == (this->x[4] & 0x7fffu)
    );
  }
  inline __declspec(nothrow) bool IsOne(void) const {
    return (
      0 == this->x[0] &&
      0 == this->x[1] &&
      0 == this->x[2] &&
      0x8000u == this->x[3] &&
      0x3fffu == this->x[4]
    );
  }
  inline __declspec(nothrow) bool IsPositive(void) const {
    return (0 == (this->x[4] & 0x8000u));
  }
  inline __declspec(nothrow) bool IsNegative(void) const {
    return (0 != (this->x[4] & 0x8000u));
  }
  inline __declspec(nothrow) bool IsInfinite(void) const {
    return (0 != (this->x[3] & 0x8000u) && 0x7fffu == (this->x[4] & 0x7fffu));
  }
  inline __declspec(nothrow) bool IsQNaN(void) const {
    return (0xc000u == (this->x[3] & 0xc000u) && 0x7fffu == (this->x[4] & 0x7fffu));
  }
};

// mathematical constants
const float_80_t F80_LOG2_E = {0xf0bcu, 0x5c17u, 0x3b29u, 0xb8aau, 0x3fffu}; // log2(e)
const float_80_t F80_LN2 = {0x79acu, 0xd1cfu, 0x17f7u, 0xb172u, 0x3ffeu}; // ln(2)
const float_80_t F80_LOG2_10 = {0x8afeu, 0xcd1bu, 0x784bu, 0xd49au, 0x4000u}; // log2(10)
const float_80_t F80_LOG10_2 = {0xf799u, 0xfbcfu, 0x9a84u, 0x9a20u, 0x3ffdu}; // log10(2)
const float_80_t F80_PI = {0xc235u, 0x2168u, 0xdaa2u, 0xc90fu, 0x4000u}; // pi

// limits
const float_80_t F80_EPS = {0, 0, 0, 0x8000u, 0x3fc0u}; // epsilon
const float_80_t F80_MAX = {0xffffu, 0xffffu, 0xffffu, 0xffffu, 0x7ffeu}; // maximum
const float_80_t F80_MIN = {0, 0, 0, 0x8000u, 0x0001u}; // minimum
const int F80_DIG = 18;

// Equality Comparisons
inline bool operator ==(const int &lh, const float_80_t &rh) { return rh == lh; }
inline bool operator ==(const double &lh, const float_80_t &rh) { return rh == lh; }
// Not-Equal-To Comparisons
inline bool operator !=(const int &lh, const float_80_t &rh) { return rh != lh; }
inline bool operator !=(const double &lh, const float_80_t &rh) { return rh != lh; }
// Greater-Than Comparisons
inline bool operator >(const int &lh, const float_80_t &rh) { return rh < lh; }
inline bool operator >(const double &lh, const float_80_t &rh) { return rh < lh; }
// Less-Than Comparisons
inline bool operator <(const int &lh, const float_80_t &rh) { return rh > lh; }
inline bool operator <(const double &lh, const float_80_t &rh) { return rh > lh; }
// Greater-Than-Or-Equal-To Comparisons
inline bool operator >=(const int &lh, const float_80_t &rh) { return rh <= lh; }
inline bool operator >=(const double &lh, const float_80_t &rh) { return rh <= lh; }
// Less-Than-Or-Equal-To Comparisons
inline bool operator <=(const int &lh, const float_80_t &rh) { return rh >= lh; }
inline bool operator <=(const double &lh, const float_80_t &rh) { return rh >= lh; }

// Additions
inline float_80_t operator +(
  const float_80_t &a, const float_80_t &b
) {
  float_80_t t(a);
  t += b;
  return t;
}
// Subtractions
inline float_80_t operator -(
  const float_80_t &a, const float_80_t &b
) {
  float_80_t t(a);
  t -= b;
  return t;
}
// Multiplications
inline float_80_t operator *(
  const float_80_t &a, const float_80_t &b
) {
  float_80_t t(a);
  t *= b;
  return t;
}
// Divisions
inline float_80_t operator /(
  const float_80_t &a, const float_80_t &b
) {
  float_80_t t(a);
  t /= b;
  return t;
}

// Absolute value
inline __declspec(nothrow) float_80_t Abs(const float_80_t &a) {
  return {
    a.x0(), a.x1(), a.x2(), a.x3(), (unsigned short int)(a.x4() & 0x7fffu)
  };
}

// Reciprocal estimation
inline float_80_t Rcp(const float_80_t &x) {
  float_80_t f;
  LongDoubleRcp(f, x);
  return f;
}

// Square root
inline float_80_t Sqrt(const float_80_t &x) {
  float_80_t f;
  LongDoubleSqrt(f, x);
  return f;
}

// Trigonometric
inline float_80_t Sin(const float_80_t &x) {
  float_80_t f;
  LongDoubleSin(f, x);
  return f;
}
inline float_80_t Cos(const float_80_t &x) {
  float_80_t f;
  LongDoubleCos(f, x);
  return f;
}

// Logarithmic
inline float_80_t Ln(const float_80_t &x) {
  float_80_t f;
  LongDoubleLn(f, x);
  return f;
}
inline float_80_t Log2(const float_80_t &x) {
  float_80_t f;
  LongDoubleLog2(f, x);
  return f;
}
inline float_80_t Log10(const float_80_t &x) {
  float_80_t f;
  LongDoubleLog10(f, x);
  return f;
}

#endif // _9F964833_F9D8_4D80_992F_45B17DCAD943
