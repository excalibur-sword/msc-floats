#pragma warning(push)
#if !defined(__INTEL_COMPILER)
#pragma warning(disable : 4514) // unreferenced inline function
#if !defined(_DEBUG)
#pragma warning(disable : 4710) // function not inlined
#endif
#endif
#include "double_float_80.h"
#pragma warning(pop)

using f80 = float_80_t;
using df80 = double_float_80_t;

namespace {
// Computes fl(a+b) and err(a+b).  Assumes |a| >= |b|.
inline f80 FastTwoSum(const f80 &a, const f80 &b, f80 &e) {
  f80 s = a + b;
  e = b - (s - a);
  return s;
}

// Computes fl(a+b) and err(a+b).
inline f80 TwoSum(const f80 &a, const f80 &b, f80 &e) {
  f80 s = a + b;
  f80 c = s - a;
  e = (a - (s - c)) + (b - c);
  return s;
}

// Computes fl(a-b) and err(a-b).
inline f80 TwoDif(const f80 &a, const f80 &b, f80 &e) {
  f80 s = a - b;
  f80 c = s - a;
  e = (a - (s - c)) - (b + c);
  return s;
}

const f80 C0 = {0x0000u, 0x8000u, 0x0000u, 0x8000u, 0x401fu}; // splitter = 2^32 + 1
const f80 C1 = {0x0000u, 0x0000u, 0x0000u, 0x8000u, 0x7fdeu}; // threshold = 2^16351

// split f80 into hi and lo
void Split(const f80 &a, f80 &hi, f80 &lo) {
  if (Abs(a) > C1) { // overflow
    f80 b = {a.x0(), a.x1(), a.x2(), a.x3(), (unsigned short)((a.x4() - 33u) & 0xffffu)};
    f80 t(C0*b);
    t -= (t - b);
    b -= t;
    hi = {t.x0(), t.x1(), t.x2(), t.x3(), (unsigned short)((t.x4() + 33u) & 0xffffu)};
    lo = {b.x0(), b.x1(), b.x2(), b.x3(), (unsigned short)((b.x4() + 33u) & 0xffffu)};
  } else {
    f80 t(C0*a);
    hi = t - (t - a);
    lo = a - hi;
  }
}

// Computes fl(a*b) and err(a*b).
inline f80 TwoMul(const f80 &a, const f80 &b, f80 &e) {
  f80 a_hi, a_lo, b_hi, b_lo;
  f80 p = a*b;
  Split(a, a_hi, a_lo);
  Split(b, b_hi, b_lo);
  e = ((a_hi*b_hi - p) + a_hi*b_lo + a_lo*b_hi) + a_lo*b_lo;
  return p;
}
} // unnamed namespace

// Self-Additions
df80 & double_float_80_t::operator +=(const f80 &a) {
  f80 s2;
  f80 s1 = TwoSum(this->x[0], a, s2);
  s2 += this->x[1];
  this->x[0] = FastTwoSum(s1, s2, this->x[1]);
  return *this;
}
df80 & double_float_80_t::operator +=(const df80 &a) {
  f80 s2, t2;
  f80 s1 = TwoSum(this->x[0], a.x[0], s2);
  f80 t1 = TwoSum(this->x[1], a.x[1], t2);
  s2 += t1;
  s1 = FastTwoSum(s1, s2, s2);
  s2 += t2;
  this->x[0] = FastTwoSum(s1, s2, this->x[1]);
  return *this;
}

// Self-Subtractions
df80 & double_float_80_t::operator -=(const f80 &a) {
  f80 s2;
  f80 s1 = TwoDif(this->x[0], a, s2);
  s2 += this->x[1];
  this->x[0] = FastTwoSum(s1, s2, this->x[1]);
  return *this;
}
df80 & double_float_80_t::operator -=(const df80 &a) {
  f80 s2, t2;
  f80 s1 = TwoDif(this->x[0], a.x[0], s2);
  f80 t1 = TwoDif(this->x[1], a.x[1], t2);
  s2 += t1;
  s1 = FastTwoSum(s1, s2, s2);
  s2 += t2;
  this->x[0] = FastTwoSum(s1, s2, this->x[1]);
  return *this;
}

// Self-Multiplications
df80 & double_float_80_t::operator *=(const f80 &a) {
  f80 p2;
  f80 p1 = TwoMul(this->x[0], a, p2);
  p2 += this->x[1]*a;
  this->x[0] = FastTwoSum(p1, p2, this->x[1]);
  return *this;
}
df80 & double_float_80_t::operator *=(const df80 &a) {
  f80 p2;
  f80 p1 = TwoMul(this->x[0], a.x[0], p2);
  p2 += a.x[1]*this->x[0];
  p2 += a.x[0]*this->x[1];
  this->x[0] = FastTwoSum(p1, p2, this->x[1]);
  return *this;
}

// Self-Divisions
df80 & double_float_80_t::operator /=(const f80 &y) {
  f80 ry;
  LongDoubleRcp(ry, y);
  f80 th = this->x[0]*ry;
  f80 pl;
  f80 ph = TwoMul(th, y, pl);
  f80 tl = this->x[0] - ph;
  tl += this->x[1] - pl;
  tl *= ry;
  this->x[0] = FastTwoSum(th, tl, this->x[1]);
  return *this;
}
df80 & double_float_80_t::operator /=(const df80 &y) {
  f80 ry;
  LongDoubleRcp(ry, y.x[0]);
  f80 th = this->x[0]*ry;
  df80 r = y;
  r *= th;
  f80 tl = this->x[0] - r.x[0];
  tl += this->x[1] - r.x[1];
  tl *= ry;
  this->x[0] = FastTwoSum(th, tl, this->x[1]);
  return *this;
}
